#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <iterator>
#include <iomanip>
#include <chrono>
#include <cassert>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include "objectPool.h"

using namespace std;

class ExpensiveObject {
    public:
        ExpensiveObject() {}
        virtual ~ExpensiveObject() = default;
        // Methods to populate the object with specific information
        // Methods to retrieve the object data
        //
    private:
        // An expensive data member
        array<double, 4*1024*1024> m_data;
        // Other members
};

using MyPool = ObjectPool<ExpensiveObject>;
shared_ptr<ExpensiveObject> getExpensiveObject(MyPool& pool)
{
    // Obtain an ExpensiveObject object from the pool
    auto object { pool.acquireObject() };
    // Populate the object.
    return object;
}

void processExpensiveObject(ExpensiveObject* object)
{}

int main()
{
    std::vector<double> data(9);
    double initial {-4};
    std::iota(std::begin(data), std::end(data), initial);
    std::copy(std::begin(data), std::end(data),
        std::ostream_iterator<double> {std::cout << std::fixed << std::setprecision(2), " "});
    std::cout << std::endl;

    const size_t numberOfIterations { 500'000 };
    cout << "Starting loop using pool..." << endl;
    MyPool requestPool;
    auto start1 { chrono::steady_clock::now() };
    for (size_t i {0}; i<numberOfIterations; ++i) {
        auto object { getExpensiveObject(requestPool) };
        processExpensiveObject(object.get());
    }
    auto end1 { chrono::steady_clock::now() };
    auto diff1 { end1 - start1 };
    cout << fmt::v9::format("{}ms\n", chrono::duration<double, milli>(diff1).count());
    return 0;
}