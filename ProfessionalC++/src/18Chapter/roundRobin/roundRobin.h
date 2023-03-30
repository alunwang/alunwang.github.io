#ifndef __ROUNDROBIN_H__
#define __ROUNDROBIN_H__

module;
#include <cstddef>
export module round_robin;
import <stdexcept>;
import <vector>;
 
// Class template RoundRobin
// Provides simple round-robin semantics for a list of elements.
export template <typename T>
class RoundRobin
{
    public:
        // Client can give a hint as to the number of expected elements for
        // increased efficiency.
        explicit RoundRobin(size_t numExpected = 0);
        virtual ~RoundRobin() = default;
        // Prevent assignment and pass-by-value
        RoundRobin(const RoundRobin& src) = delete;
        RoundRobin& operator=(const RoundRobin& rhs) = delete;
        // Explicitly default a move constructor and move assignment operator
        RoundRobin(RoundRobin&& src) noexcept = default;
        RoundRobin& operator=(RoundRobin&& rhs) noexcept = default;
        // Appends element to the end of the list. May be called
        // between calls to getNext().
        void add(const T& element);
        // Removes the first (and only the first) element
        // in the list that is equal (with operator==) to element.
        // May be called between calls to getNext().
        void remove(const T& element);
        // Returns the next element in the list, starting with the first,
        // and cycling back to the first when the end of the list is
        // reached, taking into account elements that are added or removed.
        T& getNext();
    private:
        std::vector<T> m_elements;
        typename std::vector<T>::iterator m_nextElement;
};

template <tyepname T>
RoundRobin<T>::RoundBin(size_t numExpected)
{
    m_elements.reserve(numExpected);
    m_nextElement = begin(m_elements);
}

template <typename T>
void RoundRobin<T>::add(const T& element)
{
    // Record the difference
    ptrdiff_t pos {m_nextElement - begin(m_elements)};

    m_elements.push_back(element);

    // push_back might allocate  a new memory block, so begin(m_elements) points the new block instead of the old one.
    // So we need to update the iterator 
    m_nextElement = begin(m_elements) + pos;
}

template <typename T> void RoundRobin<T>::remove(const T& element)
{
    for (auto it {begin(m_elements)}; it != end(m_elements); ++it) {
        if (*it == element) {
            ptrdiff_t newPos;

            if (m_nextElement == end(m_elements) - 1 && m_nextElement == it) {
                newPos = 0;
            } else if (m_nextElement <= it) {
                newPos = m_nextElement - begin(m_elements);
            } else {
                newPos = m_nextElement - begin(m_elements) - 1;
            }

            m_elements.erase(it);
            m_nextElement = begin(m_elements) + newPos;
            return;
        }
    }
}

template <typename T> T& RoundRobin<T>::getNext()
{
    if (m_elements.empty()) {
        throw std::out_of_range {"No element in the list."};
    }

    auto& toReturn {*m_nextElement};

    ++m_nextElement;
    if (m_nextElement == end(m_elements)) {
        m_nextElement = begin(m_elements);
    }

    return toReturn;
}
#endif  // __ROUNDROBIN_H__