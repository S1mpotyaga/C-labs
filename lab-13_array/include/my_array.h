#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdlib.h>
#include <stdexcept>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:
    my_array();
    
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;


    bool empty() const;
    std::size_t size() const;

    void fill(const T& val);
private:
    T array_[N];
};

template<typename T, std::size_t N>
my_array<T, N>::my_array() {
    for (size_t i = 0; i < N; i++) {
        new (array_ + i) T();
    }
}

template<typename T, std::size_t N>
T& my_array<T, N>::at(std::size_t i) {
    if (i >= N) throw std::out_of_range("Index out of range");
    return array_[i];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::at(std::size_t i) const{
    if (i >= N) throw std::out_of_range("Index out of range");
    return array_[i];
}

template<typename T, std::size_t N>
T& my_array<T, N>::operator[](std::size_t i) {
    return array_[i];
}

template<typename T, std::size_t N>
const T& my_array<T, N>::operator[](std::size_t i) const {
    return array_[i];
}

template<typename T, std::size_t N>
bool my_array<T, N>::empty() const{
    return N == 0;
}

template<typename T, std::size_t N>
size_t my_array<T, N>::size() const{
    return N;
}

template<typename T, std::size_t N>
void my_array<T, N>::fill(const T& val) {
    for (std::size_t i = 0; i < N; i++) {
        array_[i] = val;
    }
}

// bool specification

const uint8_t BLOCK_SIZE = 8;

class my_bool {
public:
    my_bool(uint8_t* data, uint8_t ptr);

    operator bool () const;
    const my_bool& operator= (const my_bool& other);
    const my_bool& operator= (bool b);
private:
    uint8_t* data_;
    uint8_t ptr_;

    bool value() const;
};

my_bool::my_bool(uint8_t* data, uint8_t ptr) {
    data_ = data;
    ptr_ = ptr;
}


bool my_bool::value() const {
    return (((*data_) >> ptr_) & 1);
}

my_bool::operator bool () const{
    return (((*data_) >> ptr_) & 1);
}

const my_bool& my_bool::operator= (const my_bool& other) {
    return (*this = other.value());
}

const my_bool& my_bool::operator= (bool b) {
    (*data_) ^= ((value() ^ b) >> (ptr_));
    return *this;
}

template<std::size_t N>
class my_array<bool, N> {
public:
    my_bool at(std::size_t index);
    bool at(std::size_t index) const;
    my_bool operator[](std::size_t index);
    bool operator[](std::size_t index) const;


    bool empty() const;
    std::size_t size() const;

    void fill(bool b);
private:
    uint8_t array_[(N + BLOCK_SIZE - 1) / BLOCK_SIZE];
};

template<std::size_t N>
my_bool my_array<bool, N>::at(std::size_t i) {
    if (i >= N) throw std::out_of_range("List index out of range");
    return my_bool(array_ + (i / BLOCK_SIZE), (i & (BLOCK_SIZE - 1)));
}

template<std::size_t N>
bool my_array<bool, N>::at(std::size_t i) const {
    if (i >= N) throw std::out_of_range("List index out of range");
    return ((array_[i / BLOCK_SIZE] >> (i & (BLOCK_SIZE - 1))) & 1);
}

template<std::size_t N>
my_bool my_array<bool, N>::operator[](std::size_t i) {
    return my_bool(array_ + (i / BLOCK_SIZE), (i & (BLOCK_SIZE - 1)));
}

template<std::size_t N>
bool my_array<bool, N>::operator[](std::size_t i) const {
    return ((array_[i / BLOCK_SIZE] >> (i & (BLOCK_SIZE - 1))) & 1);
}

template<std::size_t N>
bool my_array<bool, N>::empty() const {
    return N == 0;
}

template<std::size_t N>
std::size_t my_array<bool,N>::size() const{
    return N;
}

template<std::size_t N>
void my_array<bool, N>::fill(bool b) {
    for (std::size_t i = 0; i < (N + (BLOCK_SIZE - 1)) / BLOCK_SIZE; i++) {
        if (b) array_[i] = ((1 << BLOCK_SIZE) - 1);
        else array_[i] = 0;
    }
}

}  // namespace lab_13

#endif  // MY_ARRAY_H_
