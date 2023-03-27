#include "Figure.hpp"

Figure::Figure(int id, int x, int y) {
	this->id = id;
	this->x = x;
	this->y = y;
}

Figure::~Figure() {}

int Figure::getId() const {
	return id;
}

int Figure::getX() const {
	return x;
}

int Figure::getY() const {
	return y;
}