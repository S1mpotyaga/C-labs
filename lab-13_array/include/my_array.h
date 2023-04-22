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

}  // namespace lab_13



#endif  // MY_ARRAY_H_
