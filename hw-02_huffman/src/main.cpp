#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "huffman.h"
#include <exception>

int main(int argc, char* argv[]) {

	bool isCompress = false;
	bool isDecompress = false;
	std::string fromPath = "";
	std::string toPath = "";
	std::string arg;
	for (int i = 1; i < argc; i++) {
		arg = std::string(argv[i]);
		if (arg == "-c") {
			if (isCompress) return -1;
			isCompress = true;
		} else if (arg == "-u") {
			if (isDecompress) return -1;
			isDecompress = true;
		} else if (arg == "-f" || arg == "--file") {
			if (fromPath != "" || i + 1 == argc) return -1;
			fromPath = argv[++i];
		} else if (arg == "-o" || arg == "--output") {
			if (toPath != "" || i + 1 == argc) return -1;
			toPath = argv[++i];
		} else return -1;
	}
	if ((isCompress ^ isDecompress) != true) return -1;
	if (fromPath == "" || toPath == "") return -1;

	std::ifstream in;
		
	in.open(fromPath);
	if (!in.good()) {
		return 0;
	}
	
	std::ofstream out;
	out.open(toPath, std::ios::binary|std::ios::out);
	if (!out.good()) {
		in.close();
		return 0;
	}

	HuffmanCode::HuffmanArchiver archiver;

	if (isCompress) {
		try {
			archiver.compress(in, out);
		} catch (const std::exception& e) {
			in.close();
			out.close();
			return 0;
		}
	} else {
		try {
			archiver.decompress(in, out);
		}
		catch (const HuffmanCode::MyException& e) {
			in.close();
			out.close();
			return 0;
		}
	}
}

/*
original tree:
node: 27 freq: 9
left for 27:
node: 25 freq: 4
symbol: c
end node 25
right for 27:
node: 26 freq: 5
left for 26:
node: 24 freq: 3
symbol: b
end node 24
right for 26:
node: 23 freq: 2
symbol: a
end node 23
end node 26
end node 27
*/