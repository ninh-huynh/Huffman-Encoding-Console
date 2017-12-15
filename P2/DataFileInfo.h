#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

class DataFileInfo
{
public:
	DataFileInfo();
	~DataFileInfo();
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