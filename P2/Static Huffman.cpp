#define _CRT_SECURE_NO_WARNINGS
#include "Static Huffman.h"
#include"PriorityQueue.cpp"
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

void HuffmanTree::createBitCode(short index,string bitcode_)
{	
	if (!HuffTree[index].isLeaf())
	{
		createBitCode(HuffTree[index].left, bitcode_ + '0');
		createBitCode(HuffTree[index].right, bitcode_ + '1');
	}
	else
	{
		bitCode[index] = bitcode_;
	}
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
	createBitCode(root, "");
}

bool HuffmanTree::getChar(string &bitNum,unsigned char & c)
{
	int index = root, i = 0;
	while (!HuffTree[index].isLeaf() && i <bitNum.length())
	{
		if (bitNum[i] == '0')
			index = HuffTree[index].left;
		else
			index = HuffTree[index].right;
		i++;
	}

	if (HuffTree[index].isLeaf())
	{
		c = index;
		bitNum.erase(0, i);
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
			cout << i << " : " << bitCode[i] << endl;
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

void HuffmanEncoding::convertByte_Bit(char &bit_unused)
{
	unsigned char c, magicNumber;
	string bit;

	inputFile.read((char*)&c, 1);
	bit = "";
	
	while (!inputFile.eof() || bit.length() >= 8)
	{
		if (bit.length() < 8)
		{
			bit += tree.getBitCode(c);
			inputFile.read((char*)&c, 1);
		}
		
		while(bit.length() >= 8)
		{
			magicNumber = 0;
			for (int i = 0; i < 8; i++)
				if (bit[i] == '1')
					magicNumber |=  (1 << 7 - i);
			outputFile.write((char*)&magicNumber, 1);
			bit.erase(0, 8);
		}
	}
	//last byte (some bit may unused)
	magicNumber = 0;
	for (int i = 0; i < bit.length(); i++)
	{
		if (bit[i] == '1')
			magicNumber |= (1 << 7 - i);
	}
	bit_unused = bit.length();
	outputFile.write((char*)&magicNumber, 1);
}

void HuffmanEncoding::convertBit_Byte(char fileID)
{
	unsigned char c, getBit = 0;
	unsigned int pos;
	string bit;
	inputFile.read((char*)&c, 1);
	pos = inputFile.tellg();

	while (pos != header.data[fileID].address + header.data[fileID].compressSz)
	{
		for (int i = 0; i < 8; i++)
		{
			getBit = (c >> (7 - i)) & 1;
			bit += getBit == 0 ? '0' : '1';
		}

		while(tree.getChar(bit,c) == true)
			outputFile.write((char*)&c, 1);
		
		inputFile.read((char*)&c, 1);
		pos = inputFile.tellg();
	}
	//Process the last byte
	for (int i = 0; (i < 8 && header.data[fileID].bitUnused == 0)
		|| (i < header.data[fileID].bitUnused && header.data[fileID].bitUnused != 0); i++)
	{
		getBit = (c >> (7 - i)) & 1;
		bit += getBit == 0 ? '0' : '1';
	}
	while (tree.getChar(bit, c) == true)
		outputFile.write((char*)&c, 1);
}

void HuffmanEncoding::Encode_a_File(const char * inputFilePath, int id)
{
	//Compress Data File
	inputFile.open(inputFilePath, ios::binary | ios::in);
	convertByte_Bit(header.data[id].bitUnused);

	//Calculate for the compressSz 
	unsigned int packedSz;
	unsigned int totalSz = 0;
	for (int i = 0; i <= id - 1; i++)
		totalSz += header.data[i].compressSz;
	packedSz = (unsigned int)outputFile.tellp() - totalSz - header.size();
	header.data[id].compressSz = packedSz;
	
	inputFile.close();
}

void HuffmanEncoding::Decode_a_File(const char * inputFileName, const char *outputFolder, QUEUE<int> &idList)
{
	Read_a_File(inputFileName);
	inputFile.open(inputFileName, ios::binary | ios::in);
	tree.initFeqTab(header.Freq);
	tree.buildTree();
	tree.createBitcode();
	char sPath[512];
	int i = 0;
	if (idList.isEmpty())
	{
		for (int i = 1; i <= header.numOfFile; i++)
			idList.enqueue(i);
	}
	
	while (!idList.isEmpty())
	{
		idList.dequeue(i);
		printf("%2.d %s\n", i, header.data[i -1].fileName);
		sprintf(sPath, "%s\\%s", outputFolder, header.data[i - 1].fileName);
		outputFile.open(sPath, ios::binary | ios::out);
		inputFile.seekg(header.data[i - 1].address);
		convertBit_Byte(i - 1);
		outputFile.close();
	}
	inputFile.close();
}

void HuffmanEncoding::ListFiles(const char * fileName)
{
	Read_a_File(fileName);
	printf("   File name\t\tSize\t\tPacked\n");
	for (int i = 0; i < header.numOfFile; i++)
	{
		printf("%2.d %s\t\t%d\t\t%d\n", i+1, header.data[i].fileName, header.data[i].originalSz, header.data[i].compressSz);
	}
}

void CompressFileHeader::write(fstream &fOut)
{
	fOut.seekp(ios::beg);
	fOut.write(signature, sizeof(signature));
	fOut.write((char*)&Freq, sizeof(Freq));
	fOut.write((char*)&numOfFile, sizeof(numOfFile));
	for (int i = 0; i < numOfFile; i++)
		data[i].write(fOut);
}

bool CompressFileHeader::read(fstream &fIn)
{
	fIn.read(signature, sizeof(signature));
	if (strcmp(signature, "hfm") != 0)
		return false;
	fIn.read((char*)&Freq, sizeof(Freq));
	fIn.read((char*)&numOfFile, sizeof(numOfFile));
	data = new DataFileInfo[numOfFile];
	for (int i = 0; i < numOfFile; i++)
		data[i].read(fIn);
	return true;
}

void CompressFileHeader::setNumberOfFile(short nFile)
{
	if (nFile < 1)
		return;
	numOfFile = nFile;
	data = new DataFileInfo[numOfFile];
}

void CompressFileHeader::setFileInfo(const char * name, unsigned int size, char id)
{
	data[id].initFileName(name);
	data[id].originalSz = size;
}

DataFileInfo::DataFileInfo()
{
	address = originalSz = compressSz = 0xFFFFFFFF;
	fileName = nullptr;
	fileNameLength = 0;
	bitUnused = 0;
}

DataFileInfo::~DataFileInfo()
{
	if (!fileName)
		delete[]fileName;
	address = originalSz = compressSz = 0xFFFFFFFF;
	fileName = nullptr;
	fileNameLength = 0;
	bitUnused = 0;
}

void DataFileInfo::initFileName(const char * name)
{
	fileNameLength = strlen(name);
	fileName = new char[fileNameLength + 1];
	strcpy(fileName, name);
	fileName[fileNameLength] = '\0';
}

void DataFileInfo::write(fstream & fOut)
{
	char *buff, *pCur;
	buff = new char[this->size()];

	pCur = buff;

	memcpy(pCur, (char*) &originalSz, sizeof(originalSz));
	pCur += sizeof(originalSz);
	
	memcpy(pCur, (char*)&compressSz, sizeof(compressSz));
	pCur += sizeof(compressSz);

	memcpy(pCur, (char*)&fileNameLength, sizeof(fileNameLength));
	pCur += sizeof(fileNameLength);

	memcpy(pCur, fileName, fileNameLength);
	pCur += fileNameLength;

	memcpy(pCur, (char*)&bitUnused, sizeof(bitUnused));
	pCur += sizeof(bitUnused);

	memcpy(pCur, (char*)&address, sizeof(address));
	pCur += sizeof(address);
	
	fOut.write(buff, this->size());
	delete[] buff;
	buff = pCur = nullptr;
}

void DataFileInfo::read(fstream & fIn)
{
	fIn.read((char*)&originalSz, sizeof(originalSz));
	fIn.read((char*)&compressSz, sizeof(compressSz));
	fIn.read((char*)&fileNameLength, sizeof(fileNameLength));

	this->fileName = new char[fileNameLength + 1];
	fIn.read(fileName, fileNameLength); fileName[fileNameLength] = '\0';
	fIn.read(&bitUnused, sizeof(bitUnused));
	fIn.read((char*)&address, sizeof(address));
}

void HuffmanEncoding::PrepareForEncode(const char *sDir)
{
	unsigned short totalFile = getTotalFile(sDir);
	header.setNumberOfFile(totalFile);

	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	char sPath[256];
	sprintf(sPath, "%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		printf("Path not found : %s", sPath);
		return;
	}

	do
	{
		if (strcmp(fdFile.cFileName, ".") != 0
			&& strcmp(fdFile.cFileName, "..") != 0)
		{
			if (!(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
			{
				static int id = 0;
				header.setFileInfo(fdFile.cFileName, fdFile.nFileSizeLow, id++);
				sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
				tree.countChar(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);

	tree.exportFeqTab(header.Freq);
	tree.buildTree();
	tree.createBitcode();
}

void HuffmanEncoding::computeAddress()
{
	unsigned int totalSz = 0;
	for (int i = 0; i < header.numOfFile; i++)
	{
		if (i == 0)
			totalSz = header.size();
		else
			totalSz += header.data[i - 1].compressSz;
		header.data[i].address = totalSz;
	}
}

void HuffmanEncoding::Read_a_File(const char * inputFileName)
{
	inputFile.open(inputFileName, ios::binary | ios::in);
	header.read(inputFile);
	inputFile.close();
}

void HuffmanEncoding::Encode_a_Folder(const char *sDir, const char *outputFileName)
{
	PrepareForEncode(sDir);
	outputFile.open(outputFileName, ios::binary | ios::out);

	header.write(outputFile);
	char sPath[256];
	for (int i = 0; i < header.numOfFile; i++)
	{
		sprintf(sPath, "%s\\%s", sDir, header.data[i].fileName);
		Encode_a_File(sPath, i);
		printf("%s\t%d Done!\n", header.data[i].fileName, header.data[i].originalSz);
	}

	computeAddress();
	outputFile.seekp(ios::beg);
	header.write(outputFile);
	outputFile.close();
}

unsigned short getTotalFile(const char * sDir)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	char sPath[256];

	sprintf(sPath, "%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		
	}

	//Count total file in Directory
	unsigned short totalFile = 0;
	do
	{
		if (strcmp(fdFile.cFileName, ".") != 0
			&& strcmp(fdFile.cFileName, "..") != 0)
		{
			if (!(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
				totalFile++;
			else
			{
				sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
				totalFile += getTotalFile(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);
	return totalFile;
}


