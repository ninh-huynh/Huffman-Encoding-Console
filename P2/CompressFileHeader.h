#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"DataFileInfo.h"
class CompressFileHeader
{
public:
	char signature[3];			//3 bytes
	unsigned int Freq[256];		//256*4 = 1024 bytes
	short numOfFile;			//2 bytes
	DataFileInfo *data;			// ? * numOfFile
	CompressFileHeader();
	~CompressFileHeader();
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
	void setNumberOfFile(short nFile);
	void setFileInfo(const char *name, unsigned int size, char id);
};