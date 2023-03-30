#include <thread>
#include <iostream>
#include <future> // promise(), future()
#include <vector>
#include <array>
#include <cassert>


using namespace std;

void counter(int id, int iterations)
{
    for (auto i {0}; i<iterations; ++i) {
        cout << "Counter " << id << " has value " << i << endl;
    }
}

class Counter {
    public:
        Counter(int id, int iterations) : m_id {id}, m_iterations {iterations} {}
        void operator()() const
        {
            for (int i {0}; i<m_iterations; ++i) {
                cout << "Counter " << m_id << " has value " << i << endl;
            }
        }
    private:
        int m_id;
        int m_iterations;
};

class Request {
    public:
        Request(int id) : m_id {id} {}
        void process() const
        {
            cout << "Processing request " << m_id << endl;
        }
    private:
        int m_id;
};

void test_threadCreation()
{
    // 1. With function pointer
    thread t1(counter, 1, 6);   // 参数是函数指针hello、指定线程id和打印累计数
    t1.join();

    // 2. With function object
    {
    // Counter counter {2, 6};
    // thread t2 {ref(counter)};    // 通过引用传递，避免函数对象被复制
    thread t2 {Counter{2, 6}};
    t2.join();
    }
    // 3. With lambda
    {
    int id {3};
    int iterations {5};
    // thread t3 {[](id, iterations){   // 传递参数
    thread t3 {[id, iterations](){        // 直接捕获参数
        for (int i {0}; i<iterations; ++i) {
            cout << "Counter " << id << " has value " << i << endl;
        }
    }};
    t3.join();
    }
    // 4. With member function
    {
    Request req {100};
    thread t4 {&Request::process, &req};    // 对于成员函数，必须使用&。给成员函数传参，必须传地址，所以使用&req
    t4.join();
    }
}

void test_joinAndDetach()
{
    // With join() to wait the thead to finish
    {
    thread t {[]() {
        for (int i {0}; i<10; ++i) {
            cout << "Thread1 running " << i << endl;
        }
    }};
    t.join();   // join()会等待线程直到执行完成
    cout << "Thead1 finished" << endl;  // 保证顺序打印
    }
    // With detach() to have the thread running background, does not wait for its finishing
    {
    thread t {[]() {
        for (int i {0}; i<10; ++i) {
            cout << "Thread2 running " << i << endl;
        }
    }};
    t.detach(); // 与join()对应的，detach()用来在后台运行线程。
    cout << "Thead2 running separately" << endl;    // 无法保证顺序打印
    }
}

void multiply(int m, int n, promise<int>&& p)
{
    p.set_value(m*n);
}

int foo(int m, int n)
{
    return (m*n);
}

void test_returnValue()
{
    // lambda + reference captured
    {
        int res = 0;
        cout << "Before thread: res = " << res << endl;
        thread t {[&res]() {
            res = 10;
        }};
        t.join();
        cout << "After thread: res = " << res << endl;
    }
    // std::promise和std::future提供了一种可以从异步方法中拿到执行结果的机制。
    {
    promise<int> p;
    auto f = p.get_future();
    thread t {multiply, 5, 6, move(p)};
    t.join();
    int value {f.get()};
    cout << "value = " << value << endl;
    }
    // 使用std::async可以简化上面例子的写法，它异步地执行一个函数，返回std::future类型的结果。
    {
    auto f = async(foo, 7, 8);  // 启动线程异步执行foo，返回std::future给f
    cout << "async value = " << f.get() << endl;
    }
}

class Singleton {
    public:
        static Singleton& instance()
        {
            static Singleton s;
            return s;
        }
        void add(int n)
        {
            lock_guard<mutex> guard(m_mutex);
            m_vec.emplace_back(n);
        }
        int count() const
        {
            return m_vec.size();
        }
        void clear()
        {
            m_vec.clear();
        }
        Singleton(const Singleton&) = delete;   // 禁止构造
        void operator=(const Singleton&) = delete;  // 禁止拷贝
    private:
        mutex m_mutex;
        vector<int> m_vec;
        Singleton() {}
};

int test_dataShare()
{
    vector<thread> threads;
    for (int i {0}; i<10; ++i) {    // 生成10 thread的线程池
        threads.emplace_back(thread([](int i) { // 产生一个thread，放入threads线程池
            Singleton::instance().add(i);   // 每一个thread，都在单例管理的共享vector放入一项
        }, i));
    }
    for (auto& t : threads) {
        t.join();
    }
    // cout << "Now count = " << Singleton::instance().count() << endl;
    return Singleton::instance().count();
}

int g_k;
thread_local int g_n;
void threadFunction(int id)
{
    cout << "Thread " << id << ": " << "k = " << g_k << ", " << "n = " << g_n << "\n";
    ++g_n;  // Each thread has its own copy of g_n
    ++g_k;  // All threads share the same copy of g_k
}

void test_thread_local()
{
    array<thread, 3> threads;
    for (int i {0}; i<3; ++i) {
        threads[i] = thread(threadFunction, i+1);
        threads[i].join();
    }
}

void test_jthread()
{
    // jthread线程在其构造函数调用join()
    jthread job {[](const stop_token& token) {
        while (!token.stop_requested()) {   // jthread支持所谓的合作退出，没有收到退出请求？
            cout << "Doing work ..." << "\n";
        }
    }};
    this_thread::sleep_for(chrono::seconds(1));
    job.request_stop(); // 发退出请求给线程
}

int main()
{
    test_threadCreation();
    test_joinAndDetach();
    test_returnValue();
    for (int i {0}; i<100; ++i) {
        Singleton::instance().clear();  // 需清掉之前的数据
        assert(test_dataShare() == 10);
    }
    test_thread_local();
    test_jthread();
    return 0;
}