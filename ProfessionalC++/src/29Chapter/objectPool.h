#ifndef __OBJECTPOOL_H__
#define __OBJECTPOOL_H__

#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <iomanip>

/*
 * Provides an object pool that can be used with any class that provides a default constructor
 * 
 * acquireObject() returns an object from the list of free objects. If there are no more free objects,
 * acquireObject() creates a new chunk of objects.
 * The pool only grows: Objects are never removed from the pool, until the pool is destroyed.
 * acquireObject() returns an std::shared_ptr with a custom deleter that auttomatically puts the object
 * back into the object poolthe shared_ptr is destroyed and its reference couter reaches 0.
 */
template <typename T, typename Allocator = std::allocator<T>>
class ObjectPool {
    public:
        ObjectPool() = default;
        explicit ObjectPool(const Allocator& alloc);
        virtual ~ObjectPool();
        // Allow move construction and move assignment
        ObjectPool(ObjectPool&& src) noexcept = default;
        ObjectPool& operator=(ObjectPool&& rhs) noexcept = default;
        // Prevent copy construction and copy assignment
        ObjectPool(const ObjectPool& src) = delete;
        ObjectPool& operator=(const ObjectPool& rhs) = delete;

        // Reserves and returns an object from the pool. Arguments can be provided which are perfectly forwarded
        // to a constructor of T.
        template <typename... Args>
        std::shared_ptr<T> acquireObject(Args... args);
    private:
        // Contains chunks of memory in which instances of T will be created.
        // For each chunk, the pointer to its first object is stored.
        std::vector<T*> m_pool;
        // Contains pointers to all free instances of T that are available in the pool.
        std::vector<T*> m_freeObjects;
        // The number of T instances that should fit in the first allocated chunk.
        static const size_t m_initialChunkSize {5};
        // The number of T instances that should fit in a newly allocated chunk.
        size_t m_newChunkSize {m_initialChunkSize};
        // Create a new block of uninitialized memory, bit enough to hold m_newChunkSzie instances of T.
        void addChunk();
        // The allocator to use for allocating and deallocating chunks.
        Allocator m_allocator;
};

template <typename T, typename Allocator>
ObjectPool<T, Allocator>::ObjectPool(const Allocator& alloc) : m_allocator {alloc} {}

template <typename T, typename Allocator>
void ObjectPool<T, Allocator>::addChunk()
{
    std::cout << "Allocating new chunk..." << std::endl;

    // Allocate a new chunk of uninitialized memory big enough to hold m_newChunkSize instances of T,
    // and add the chunk to the pool.
    auto* firstNewObject {m_allocator.allocate(m_newChunkSize)};
    m_pool.push_back(firstNewObject); // 为何只push_back()一次？？？

    // Create pointers to each individual object in the new chunk and store them in the list of free objects.
    auto oldFreeObjectSize {m_freeObjects.size()};
    m_freeObjects.resize(oldFreeObjectSize + m_newChunkSize); // 调整大小
    // iota()函数用firstNewObject作初值，填入第一个iterator参数指定位置，然后++，连续填入后续的位置
    std::iota(std::begin(m_freeObjects) + oldFreeObjectSize, std::end(m_freeObjects), firstNewObject);

    // Double the chunk size for next time
    m_newChunkSize *= 2;
}

template <typename T, typename Allocator>
template <typename... Args>
std::shared_ptr<T> ObjectPool<T, Allocator>::acquireObject(Args... args)
{
    // If there is no free object, allocate a new chunk.
    if (m_freeObjects.empty()) {
        addChunk();
    }
    // Got a free object
    T* object {m_freeObjects.back()};
    // Initialize, i.e. contruct, an instance of T in an unintialized block of memory using placement new,
    // and perfectly forward any provided arguments to the constructor.
    new(object) T {std::forward<Args>(args)...};
    // Remove the object from the list of free objects
    m_freeObjects.pop_back();
    // Wrap the initialized object and return it.
    return std::shared_ptr<T> {object, [this](T* object) {
        // Destroy object.
        std::destroy_at(object);
        // Put the object back in the list of free objects.
        m_freeObjects.push_back(object);
    }};
}

template <typename T, typename Allocator>
ObjectPool<T, Allocator>::~ObjectPool()
{
    // Note: this implementation assumes that all objects handed out by this pool have been returned to
    // the pool before the pool is destroyed.
    // The following statement asserts if that is not the case.
    assert(m_freeObjects.size() == m_initialChunkSize * (std::pow(2, m_pool.size())-1));
    // Deallocate all allocated memory.
    size_t chunkSize {m_initialChunkSize};
    for (auto* chunk : m_pool) {
        m_allocator.deallocate(chunk, chunkSize);
        chunkSize *= 2;
    }
    m_pool.clear();
}

#endif // __OBJECTPOOL_H__