#include "HuffmanNode.h"

bool HuffmanNode::operator < (HuffmanNode node)
{
	if (this->freq == node.freq)
		return this->c < node.c;
	return this->freq < node.freq;
}

bool HuffmanNode::operator>(HuffmanNode node)
{
	if (this->freq == node.freq)
		return this->c > node.c;
	return this->freq > node.freq;
}

bool HuffmanNode::isLeaf()
{
	return this->left == -1 && this->right == -1;
}

void HuffmanNode::initNode(unsigned char ch, unsigned int frq, short l, short r, short idx)
{
	c = ch;
	freq = frq;
	left = l;
	right = r;
	id = idx;
}

unsigned char HuffmanNode::getChar()
{
	return c;
}

unsigned int HuffmanNode::getFreq()
{
	return freq;
}

short HuffmanNode::getId()
{
	return id;
}

void HuffmanNode::setChar(unsigned char ch)
{
	c = ch;
}

void HuffmanNode::increseFreq(int k)
{
	freq += k;
}

void HuffmanNode::NodeOut()
{
	cout << c << ":" << freq << endl;
	cout << left << "|" << right << endl;
}
