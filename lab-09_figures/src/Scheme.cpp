#include "Scheme.hpp"
#include <iostream>

Scheme::Scheme(int capacity) {
	if (capacity < 0)
		throw new std::runtime_error("Capacity is below zero");
	capacity_ = capacity;
	figures_ = new Figure*[capacity_];
	real_figures_count_ = 0;
}

Scheme::~Scheme() {
	for (int i = 0; i < real_figures_count_; i++) {
		delete figures_[i];
	}
	delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
	if (fg == nullptr)
		throw new std::runtime_error("Figure does not exist");
	if (real_figures_count_ == capacity_)
		throw new std::runtime_error(
			"Can't push back figure: all places are taken"
			);
	figures_[real_figures_count_++] = fg;
}

void Scheme::remove_figure(int id) {
	int deleted_index = -1;
	for (int i = 0; i < real_figures_count_; i++) {
		if (figures_[i]->getId() == id) {
			deleted_index = i;
			break;
		}
	}
	if (deleted_index == -1) return;
	delete figures_[deleted_index];
	for (int i = deleted_index; i < real_figures_count_ - 1; i++) {
		figures_[i] = figures_[i + 1];
	}
	real_figures_count_--;
}

void Scheme::print_all_figures() {
	for (int i = 0; i < real_figures_count_; i++) {
		figures_[i]->print();
	}
}

void Scheme::zoom_figure(int id, int factor) {
	for (int i = 0; i < real_figures_count_; i++) {
		if (figures_[i]->getId() == id) {
			figures_[i]->zoom(factor);
		}
	}
}

Figure* Scheme::is_inside_figure(int x, int y) {
	for (int i = 0; i < real_figures_count_; i++) {
		if (figures_[i]->is_inside(x, y))
			return figures_[i];
	}
	return NULL;
}

void Scheme::move(int id, int new_x, int new_y) {
	for (int i = 0; i < real_figures_count_; i++) {
		if (figures_[i]->getId() == id)
			figures_[i]->move(new_x, new_y);
	}
}