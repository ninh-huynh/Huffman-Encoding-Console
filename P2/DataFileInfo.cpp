#include "DataFileInfo.h"

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

	memcpy(pCur, (char*)&originalSz, sizeof(originalSz));
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
