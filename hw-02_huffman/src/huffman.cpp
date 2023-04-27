#include "huffman.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>

namespace HuffmanCode{

size_t HuffmanNode::nextId = 0;

HuffmanNode::HuffmanNode(size_t frequency, HuffmanNode* left = nullptr,
	HuffmanNode* right = nullptr, HuffmanNode* parent = nullptr, bool edge = false):
frequency(frequency), left(left), right(right), parent(parent), edge(edge) {
	symbol_ = '\0';
	isTerminate_ = false;
	id_ = nextId++;
}

size_t HuffmanNode::id() const {
	return id_;
}

bool HuffmanNode::operator< (const HuffmanNode& node) const {
	if (frequency == node.frequency) return id() < node.id();
	return frequency < node.frequency;
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

template<size_t N>
HuffmanTree::HuffmanTree(size_t (&cnt)[N]) {
	if (N != SYMB_COUNT) throw std::length_error("Incorrect array length");
	rootId = -1;
	std::fill(codeId, codeId + SYMB_COUNT, -1);
	int notZeroCount = 0;
	for (size_t i = 0; i < SYMB_COUNT; i++) {
		if (cnt[i] != 0) notZeroCount++;
	}

	nodes.reserve(std::max(0, notZeroCount * 2 - 1));
	std::priority_queue<HuffmanNode*> queue;
	for (size_t i = 0; i < SYMB_COUNT; i++) {
		if (cnt[i] == 0) continue;
		HuffmanNode* node = new HuffmanNode(cnt[i]);
		node->madeTerminate(static_cast<char>(i - ADDITION));
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
	int index = codeId[static_cast<int> (c) + ADDITION];
	HuffmanNode* node = nodes[index];
	while (node->parent != nullptr) {
		result.push_back(node->edge);
		node = node->parent;
	}
	std::reverse(result.begin(), result.end());
	return result;
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

void MyBigString::add(char c) {
	if (size_ == MAX_COUNT) throw MyException("Too long string!");
	ptr_[size_] = c;
	size_++;
}

void MyBigString::read(std::ifstream& in) {
	in.read(ptr_, MAX_COUNT);
	size_ = in.gcount();
}

BitString::BitString() {
	value_ = 0;
	bitNumber_ = 0;
}

const char* BitString::result() const {
	return result_.ptr();
}

int BitString::bitNumber() const {
	return bitNumber_;
}

size_t BitString::size() const {
	return result_.size();
}


void BitString::addBit(bool b) {
	if (bitNumber_ == CHAR_SIZE) {
		result_.add(static_cast<char> (value_));
		value_ = 0;
		bitNumber_ = 0;
	}
	value_ ^= (static_cast<uint8_t>(b) << bitNumber_);
	++bitNumber_;
}

void printTree(HuffmanNode* node) {
	if (!node) return;
	std::cout << "node: " << node->id() << " freq: " << node->frequency << std::endl;
	if (node->isTerminate()) {
		std::cout << "symbol: " << node->symbol() << std::endl;
	}
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

void BitString::finish() {
	result_.add(static_cast<char> (value_));
}

void HuffmanArchiver::build(const MyBigString& text) {
	std::fill(count, count + SYMB_COUNT, 0);
	for (size_t i = 0; i < text.size(); i++) {
		int index = static_cast<int>(text[i]) + ADDITION;
		count[index]++;
	}
}

void HuffmanArchiver::compress(std::ifstream& in, std::ofstream& out){
	MyBigString text;

	text.read(in);

	std::cout << text.size() << '\n';

	build(text);
	HuffmanTree tree(count);

	printTree(tree.getRoot());

	BitString bitString;

	for (size_t i = 0; i < text.size(); i++) {
		for (bool b : tree.getCode(text[i])) bitString.addBit(b);
	}

	bitString.finish();

	for (size_t i = 0; i < SYMB_COUNT; i++) {
		out.write((char*) (count + i), sizeof(count[i]));
	}
	int bitNum = bitString.bitNumber();
	
	out.write((char*)(&bitNum), sizeof(bitNum));
	
	const char* result = bitString.result();

	
	out.write(result, bitString.size());
	
	std::cout << bitString.size() << '\n';
	std::cout << SYMB_COUNT + sizeof(bitNum) << '\n';
}

void HuffmanArchiver::decompress(std::ifstream& in, std::ofstream& out) {
	MyException dataException("Incorrect input data");
	for (size_t i = 0; i < SYMB_COUNT; i++) {
		in.read((char*)(count + i), sizeof(count[i]));
		if (!in.good()) {
			throw dataException;
		}
	}
	int lastBitNumber = 0;
	in.read((char*)&lastBitNumber, sizeof(lastBitNumber));
	if (!in.good()) throw dataException;
	MyBigString compressed;
	char tmp;
	while (true) {
		in.read(&tmp, sizeof(tmp));
		if (!in.good()) break;
		compressed.add(tmp);
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
				result.add(node->symbol());
				node = tree.getRoot();
			}
		}
	}
	
	out.write(result.ptr(), result.size());

	std::cout << result.size() << '\n';
	std::cout << SYMB_COUNT + sizeof(lastBitNumber) << '\n';
}

MyException::MyException(std::string s) {
	error = s;
}

const char* MyException::what() const noexcept {
	return error.c_str();
}

}