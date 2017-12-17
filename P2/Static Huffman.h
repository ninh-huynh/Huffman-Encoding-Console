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
	HuffmanTree tree;
	bool checkSum;
	void convertByte_Bit(char &bit_unused, fstream& inputFile, fstream& outputFile);
	void convertBit_Byte(char fileID, fstream& inputFile, fstream& outputFile);
	void PrepareForEncode(const char *sDir);
	void computeAddress();
	void Saving_to_header(const char *inputFileName);
	void Encode_a_File(const char *inputFilePath, int id, fstream& outputFile);
	void Decode_a_File(const char * outputFolder, int id, fstream& inputFile);
	void viewSavingInfo();
public:
	void Encode_a_Folder(const char *sDir, const char *outputName);
	void Decode_Files(const char * inputFileName, const char *outputFolder, QUEUE<int> &idList);
	void ListFiles(const char *fileName);
};

unsigned short getTotalFile(const char *dir);