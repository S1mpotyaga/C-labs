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
samples/sample1.txt
samples/sampleOut.txt
*/