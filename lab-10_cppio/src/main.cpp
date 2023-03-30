#include "employees.h"
#include "bin_manip.h"
#include <iostream>
#include <fstream>

int main() {

	std::string type;
	std::string file_name;

	emp::EmployeesArray e;

	while (std::cin >> type) {
		if (type == "exit") {
			break;
		}
		else if (type == "load") {
			std::cin >> file_name;

			std::ifstream in(file_name, std::ios::binary);
			
			int n;
			int type;

			in >> bman::read_le_int32(n);
			for (int i = 0; i < n; i++) {
				in >> bman::read_le_int32(type);
				if (type == 1) {
					emp::Developer* d = new emp::Developer();
					in >> *d;
					e.add(d);
				} else if (type == 2) {
					emp::SalesManager* s = new emp::SalesManager();
					in >> *s;
					e.add(s);
				}
			}
			in.close();
		} else if (type == "save") {
			std::cin >> file_name;
			std::ofstream out(file_name, std::ios::binary);
			out << e;
			out.close();
		} else if (type == "add") {
			int empType = -1;
			std::cin >> empType;

			if (empType == 1) {
				emp::Developer* d = new emp::Developer();
				std::cin >> *d;
				e.add(d);
			} else if (empType == 2) {
				emp::SalesManager* s = new emp::SalesManager();
				std::cin >> *s;
				e.add(s);
			}
		} else if (type == "list") {
			std::cout << e;
		}
	}

	return 0;
}