#include "CompressFileHeader.h"

CompressFileHeader::CompressFileHeader()
{
	strcpy(signature, "hfm");
	nFile = 0;
	data = nullptr;
}

CompressFileHeader::~CompressFileHeader() 
{
	if (!data)
		delete[]data;
	nFile = 0;
	data = nullptr;
}

void CompressFileHeader::write(fstream &fOut)
{
	fOut.seekp(ios::beg);
	fOut.write(signature, sizeof(signature));
	fOut.write((char*)&Freq, sizeof(Freq));
	fOut.write((char*)&nFile, sizeof(nFile));
	for (int i = 0; i < nFile; i++)
		data[i].write(fOut);
}

bool CompressFileHeader::read(fstream &fIn)
{
	fIn.read(signature, sizeof(signature));
	if (strcmp(signature, "hfm") != 0)
		return false;
	fIn.read((char*)&Freq, sizeof(Freq));
	fIn.read((char*)&nFile, sizeof(nFile));
	data = new DataFileInfo[nFile];
	for (int i = 0; i < nFile; i++)
		data[i].read(fIn);
	return true;
}

void CompressFileHeader::setNumberOfFile(short nFile_)
{
	if (nFile_ < 1)
		return;
	nFile = nFile_;
	data = new DataFileInfo[nFile];
}

void CompressFileHeader::setFileInfo(const char * name, unsigned int size, char id)
{
	data[id].initFileName(name);
	data[id].originalSz = size;
}
