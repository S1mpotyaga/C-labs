#include "employees.h"
#include "bin_manip.h"

namespace emp {

	Employee::~Employee() {}

	std::ostream& operator<<(std::ostream& out, const Employee& e) {
		e.print(out);
		return out; 
	}

	std::istream& operator>>(std::istream& in, Employee& e) {
		e.input(in);
		return in;
	}

	std::ofstream& operator<<(std::ofstream& out, const Employee& e) {
		e.printFile(out);
		return out; 
	}

	std::ifstream& operator>>(std::ifstream& in, Employee& e) {
		e.inputFile(in);
		return in;
	}

	Developer::~Developer() {}

	void Developer::print(std::ostream& out) const {
		out << "Developer\n";
		out << "Name: " << _name << '\n';
		out << "Base Salary: " << _base_salary << '\n';
		out << "Has bonus: " << (_has_bonus ? '+' : '-') << '\n'; 
	}

	void Developer::input(std::istream& in) {
		in >> _name >> _base_salary >> _has_bonus;
	}

	void Developer::printFile(std::ofstream& out) const {
		out << bman::write_le_int32((int)1);
		out << bman::write_c_str((char*)_name.c_str());
		out << bman::write_le_int32(_base_salary);
		out << bman::write_bool(_has_bonus); 
	}

	void Developer::inputFile(std::ifstream& in) {
		char* tmp = new char[MAX_NAME_LENGHT + 1];
		in >> bman::read_c_str(tmp, MAX_NAME_LENGHT);
		_name = std::string(tmp);
		delete[] tmp;
		in >> bman::read_le_int32(_base_salary);
		in >> bman::read_bool(_has_bonus);
	}

	SalesManager::~SalesManager() {}

	void SalesManager::print(std::ostream& out) const {
		out << "Sales Manager\n";
		out << "Name: " << _name << '\n';
		out << "Base Salary: " << _base_salary << '\n';
		out << "Sold items: " << _sold_nm<< '\n';
		out << "Item price: " << _price << '\n'; 
	}

	void SalesManager::input(std::istream& in) {
		in >>  _name >> _base_salary >> _sold_nm >> _price;
	}

	void SalesManager::printFile(std::ofstream& out) const {
		out << bman::write_le_int32((int)2);
		out << bman::write_c_str((char*)_name.c_str());
		out << bman::write_le_int32(_base_salary);
		out << bman::write_le_int32(_sold_nm);
		out << bman::write_le_int32(_price); 
	}

	void SalesManager::inputFile(std::ifstream& in) {
		char* tmp = nullptr;
		in >> bman::read_c_str(tmp, MAX_NAME_LENGHT);
		_name = std::string(tmp);
		delete[] tmp;
		in >> bman::read_le_int32(_base_salary);
		in >> bman::read_le_int32(_sold_nm);
		in >> bman::read_le_int32(_price);
	}

	EmployeesArray::~EmployeesArray() {
		for (size_t i = 0; i < _employees.size(); i++) {
			delete _employees[i];
		}
	}

	void EmployeesArray::add(const Employee *e) {
		_employees.push_back((Employee*)e);
	}

	int EmployeesArray::total_salary() const {
		int answer = 0;
		for (Employee* e : _employees) {
			answer += e->salary();
		}
		return answer;
	}

	std::ostream& operator<< (std::ostream& out, const EmployeesArray& e) {
		for (size_t i = 0; i < e._employees.size(); i++) {
			out << i + 1 << ". " << *e._employees[i];
		}
		out << "== Total salary: " << e.total_salary() << '\n';
		out << '\n';
		return out;
	}

	std::ofstream& operator<< (std::ofstream& out, const EmployeesArray& e) {
		int n = e._employees.size();
		out << bman::write_le_int32(n);
		for (int i = 0; i < n; i++) {
			out << *e._employees[i];
		}
		return out;
	}
}