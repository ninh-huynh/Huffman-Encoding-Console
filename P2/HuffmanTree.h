#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define MAX_NODE 511
#include"HuffmanNode.h"
#include"PriorityQueue.cpp"
#include"Bits.h"

class HuffmanTree
{
private:
	short root;
	HuffmanNode HuffTree[MAX_NODE];
	//string bitCode[256];
	BITS bitCode[256];
	//void createBitCode(short index, string bitcode_);
	void createBitCode(short index, BITS bitcode_);
public:
	HuffmanTree()
	{
		for (int i = 0; i < 256; i++)
			HuffTree[i].initNode(i, 0, -1, -1, i);
	}
	bool countChar(const char *fileName);
	void exportFeqTab(unsigned int F[]);
	void initFeqTab(unsigned int F[]);
	void buildTree();
	void createBitcode();
	/*string getBitCode(const unsigned char c)
	{
		return bitCode[c];
	}*/
	BITS getBitCode(const unsigned char c)
	{
		return bitCode[c];
	}
	//bool getChar(string &bitNum, unsigned char &c);
	bool getChar(BITS &bits, unsigned char &c);
	void huffTreeOut();
	void bitCodeOut();
};