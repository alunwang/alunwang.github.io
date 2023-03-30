#include <queue>


template <typename T>
class SaveQueue {
    private:
        std::queue<T> m_queue;
        std::mutex m_mtx;
    public:
        SaveQueue() {}
        SaveQueue(SaveQueue&& q) {}
        ~SaveQueue() {}

        bool empty() const
        {
            // Lock the queue from being changed
            std::unqiue_lock<std::mutex> lock(m_mtx);
            return m_queue.empty();
        }
        int size() const
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            return m_queue.size();
        }
        void enqueue(T& t)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            m_queue.emplace_back(t);
        }
        bool dequeue(T& t)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            if (m_queue.empty()) {
                return false;
            }
            t = std::move(m_queue.front()); // 取出队首元素，返回队首元素值，并进行右值引用
            m_queue.pop();
            return true;
        }
};


tempalte <typename F, typename... Args>
auto submit(F&& f, Args&&...args) -> std::future<decltype(f(args...))> // 尾返回类型推导
{
    // Create a function with bounded parameter ready to execute
    std::function<decltype(f(args...))()> func = std::bind(
        std::forward<F>(f), 
        std::forward<Args>(args)...); // 连接函数和参数定义，特殊函数类型，避免左右值错误
    // Encapsulate it into a shared pointer in order to be able to copyt constructor
    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

    // Wrap packaged task into void function
    std::function<void()> wrapper_func = [task_ptr]()
    {
        (*task_ptr)();
    };

    m_queue.enqueue(wrapper_func);
    m_condVar.notify_one();
    // 返回先前注册的任务指针
    return task_ptr->get_future();
}