#pragma once
#include <fstream>

namespace bman {

	class write_le_int32 {
	public:
		int val;
		explicit write_le_int32(int x);
	
		friend std::ofstream& operator<<(std::ofstream& out, const write_le_int32& w);
	};

	
	class read_le_int32 {
    public:
        int *val;
 
        explicit read_le_int32(int &ptr);
 
        friend std::ifstream &operator>>(std::ifstream &in, const read_le_int32 &r);
    };

	class write_bool {
	public:
		bool val;

		explicit write_bool(bool b);

		friend std::ofstream& operator<<(std::ofstream& out, const write_bool& w);
	};


	class read_bool {
	public:
		bool* val;
		explicit read_bool(bool& b);

		friend std::ifstream& operator>>(std::ifstream& in, const read_bool& r);
	};


	class write_c_str {
	public:
		char* val;
		explicit write_c_str(char *c);
	
		friend std::ofstream& operator<<(std::ofstream& out, const write_c_str& w);
	};

	
	class read_c_str {
	public:
		char** val;
		size_t sz;
		read_c_str(char*& c, size_t size);

		friend std::ifstream& operator>>(std::ifstream& in, const read_c_str& r);
	};

}