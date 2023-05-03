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

	HuffmanNode(size_t frequency, HuffmanNode* left = nullptr,
		HuffmanNode* right = nullptr, HuffmanNode* parent = nullptr, bool edge = false);

	bool operator< (const HuffmanNode& node) const; 
	bool operator== (const HuffmanNode& node) const;
	bool operator!= (const HuffmanNode& node) const;

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

std::ostream& operator<< (std::ostream& out, const HuffmanNode& node);

void combine(HuffmanNode* parent, HuffmanNode* left, HuffmanNode* right);

const size_t SYMB_COUNT = 256;
const size_t ADDITION = 128;

size_t fromCharToInt(char c);
char fromIntToChar(size_t x);

class HuffmanTree{
private:
	std::vector<HuffmanNode*> nodes;
	int codeId[SYMB_COUNT]; // IDs of the leafs for symbols
	int rootId;
public:

	HuffmanTree(size_t (&cnt)[SYMB_COUNT]);

	~HuffmanTree();
	HuffmanNode* getRoot() const;

	std::vector<bool> getCode(char c) const;
};

void printTree(HuffmanNode* node);

const size_t CHAR_SIZE = sizeof(uint8_t) * 8;
const size_t MAX_COUNT = 5 * (1 << 20) + 10;

class MyBigString{
private:
	char* ptr_;
	size_t size_;
public:

	MyBigString();
	~MyBigString();

	size_t size() const;
	const char* ptr() const;
	char operator[] (size_t i) const;
	
	void operator+=(char c);
	void read(std::ifstream& in);
};

class BitString{
private:
	uint8_t value_;
	std::string result_;
	int bitNumber_;
public:
	BitString();
	const char* result() const;
	int bitNumber() const;
	size_t size() const;

	void addBit(bool b);
	void finish();
};

class HuffmanArchiver {
private:
	size_t count[SYMB_COUNT];

	void build(const MyBigString& text);
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
/*
my tree:
node: 32 freq: 9
left for 32:
node: 30 freq: 4
symbol: c
end node 30
right for 32:
node: 31 freq: 5
left for 31:
node: 28 freq: 2
symbol: a
end node 28
right for 31:
node: 29 freq: 3
symbol: b
end node 29
end node 31
end node 32
*/