#include "HuffmanTree.h"

void HuffmanTree::createBitCode(short index, BITS bitcode_)
{
	if (!HuffTree[index].isLeaf())
	{
		createBitCode(HuffTree[index].left, bitcode_ + 0);
		createBitCode(HuffTree[index].right, bitcode_ + 1);
	}
	else
		bitCode[index] = bitcode_;
}

bool HuffmanTree::countChar(const char * fileName)
{
	fstream inFile(fileName, ios::binary | ios::in);
	unsigned char tmp;
	inFile.read((char*)&tmp, 1);
	while (!inFile.eof())
	{
		HuffTree[tmp].increseFreq();
		inFile.read((char*)&tmp, 1);
	}

	inFile.close();
	return true;
}

void HuffmanTree::exportFeqTab(unsigned int F[])
{
	for (int i = 0; i < 256; i++)
		F[i] = HuffTree[i].getFreq();
}

void HuffmanTree::initFeqTab(unsigned int F[])
{
	for (int i = 0; i < 256; i++)
		HuffTree[i].increseFreq(F[i]);
}

void HuffmanTree::buildTree()
{
	PRIORITY_QUEUE<HuffmanNode> queue(MAX_NODE);
	int i;
	for (i = 0; i < 256; i++)
		if (HuffTree[i].getFreq() != 0)
			queue.insert(HuffTree[i]);

	HuffmanNode x, y;
	while (true)
	{
		queue.deleteMin(x);
		if (queue.deleteMin(y) == false)
			break;
		if (x < y)
			HuffTree[i].initNode(x.getChar(), x.getFreq() + y.getFreq(), x.getId(), y.getId(), i);
		else if (x > y)
			HuffTree[i].initNode(y.getChar(), x.getFreq() + y.getFreq(), y.getId(), x.getId(), i);

		queue.insert(HuffTree[i]);
		i++;
	}
	root = x.getId();
}

void HuffmanTree::createBitcode()
{
	BITS emptyBit;
	createBitCode(root, emptyBit);
}

bool HuffmanTree::getChar(BITS & bits, unsigned char & c)
{
	int index = root, i = 0;
	while (!HuffTree[index].isLeaf() && i < bits.size())
	{
		if (bits[i] == 0)
			index = HuffTree[index].left;
		else
			index = HuffTree[index].right;
		i++;
	}

	if (HuffTree[index].isLeaf())
	{
		c = index;
		bits.removeBit(i);
		return true;
	}
	else
		return false;
}

void HuffmanTree::huffTreeOut()
{

	for (int i = 0; i < MAX_NODE; i++)
	{
		if (HuffTree[i].getFreq() != 0)
		{
			if (i == root)
				cout << "Root : " << root << endl;
			else
				cout << "Index : " << i << endl;
			HuffTree[i].NodeOut();
			cout << endl;
		}
	}
}

void HuffmanTree::bitCodeOut()
{
	for (int i = 0; i < 256; i++)
		if (HuffTree[i].getFreq() != 0)
		{
			cout << i << " : "; 
			bitCode[i].toString();
			cout << endl;
		}
}
