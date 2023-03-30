#include "bin_manip.h"
#include <fstream>
#include <cstring>

namespace bman {

	write_le_int32::write_le_int32(int x) {
		val = x;
	}

	std::ofstream& operator<<(std::ofstream& out, const write_le_int32& w) {
		out.write((char*) &w.val, sizeof(w.val));
		return out;	
	}

	read_le_int32::read_le_int32(int& x) {
		val = (int*) &x;
	}

	std::ifstream& operator>>(std::ifstream& in, const read_le_int32& r) {
		in.read((char*) r.val, sizeof (*r.val));
		return in;
	}

	write_bool::write_bool(bool x) {
		val = x;
	}

	std::ofstream& operator<<(std::ofstream& out, const write_bool& w) {
		out.write((char*) &w.val, sizeof(w.val));
		return out;	
	}

	read_bool::read_bool(bool& x) {
		val = (bool*) &x;
	}

	std::ifstream& operator>>(std::ifstream& in, const read_bool& r) {
		in.read((char*) r.val, sizeof (*r.val));
		return in;
	}

	write_c_str::write_c_str(char* c) {
		val = c;
	}

	std::ofstream& operator<<(std::ofstream& out, const write_c_str& w) {
		for (size_t i = 0; i <= strlen(w.val); ++i) {
            out.write((char *) &(w.val[i]), sizeof(w.val[i]));
 
            if (w.val[i] == '\0')
                break;
        }
        return out;
	}

	read_c_str::read_c_str(char*& c, size_t size) {
		val = &c;
		sz = size;
	}

	std::ifstream &operator>>(std::ifstream &in, const read_c_str &x) {
        delete[] *x.val;
 	
        *x.val = new char[x.sz];
        std::fill(*x.val, *x.val + x.sz, '\0');
 
        for (size_t i = 0; i < x.sz; ++i) {
            char c;
            in.read((char *) &c, sizeof(c));
            (*x.val)[i] = c;
 
            if (c == '\0')
                break;
        }
 
        return in;
    }
}