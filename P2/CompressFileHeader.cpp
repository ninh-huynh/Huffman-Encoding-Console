#include "CompressFileHeader.h"

CompressFileHeader::CompressFileHeader()
{
	strcpy(signature, "hfm");
	numOfFile = 0;
	data = nullptr;
}

CompressFileHeader::~CompressFileHeader() 
{
	if (!data)
		delete[]data;
	numOfFile = 0;
	data = nullptr;
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
