#include "huffman.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>

namespace HuffmanCode{

size_t HuffmanNode::nextId = 0;

HuffmanNode::HuffmanNode(size_t frequency, HuffmanNode* left,
	HuffmanNode* right, HuffmanNode* parent, bool edge):
frequency(frequency), left(left), right(right), parent(parent), edge(edge) {
	symbol_ = '\0';
	isTerminate_ = false;
	id_ = nextId++;
}

size_t HuffmanNode::id() const {
	return id_;
}

bool HuffmanNode::operator< (const HuffmanNode& node) const {
	if (frequency != node.frequency) return frequency < node.frequency;
	return id_ < node.id_;
}


bool HuffmanNode::operator== (const HuffmanNode& node) const {
	if (frequency != node.frequency) return false;
	if (isTerminate_ != node.isTerminate_) return false;
	if (isTerminate_ && symbol_ != node.symbol_) return false;
	return edge == node.edge;
}

bool HuffmanNode::operator!= (const HuffmanNode& node) const {
	return !(*this == node);
}

void HuffmanNode::madeTerminate(char c) {
	if (left || right) throw MyException("Incorrect: can'r made node terminate");
	symbol_ = c;
	isTerminate_ = true;
}

char HuffmanNode::symbol() const {
	if (!isTerminate_) throw MyException("Error: call symbol, when node is not terminate");
	return symbol_;
}

bool HuffmanNode::isTerminate() const {
	return isTerminate_;
}

std::ostream& operator<< (std::ostream& out, const HuffmanNode& node) {
	std::cout << "node: " << node.id() << " freq: " << node.frequency << std::endl;
	if (node.isTerminate()) {
		std::cout << "symbol: " << node.symbol() << std::endl;
	}
	return out;
}

void combine(HuffmanNode* parent, HuffmanNode* left, HuffmanNode* right) {
	parent->left = left;
	if (left) {
		left->parent = parent;
		left->edge = false;
	}

	parent->right = right;
	if (right) {
		right->parent = parent;
		right->edge = true;
	}
}

size_t fromCharToInt(char c) {
	return static_cast<size_t> (c) + ADDITION;
}

char fromIntToChar(size_t x) {
	return static_cast<char>(x - ADDITION);
}

struct HuffmanNodeCompare {
	bool operator() (HuffmanNode* first, HuffmanNode* second) {
		return (*second) < (*first);
	}
};

HuffmanTree::HuffmanTree(size_t (&cnt)[SYMB_COUNT]) {
	rootId = -1;
	std::fill(codeId, codeId + SYMB_COUNT, -1);
	int notZeroCount = 0;
	for (size_t i = 0; i < SYMB_COUNT; i++) {
		if (cnt[i] != 0) notZeroCount++;
	}

	nodes.reserve(std::max(0, notZeroCount * 2 - 1));

	std::priority_queue<HuffmanNode*,
						std::vector<HuffmanNode*>,
						HuffmanNodeCompare > queue;
	
	for (size_t i = 0; i < SYMB_COUNT; i++) {
		if (cnt[i] == 0) continue;
		HuffmanNode* node = new HuffmanNode(cnt[i]);
		node->madeTerminate(fromIntToChar(i));
		queue.push(node);
		nodes.push_back(node);
		codeId[i] = static_cast<int>(nodes.size()) - 1;
	}
	if (queue.size() == 1) {
		HuffmanNode* lonely = nodes.back();
		HuffmanNode* node = new HuffmanNode(lonely->frequency);
		nodes.push_back(node);
		combine(node, lonely, nullptr);
	}

	while (queue.size() > 1) {
		const HuffmanNode* left = queue.top();
		queue.pop();
		const HuffmanNode* right = queue.top();
		queue.pop();
		HuffmanNode* node = new HuffmanNode(left->frequency + right->frequency);



		combine(node, const_cast<HuffmanNode*> (left), const_cast<HuffmanNode*> (right));

		queue.push(node);
		nodes.push_back(node);
	}
	rootId = static_cast<int>(nodes.size()) - 1;
}

HuffmanTree::~HuffmanTree() {
	for (size_t i = 0; i < nodes.size(); i++) 
		delete nodes[i];
}

HuffmanNode* HuffmanTree::getRoot() const {
	return nodes[rootId];
}

std::vector<bool> HuffmanTree::getCode(char c) const{
	std::vector<bool> result;
	int index = codeId[fromCharToInt(c)];
	HuffmanNode* node = nodes[index];
	while (node->parent != nullptr) {
		result.push_back(node->edge);
		node = node->parent;
	}
	std::reverse(result.begin(), result.end());
	return result;
}


void printTree(HuffmanNode* node) {
	if (!node) return;
	std::cout << (*node);
	if (node->left) {
		std::cout << "left for " << node->id() << ":" << std::endl;
		printTree(node->left);
	}
	if (node->right) {
		std::cout << "right for " << node->id() << ":" << std::endl;
		printTree(node->right);
	}
	std::cout << "end node " << node->id() << std::endl;
}

MyBigString::MyBigString() {
	ptr_ = new char[MAX_COUNT];
	size_ = 0;
}

MyBigString::~MyBigString() {
	delete[] ptr_;
}

size_t MyBigString::size() const {
	return size_;
}

const char* MyBigString::ptr() const {
	return static_cast<const char*> (ptr_);
}

char MyBigString::operator[] (size_t i) const {
	return ptr_[i];
}

void MyBigString::operator+=(char c) {
	if (size_ == MAX_COUNT) throw MyException("Too long string!");
	ptr_[size_] = c;
	size_++;
}

void MyBigString::read(std::ifstream& in) {
	in.read(ptr_, MAX_COUNT);
	size_ = in.gcount();
}

BitString::BitString() {
	result_ = "";
	value_ = 0;
	bitNumber_ = 0;
}

const char* BitString::result() const {
	return result_.c_str();
}

int BitString::bitNumber() const {
	return bitNumber_;
}

size_t BitString::size() const {
	return result_.size();
}


void BitString::addBit(bool b) {
	if (bitNumber_ == CHAR_SIZE) {
		result_ += static_cast<char> (value_);
		value_ = 0;
		bitNumber_ = 0;
	}
	value_ ^= (static_cast<uint8_t>(b) << bitNumber_);
	++bitNumber_;
}

void BitString::finish() {
	result_ += static_cast<char> (value_);
}

void HuffmanArchiver::build(const MyBigString& text) {
	std::fill(count, count + SYMB_COUNT, 0);
	for (size_t i = 0; i < text.size(); i++) {
		size_t index = fromCharToInt(text[i]);
		count[index]++;
	}
}

void HuffmanArchiver::compress(std::ifstream& in, std::ofstream& out){
	MyBigString text;

	text.read(in);

	std::cout << text.size() << '\n';

	if (text.size() == 0) {
		std::cout << 0 << '\n';
		std::cout << 0 << '\n';
		return;
	}
	build(text);
	HuffmanTree tree(count);

	BitString bitString;

	for (size_t i = 0; i < text.size(); i++) {
		for (bool b : tree.getCode(text[i])) {
			bitString.addBit(b);
		}
	}

	bitString.finish();

	std::vector<std::pair<char, size_t> > countWithoutZeroes;

	for (size_t i = 0; i < SYMB_COUNT; i++) {
		if (count[i] != 0)
			countWithoutZeroes.push_back(
				std::make_pair(fromIntToChar(i), count[i])
			);
	}

	size_t countSize = countWithoutZeroes.size();

	out.write(reinterpret_cast<char*>(&countSize), sizeof(countSize));

	for (size_t i = 0; i < countSize; i++) {
		out.write(&countWithoutZeroes[i].first,
			sizeof(countWithoutZeroes[i].first));

		out.write(reinterpret_cast<char*>(&countWithoutZeroes[i].second),
			sizeof(countWithoutZeroes[i].second));

	}

	int bitNum = bitString.bitNumber();

	out.write(reinterpret_cast<char*>(&bitNum), sizeof(bitNum));
	
	const char* result = bitString.result();

	
	for (size_t i = 0; i < bitString.size(); i++) {
		out.write(result + i, sizeof(char));
	}
	
	std::cout << bitString.size() << '\n';
	std::cout << sizeof(countSize) + countSize * (sizeof(char) + sizeof(size_t)) + sizeof(bitNum) << '\n';
}

void HuffmanArchiver::decompress(std::ifstream& in, std::ofstream& out) {
	MyException dataException("Incorrect input data");
	size_t countSize;
	
	in.read(reinterpret_cast<char*>(&countSize), sizeof(countSize));
	
	if (!in.good()) {
		std::cout << 0 << '\n';
		std::cout << 0 << '\n';
		std::cout << 0 << '\n';
		return;
	}

	std::fill(count, count + SYMB_COUNT, 0);

	for (size_t i = 0; i < countSize; i++) {
		char c;
		
		in.read(&c, sizeof(c));
		if (!in.good()) throw dataException;
		
		size_t pos = fromCharToInt(c);
		
		in.read(reinterpret_cast<char*>(count + pos), sizeof(count[pos]));
		if (!in.good()) throw dataException;
	}
	int lastBitNumber = 0;
	in.read((char*)&lastBitNumber, sizeof(lastBitNumber));
	if (!in.good()) throw dataException;
	MyBigString compressed;
	char tmp;
	while (true) {
		in.read(&tmp, sizeof(tmp));
		if (!in.good()) break;
		compressed += tmp;
	}

	std::cout << compressed.size() << '\n';
	
	HuffmanTree tree(count);
	MyBigString result; 

	HuffmanNode* node = tree.getRoot();
	for (size_t i = 0; i < compressed.size(); i++) {
		size_t m = (i + 1 == compressed.size() ? lastBitNumber : CHAR_SIZE);
		for (size_t j = 0; j < m; j++) {
			bool b = ((static_cast<uint8_t>(compressed[i]) >> j) & 1);
			if (b) node = node->right;
			else node = node->left;
			if (node->isTerminate()) {
				result += node->symbol();
				node = tree.getRoot();
			}
		}
	}
	
	out.write(result.ptr(), result.size());

	std::cout << result.size() << '\n';
	std::cout << sizeof(countSize) + countSize * (sizeof(char) + sizeof(size_t)) + sizeof(lastBitNumber) << '\n';
}

MyException::MyException(std::string s) {
	error = s;
}

const char* MyException::what() const noexcept {
	return error.c_str();
}

}