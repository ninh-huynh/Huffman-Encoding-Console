#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
using namespace std;
#define MAX_NODE 511

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
	void initNode(unsigned char ch, unsigned int frq, short l, short r,short idx);
	unsigned char getChar();
	unsigned int getFreq();
	short getId();
	void setChar(unsigned char ch);
	void increseFreq(int k  = 1);
	void NodeOut();
};

class HuffmanTree
{
private:
	short root;
	HuffmanNode HuffTree[MAX_NODE];
	string bitCode[256];
	void createBitCode(short index,string bitcode_);
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
	string getBitCode(const unsigned char c)
	{
		return bitCode[c];
	}
	bool getChar(string &bitNum,unsigned char &c);
	void huffTreeOut();
	void bitCodeOut();
};

class DataFileInfo 
{
public:
	/*~DataFileInfo()
	{
		delete[]fileName;
	}*/
	unsigned int originalSz, compressSz;	//4 bytes + 4bytes
	unsigned char fileNameLength;
	char *fileName;			//20 bytes
	char bitUnused;							//1 bytes
	unsigned int address;					//4 bytes
	unsigned int size()
	{
		return sizeof(originalSz) + sizeof(compressSz) 
			+ sizeof(fileNameLength) + fileNameLength 
			+ sizeof(address) + sizeof(bitUnused);
	}		

	void initFileName(const char *name);
	void write(fstream &fOut);
	void read(fstream &fIn);
};

class CompressFileHeader
{
public:
	short idFile;
	char signature[3];			//3 bytes
	unsigned int Freq[256];		//256*4 = 1024 bytes
	short numOfFile;			//2 bytes
	DataFileInfo *data;			// ? * numOfFile
	CompressFileHeader()
	{
		strcpy(signature, "hfm");
	}
	/*~CompressFileHeader()
	{
		delete[]data;
	}*/
	unsigned int size()
	{
		unsigned int sz = 0;
		sz += sizeof(signature) + sizeof(Freq) + sizeof(numOfFile);
		for (int i = 0; i < numOfFile; i++)
			sz += data[i].size();
		return sz;
	}
	void write(fstream &fOut);
	bool read(fstream &fIn);
};

class HuffmanEncoding
{
private:
	CompressFileHeader header;
	fstream inputFile, outputFile;
	HuffmanTree tree;
	void convertByte_Bit(char &bit_unused);
	void convertBit_Byte(char fileID);
public:
	void PrepareForEncode(const char *sDir);
	void computeAddress();
	void Read_a_File(const char *inputFileName);
	void Encode_a_Folder(const char *sDir, const char *outputName);
	void Encode_a_File(const char *inputFilePath);
	void Decode_a_File(const char *inputFileName, const char *outputFolder);
	void ListFiles(const char *fileName);
};

unsigned short getTotalFile(const char *dir);
void TransferData(fstream &inFile, fstream &outFile);
//void mainProcess(const char *sDir);