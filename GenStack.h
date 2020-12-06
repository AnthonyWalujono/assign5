#ifndef CPSC_350_GENSTACK_H
#define CPSC_350_GENSTACK_H

#include <exception>

template <class T>
class GenStack {

public:

    GenStack();
    ~GenStack();
    void push(const T& data);
    void pop();
    T& top();
    const T& peek() const;
    bool isEmpty() const;
    int getSize() const;

private:

    T* mArray;
    int mAlloc;
    int mTop;
};

template <class T>
GenStack<T>::GenStack() {
    mArray = new T[1];
    mAlloc = 1;
    mTop = -1;
}
template <class T>
GenStack<T>::~GenStack() {
    delete[] mArray;
    mArray = nullptr;
    mAlloc = 0;
    mTop = -1;
}
template <class T>
void GenStack<T>::push(const T& data) {
    if (++mTop == mAlloc) {
        // Capacity has been reached. Double the capacity before push the new item
        T* newArray = new T[mAlloc * 2];
        for (int i = 0; i < mAlloc; ++i) {
            newArray[i] = mArray[i];
        }
        delete[] mArray;
        mArray = newArray;
        newArray = nullptr;
        mAlloc *= 2;
    }
    mArray[mTop] = data;
}
template <class T>
void GenStack<T>::pop() {
    if (isEmpty()) {
        throw std::exception("pop called on an empty stack");
    }
    --mTop;
}
template<class T>
T& GenStack<T>::top() {
    if (isEmpty()) {
        throw std::exception("top called on an empty stack");
    }
    return mArray[mTop];
}
template <class T>
const T& GenStack<T>::peek() const {
    if (isEmpty()) {
        throw std::exception("peek called on an empty stack");
    }
    return mArray[mTop];
}
template <class T>
bool GenStack<T>::isEmpty() const {
    return (mTop == -1);
}
template <class T>
int GenStack<T>::getSize() const {
    return mTop + 1;
}

#endif // !CPSC_350_GENSTACK_H