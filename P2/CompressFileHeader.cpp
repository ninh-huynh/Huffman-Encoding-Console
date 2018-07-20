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

void CompressFileHeader::read(fstream &fIn)
{
	fIn.read(signature, sizeof(signature));
	if (strcmp(signature, "hfm") != 0)
		throw std::invalid_argument("File not support!");
	fIn.read((char*)&Freq, sizeof(Freq));
	fIn.read((char*)&nFile, sizeof(nFile));
	data = new DataFileInfo[nFile];
	for (int i = 0; i < nFile; i++)
		data[i].read(fIn);
}

void CompressFileHeader::setNumberOfFile(short nFile)
{
	if (nFile < 1)
		return;
	this->nFile = nFile;
	data = new DataFileInfo[nFile];
}

void CompressFileHeader::setFileInfo(const char * name, unsigned int size)
{
	static int id = 0;
	data[id].initFileName(name);
	data[id].originalSz = size;
	id++;
}
