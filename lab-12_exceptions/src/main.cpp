#include "matrix.h"
#include <iostream>

#include <string>

int inputReq() {
	char c;
	std::cin >> c;
	int req;
	std::cin >> req;
	return req;
}

int main() {

	const int N = 10;

	std::string command;

	Matrix* matrices = new Matrix[N];

	while (std::cin >> command) {
		if (command == "load") {
			int i = inputReq();
			std::string fileName;
			std::cin >> fileName;
			try {
				matrices[i].load(fileName);
			} catch(const MatrixException& e) {
				std::cout << e.what() << '\n';
			}
		} else if (command == "print") {
			int i = inputReq();
			std::cout << matrices[i];
		} else if (command == "add") {
			int i = inputReq();
			int j = inputReq();
			try {
				matrices[i] += matrices[j];
			} catch (const MatrixException& e) {
				std::cout << e.what() << '\n';
			}
		} else if (command == "mul") {
			int i = inputReq();
			int j = inputReq();
			try {
				matrices[i] *= matrices[j];
			} catch(const MatrixException& e) {
				std::cout << e.what() << '\n';
			}
		} else if (command == "elem") {
			int i = inputReq();
			int row, col;
			std::cin >> row >> col;
			try {
				std::cout << matrices[i].get(row, col) << '\n';
			} catch (const MatrixException& e) {
				std::cout << e.what() << '\n';
			}
		} else if (command == "exit") {
			break;
		}
	}

	delete[] matrices;

	return 0;
}