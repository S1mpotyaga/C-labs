#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    explicit my_vector(const my_vector<T> &other);
    my_vector& operator=(const my_vector<T>& other);
    ~my_vector();

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T& operator[](std::size_t index) const;

    void push_back(T t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const containers::my_vector<T>& v);  

#include "my_vector_impl.hpp"

#endif  // MY_VECTOR_H_
