#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/huffman.h"

#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

#define IN_DIR "test/testInFiles/"
#define OUT_DIR "test/testOutFiles/"

//MyBigString tests begin

TEST_CASE("myBigString operator+= test") {
	HuffmanCode::MyBigString str;
	str += 'a';
	CHECK(str.size() == 1);
	str += 'b';
	CHECK(str.size() == 2);

	CHECK(str[0] == 'a');
	CHECK(str[1] == 'b');
}

TEST_CASE("myBigString read test") {
	HuffmanCode::MyBigString str;

	const std::string PATH = IN_DIR "text.txt";

	std::ifstream in;
	in.open(PATH);

	std::ifstream inCopy;
	inCopy.open(PATH);

	CHECK(in.good());

	str.read(in);

	std::string text;
	inCopy >> text;

	CHECK(str.size() == text.size());
	CHECK(std::strcmp(str.ptr(), text.c_str()) == 0);
}

//MyBigString tests end

//bitString tests begin

TEST_CASE("BitString test") {
	HuffmanCode::BitString str;

	for (size_t i = 0; i < HuffmanCode::CHAR_SIZE; ++i) {
		str.addBit(0);
		CHECK(str.bitNumber() == i + 1);
		CHECK(str.size() == 0);
	}
	str.addBit(0);
	CHECK(str.bitNumber() == 1);
	CHECK(str.size() == 1);
}

//bitString tests end

//HuffmanNode tests begin

TEST_CASE("HuffmanNode operator< test") {
	HuffmanCode::HuffmanNode zeroFreq(0);
	HuffmanCode::HuffmanNode oneFreqFirst(1);
	HuffmanCode::HuffmanNode oneFreqSecond(1);

	CHECK(zeroFreq < oneFreqFirst);
	CHECK(zeroFreq < oneFreqSecond);

	bool isSecondGreater = (oneFreqFirst < oneFreqSecond);

	bool isFirstGreater = (oneFreqSecond < oneFreqFirst);

	CHECK((isFirstGreater ^ isSecondGreater) == 1);
}

TEST_CASE("HuffmanNode madeTerminate test") {
	HuffmanCode::HuffmanNode parent(0);
	HuffmanCode::HuffmanNode left(0);
	HuffmanCode::HuffmanNode right(0);

	SUBCASE("without childs") {
		char symb = 'a';
		parent.madeTerminate(symb);
		CHECK(parent.symbol() == symb);
		CHECK(parent.isTerminate());
	}

	SUBCASE("with left child") {
		HuffmanCode::combine(&parent, &left, nullptr);
		CHECK_THROWS_AS(
			parent.madeTerminate('a'),
			const HuffmanCode::MyException&
		);
	}

	SUBCASE("with right child") {
		HuffmanCode::combine(&parent, nullptr, &right);
		CHECK_THROWS_AS(
			parent.madeTerminate('a'),
			const HuffmanCode::MyException&
		);
	}
}

TEST_CASE("HuffmanNode symbol test") {
	HuffmanCode::HuffmanNode node(0);

	SUBCASE("correct symbol") {
		char c = 'a';
		node.madeTerminate(c);
		CHECK(node.symbol() == c);
	}

	SUBCASE("Uncorrect symbol") {
		CHECK_THROWS_AS(node.symbol(), const HuffmanCode::MyException&);
	}
}

TEST_CASE("combine test") {
	HuffmanCode::HuffmanNode parent(0);
	HuffmanCode::HuffmanNode left(3);
	HuffmanCode::HuffmanNode right(5);

	#define CHECK_LEFT CHECK(left.parent == &parent); CHECK(left.edge == false)

	#define CHECK_RIGHT CHECK(right.parent == &parent); CHECK(right.edge == true)

	#define CHECK_PARENT(lef, rig) CHECK(parent.left == lef); CHECK(parent.right == rig)

	SUBCASE("left node is null") {
		HuffmanCode::combine(&parent, nullptr, &right);
		
		CHECK_PARENT(nullptr, &right);
		CHECK_RIGHT;
	}

	SUBCASE("right node is null") {
		HuffmanCode::combine(&parent, &left, nullptr);
		
		CHECK_PARENT(&left, nullptr);
		CHECK_LEFT;
	}

	SUBCASE("both nodes exist") {
		HuffmanCode::combine(&parent, &left, &right);
		CHECK_PARENT(&left, &right);
		CHECK_LEFT;
		CHECK_RIGHT;
	}
}

//HuffmanNode tests end

//HuffmanTree tests begin

