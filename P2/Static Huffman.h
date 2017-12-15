#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"CompressFileHeader.h"
#include"HuffmanTree.h"
#include"Queue.cpp"
using namespace std;

class HuffmanEncoding
{
private:
	CompressFileHeader header;
	fstream inputFile, outputFile;
	HuffmanTree tree;
	bool checkSum;
	void convertByte_Bit(char &bit_unused);
	void convertBit_Byte(char fileID);
public:
	void PrepareForEncode(const char *sDir);
	void computeAddress();
	void Read_a_File(const char *inputFileName);
	void Encode_a_Folder(const char *sDir, const char *outputName);
	void Encode_a_File(const char *inputFilePath, int id);
	void Decode_a_File(const char * outputFolder,  int id);
	void Decode_Files(const char * inputFileName, const char *outputFolder, QUEUE<int> &idList);
	void ListFiles(const char *fileName);
	void viewSavingInfo();
};

unsigned short getTotalFile(const char *dir);