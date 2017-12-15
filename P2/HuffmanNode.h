#pragma once
#include <iostream>
using namespace std;

class HuffmanNode
{
private:
	unsigned char c;
	unsigned int freq;

	short id;
public:
	short left, right; //nút lá có child left, right = -1
	HuffmanNode()
	{
		freq = 0;
		left = right = -1;
	}
	bool operator < (HuffmanNode node);
	bool operator > (HuffmanNode node);
	bool isLeaf();
	void initNode(unsigned char ch, unsigned int frq, short l, short r, short idx);
	unsigned char getChar();
	unsigned int getFreq();
	short getId();
	void setChar(unsigned char ch);
	void increseFreq(int k = 1);
	void NodeOut();
};