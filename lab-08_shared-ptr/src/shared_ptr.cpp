#include "shared_ptr.hpp"

shared_ptr::Storage::Storage(Matrix* mt) {
	data_ = mt;
	ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
	delete data_;
}

void shared_ptr::Storage::incr() {
	++ref_count_;
}

void shared_ptr::Storage::decr() {
	--ref_count_;
	if (ref_count_ == 0) {
		delete this;
	}
}

int shared_ptr::Storage::getCounter() const{
	return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const{
	return data_;
}

shared_ptr::shared_ptr(Matrix* obj) {
	if (obj == nullptr) {
		storage_ = nullptr;
		return;
	}
	storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
	storage_ = other.storage_;
	if (storage_ != nullptr) storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	if (storage_ != nullptr) storage_->decr();
	storage_ = other.storage_;
	storage_->incr();
	return *this;
}

shared_ptr::~shared_ptr() {
	if (storage_ != nullptr) storage_->decr();
	storage_ = nullptr;
}

Matrix* shared_ptr::ptr() const{
	if (storage_ == nullptr) return nullptr;
	return storage_->getObject();
}

bool shared_ptr::isNull() const {
	return storage_ == nullptr;
}

void shared_ptr::reset(Matrix* obj) {
	storage_->decr();
	if (obj == nullptr) {
		storage_ = nullptr;
		return;
	}
	storage_ = new Storage(obj);
}

Matrix* shared_ptr::operator->() const {
	if (storage_ == nullptr) return nullptr;
	return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
	return *(storage_->getObject());
}