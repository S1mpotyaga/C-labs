#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace emp {

    const size_t MAX_NAME_LENGHT = 200;

    class Employee{
    protected:
        int32_t _base_salary;
        std::string _name;
    public:
        virtual ~Employee();
        
        virtual int salary() const = 0;
        
        virtual void print(std::ostream& out) const = 0;
        virtual void input(std::istream& in) = 0;
        
        virtual void printFile(std::ofstream& out) const = 0;
        virtual void inputFile(std::ifstream& in) = 0;
    };

    std::ostream& operator<<(std::ostream& out, const Employee& e);
    std::istream& operator>>(std::istream& in, Employee& e);

    std::ofstream& operator<<(std::ofstream& out, const Employee& e);
    std::ifstream& operator>>(std::ifstream& in, Employee& e);

    class Developer : public Employee {
    public:
        int salary() const override {
            int salary = _base_salary;
            if (_has_bonus) { salary += 1000; }
            return salary;
        }
      
        void print(std::ostream& out) const override;
        void input(std::istream& in) override;

        void printFile(std::ofstream& out) const override;
        void inputFile(std::ifstream& in) override;

        virtual ~Developer();


    private:
        bool _has_bonus;
    };

    class SalesManager : public Employee {
    public:
        int salary() const override {
            return _base_salary + _sold_nm * _price * 0.01;
        }

        void print(std::ostream& out) const override;
        void input(std::istream& in) override;

        void printFile(std::ofstream& out) const override;
        void inputFile(std::ifstream& in) override;

        virtual ~SalesManager();
    private:
        int32_t _sold_nm, _price;
    };

    class EmployeesArray {
    public:

        void add(const Employee *e);
        int total_salary() const;
        ~EmployeesArray();

        friend std::ostream& operator<< (std::ostream& out, const EmployeesArray& e);
        friend std::ofstream& operator<< (std::ofstream& out, const EmployeesArray& e);
    private:
        std::vector<Employee*> _employees;
    };

}

#endif
