#include "Rectangle.hpp"
#include <cstdio>
#include <cmath>
#include <iostream>

Rectangle::Rectangle(int id, int x, int y, int width, int height): Figure(id, x, y) {
	if (width < 0 || height < 0)
		throw new std::runtime_error("Incorrect size"); 
	this->width = width;
	this->height = height;
}

Rectangle::~Rectangle() {}	

void Rectangle::print() const {
	printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", 
		id, x, y, width, height);
}

bool Rectangle::is_inside(int x, int y) const {
	int dx = abs(x - this->x);
	int dy = abs(y - this->y);
	return dx * 2 <= width && dy * 2 <= height;
}

void Rectangle::zoom(int factor) {
	height *= factor;
	width *= factor;
}