bool compareTries(HuffmanCode::HuffmanNode* firstNode, HuffmanCode::HuffmanNode* secondNode) {
	if (firstNode == secondNode && secondNode == nullptr) return true;

	if (firstNode == nullptr || secondNode == nullptr) return false;
	

	if ((*firstNode) != (*secondNode)) {
		std::cout << "first node:" << std::endl;
		std::cout << (*firstNode);
		std::cout << "second node:" << std::endl;
		std::cout << (*secondNode);
		return false;
	}
	return (compareTries(firstNode->left, secondNode->left) &&
			compareTries(firstNode->right, secondNode->right));
}

TEST_CASE("HuffmanTree test") {
	size_t cnt[HuffmanCode::SYMB_COUNT];
	std::fill(cnt, cnt + HuffmanCode::SYMB_COUNT, 0);
	const int A_FREQ = 2;
	const int B_FREQ = 3;
	const int C_FREQ = 4;
	cnt[HuffmanCode::fromCharToInt('a')] = A_FREQ;
	cnt[HuffmanCode::fromCharToInt('b')] = B_FREQ;
	cnt[HuffmanCode::fromCharToInt('c')] = C_FREQ;

	HuffmanCode::HuffmanTree tree(cnt);

	SUBCASE ("Tree structure test") {

		HuffmanCode::HuffmanNode a(A_FREQ);
		a.madeTerminate('a');

		HuffmanCode::HuffmanNode b(B_FREQ);
		b.madeTerminate('b');

		HuffmanCode::HuffmanNode c(C_FREQ);
		c.madeTerminate('c');

		HuffmanCode::HuffmanNode ab(a.frequency + b.frequency);
		HuffmanCode::combine(&ab, &a, &b);

		HuffmanCode::HuffmanNode cab(c.frequency + ab.frequency);
		HuffmanCode::combine(&cab, &c, &ab);

		HuffmanCode::HuffmanNode* root = tree.getRoot();

		CHECK(compareTries(&cab, root));
	}

	SUBCASE("getCode test") {

		HuffmanCode::HuffmanTree tree(cnt);

		std::vector<bool> aPath = {1, 0};
		std::vector<bool> bPath = {1, 1};
		std::vector<bool> cPath = {0};

		CHECK(tree.getCode('a') == aPath);
		CHECK(tree.getCode('b') == bPath);
		CHECK(tree.getCode('c') == cPath);
	}		
}


//HuffmanTree tests end

//HuffmanArchiver tests begin

bool compareFiles(const std::string& p1, const std::string& p2) {
 	std::ifstream in1(p1, std::ios::binary|std::ios::in);
 	std::ifstream in2(p2, std::ios::binary|std::ios::in);

 	if (in1.fail() || in2.fail()) {
		return false;
 	}

 	char c1, c2;
 	while (true) {
 		in1.read(&c1, sizeof(c1));
 		in2.read(&c2, sizeof(c2));
 		if (in1.good() != in2.good()) return false;
 		if (!in1.good()) break;
 		if (c1 != c2) return false;
 	}
 	return true;
}

void testFiles (const std::string& INPUT_PATH,
			    const std::string& COMPRESSED_PATH,
			    const std::string& DECOMPRESSED_PATH)
{
	std::ifstream in;
	std::ofstream compressedOut;

	in.open(INPUT_PATH);
	compressedOut.open(COMPRESSED_PATH);

	CHECK(in.good());
	CHECK(compressedOut.good());

	HuffmanCode::HuffmanArchiver archiver;

	archiver.compress(in, compressedOut);

	in.close();
	compressedOut.close();

	std::ifstream compressedIn;
	std::ofstream decompressedOut;

	compressedIn.open(COMPRESSED_PATH);
	decompressedOut.open(DECOMPRESSED_PATH);

	CHECK(compressedIn.good());
	CHECK(decompressedOut.good());

	archiver.decompress(compressedIn, decompressedOut);

	compressedIn.close();
	decompressedOut.close();

	CHECK(compareFiles(INPUT_PATH, DECOMPRESSED_PATH));
}

TEST_CASE("HuffmanArchiver test text") {

	testFiles(IN_DIR "text.txt",
			  OUT_DIR "compressedText.txt",
			  OUT_DIR "decompressedText.txt"
			  );
}

TEST_CASE("HuffmanArchiver test picture") {
	testFiles(IN_DIR "lena_512.bmp",
			  OUT_DIR "lenaCompressed.out",
			  OUT_DIR "lenaDecompressed.bmp");
}

// HuffmanArchiver tests end