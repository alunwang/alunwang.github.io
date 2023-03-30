#ifndef __ITERATOR_H__
#define __ITERATOR_H__

template <typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool valid() const = 0;
    virtual T next() = 0;
};

template <typename T>
class ArrayIterator: public Iterator<T> {
public:
    ArrayIterator(T* p, int s): data(p), size(s) {}
    bool valid() const;
    T next();
private:
    T* data;
    int size;
};

template <typename T>
bool ArrayIterator<T>::valid() const
{
    return (size>0);
}

template <typename T>
T ArrayIterator<T>::next()
{
    --size;
    return *data++;
}

template <typename T>
T sum(Iterator<T>* iter)
{
    T res { 0 };

    while (iter->valid()) {
        res += iter->next();
    }
    return res;
}

#endif // __ITERATOR_H__