#include <stdlib.h>
#include<type_traits>
#include <cstring>

namespace containers {

	template<typename T>
	my_vector<T>::my_vector(std::size_t n) {
		capacity_ = 1;
		while (capacity_ < n) capacity_ *= 2;
		size_ = 0;
		array_ = (T*)calloc(capacity_, sizeof(T));
		if (array_ == nullptr)
			throw std::runtime_error("Not enought memory");
	}

	template<typename T>
	my_vector<T>::my_vector() : my_vector(1) {}

	template<typename T>
	my_vector<T>::my_vector(const my_vector<T>& other) {
		if (&other == this)
			return;
		capacity_ = other.capacity_;
		size_ = other.size_;
		array_ = (T*)calloc(capacity_, sizeof(T));
		if (array_ == nullptr)
			throw std::runtime_error("Not enought memory");
		
		for (std::size_t i = 0; i < size_; i++) 
			array_[i] = other[i];
	}

	template<typename T>
	my_vector<T>& my_vector<T>::operator=(const my_vector<T>& other) {
		if (&other == this) 
			return *this;
		for (std::size_t i = 0; i < size_; i++) {
			delete (array_ + i);
		}
		free(array_);

		capacity_ = other.capacity_;
		size_ = other.size_;
		array_ = (T*)calloc(capacity_,  sizeof(T));
		if (array_ == nullptr)
			throw std::runtime_error("Not enought memory");
		
		for (std::size_t i = 0; i < size_; i++) 
			array_[i] = other[i];
		return *this;
	}

	template<typename T>
	my_vector<T>::~my_vector() {
		if (std::is_destructible<T>::value) {
			for (std::size_t i = 0; i < capacity_; i++) {
				array_[i].~T();
			}
		}
		free(array_);
	}

	template<typename T>
	std::size_t my_vector<T>::size() const {
		return size_;
	}

	template<typename T>
	std::size_t my_vector<T>::capacity() const {
		return capacity_;
	}

	template<typename T>
	bool my_vector<T>::empty() const {
		return size_ == 0;
	}

	template<typename T>
	void my_vector<T>::reserve(std::size_t n) {
		if (n <= capacity_) return;

		std::size_t newN = 1;
		while (newN < n) newN *= 2;
		n = newN;

		T* tmp = (T*)calloc(n, sizeof(T));

		if (tmp == nullptr)
			throw new std::runtime_error("Not enought memory for reserve");

		for (std::size_t i = 0; i < size_; i++)
			tmp[i] = array_[i];

		if (std::is_destructible<T>::value) {
			for (std::size_t i = 0; i < size_; i++) {
				array_[i].~T();		
			}
		}
		free(array_);
		array_ = tmp;
		capacity_ = n;
	}

	template<typename T>
	void my_vector<T>::resize(std::size_t n) {
		if (n > size_) {
			reserve(n);
			for (std::size_t i = size_; i < n; i++)
				array_[i] = T();
		}
		size_ = n;
	}

	template<typename T>
	T& my_vector<T>::operator[](std::size_t index) const {
		return array_[index];
	}

	template<typename T>
	void my_vector<T>::push_back(T t) {
		if (size_ == capacity_) reserve(capacity_ * 2);
		array_[size_++] = t;
	}

	template<typename T>
	void my_vector<T>::pop_back() {
		if (size_ == 0) throw new std::runtime_error("Pop back from empty vector");
		size_--;
	}

	template<typename T>
	void my_vector<T>::clear() {
		size_ = 0;
	}

}

template<typename T>
std::ostream& operator<< (std::ostream& out, const containers::my_vector<T>& v) {
	for (std::size_t i = 0; i < v.size(); i++) {
		out << v[i];
		if (i + 1 != v.size()) out << ' ';
	}
	return out;
}