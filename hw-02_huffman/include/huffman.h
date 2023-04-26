#pragma once	
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>

namespace HuffmanCode{

class HuffmanNode {
public:
	size_t frequency;
	HuffmanNode* left; //go by zero
	HuffmanNode* right; //go by one
	HuffmanNode* parent;
	bool edge; //false if gone by 0, true if 1

	HuffmanNode(size_t frequency, HuffmanNode* leftId,
		HuffmanNode* rightId, HuffmanNode* parentId, bool edge);

	bool operator< (const HuffmanNode& node) const; 

	void madeTerminate(char c);

	char symbol() const;
	bool isTerminate() const;
	size_t id() const;

private:
	static size_t nextId;
	char symbol_; //correct only if isTerminate true
	bool isTerminate_;
	size_t id_;
};

void combine(HuffmanNode* parent, HuffmanNode* left, HuffmanNode* right);



const size_t SYMB_COUNT = 256;

class HuffmanTree{
private:
	std::vector<HuffmanNode*> nodes;
	int codeId[SYMB_COUNT]; // IDs of the leafs for symbols
	int rootId;
public:

	template<size_t N>
	HuffmanTree(size_t (&cnt)[N]);
	~HuffmanTree();
	HuffmanNode* getRoot() const;

	std::vector<bool> getCode(const char c) const;
};

const size_t CHAR_SIZE = 8;

class BitString{
private:
	uint8_t value_;
	int bitNumber_;
	std::string result_;
public:
	BitString();
	std::string result() const;
	int bitNumber() const;

	void addBit(bool b);
	void finish();
};

class HuffmanArchiver {
private:
	const size_t MAX_COUNT = 5 * 1000 * 1000 + 10;
	size_t count[SYMB_COUNT];

	void build(const std::string& s);
public:
	HuffmanArchiver() = default;

	void compress(std::ifstream& in, std::ofstream& out);
	void decompress(std::ifstream& in, std::ofstream& out);
};

class MyException : std::exception{
private:
    std::string error;
public:
    MyException(std::string s);

    virtual const char* what() const noexcept;
};

}