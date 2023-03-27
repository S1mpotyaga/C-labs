#include "Circle.hpp"
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "Figure.hpp"

Circle::Circle(int id, int x, int y, int radius, const char* label): Figure(id, x, y) {
	this->radius = radius;
	this->label = new char[strlen(label) + 1];
	strcpy(this->label, label);
}

Circle::~Circle() {
	delete[] this->label;
}

void Circle::print() const {
	printf("Circle %d: x = %d y = %d radius = %d label = %s\n", 
		id, x, y, radius, label);
}

int square_dist(int x1, int y1, int x2, int y2) {
	int dx = x1 - x2;
	int dy = y1 - y2;
	return dx * dx + dy * dy;
}

bool Circle::is_inside(int x, int y) const {
	return square_dist(x, y, this->x, this->y) <= radius * radius;
}

void Circle::zoom(int factor) {
	radius *= factor;
}