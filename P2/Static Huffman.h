
#include<Windows.h>
#include"CompressFileHeader.h"
#include"HuffmanTree.h"
#include"Queue.cpp"
using namespace std;

class HuffmanEncoding
{
private:
	static void convertByte_Bit(char &bit_unused, fstream& inputFile, fstream& outputFile);
	static void convertBit_Byte(char fileID, fstream& inputFile, fstream& outputFile);
	static void PrepareForEncode(const char *sDir);
	static void computeAddress();
	static void Saving_to_header(const char *inputFileName);
	static void Encode_a_File(const char *inputFilePath, int id, fstream& outputFile);
	static void Decode_a_File(const char * outputFolder, int id, fstream& inputFile);
	static void viewSavingInfo();
public:
	static void Encode_a_Folder(const char *sDir, const char *outputName);
	static void Decode_Files(const char * inputFileName, const char *outputFolder, QUEUE<int> &idList);
	static void ListFiles(const char *fileName);
};

unsigned short getTotalFile(const char *dir);