#define _CRT_SECURE_NO_WARNINGS
#include "Static Huffman.h"

void HuffmanEncoding::convertByte_Bit(char &bit_unused, fstream& inputFile, fstream& outputFile)
{
	unsigned char c, byteOut;
	BITS bits;

	inputFile.read((char*)&c, 1);
	while (!inputFile.eof())
	{
		if (!bits.isByte())
		{
			bits += tree.getBitCode(c);
			inputFile.read((char*)&c, 1);
		}

		while (bits.isByte())
		{
			bits.pop_a_Byte(byteOut);
			outputFile.write((char*)&byteOut, 1);
		}
	}
	//last byte (some bit may unused)
	bit_unused = bits.size();
	bits.pop_a_Byte(byteOut);
	outputFile.write((char*)&byteOut, 1);
}

void HuffmanEncoding::convertBit_Byte(char fileID, fstream& inputFile, fstream& outputFile)
{
	inputFile.seekg(header.data[fileID].address);
	unsigned char c, getBit = 0;
	unsigned int pos;
	BITS bits;
	inputFile.read((char*)&c, 1);
	pos = inputFile.tellg();

	while (pos != header.data[fileID].address + header.data[fileID].compressSz)
	{
		bits.push_back(c);

		while (tree.getChar(bits, c) == true)
			outputFile.write((char*)&c, 1);

		inputFile.read((char*)&c, 1);
		pos = inputFile.tellg();
	}
	//Process the last byte
	if (header.data[fileID].bitUnused != 0)
		bits.push_back(c, header.data[fileID].bitUnused);
	
	while (tree.getChar(bits, c) == true)
		outputFile.write((char*)&c, 1);
}

void HuffmanEncoding::Encode_a_File(const char * inputFilePath, int id, fstream& outputFile)
{
	//Compress Data File
	fstream inputFile(inputFilePath, ios::binary | ios::in);
	convertByte_Bit(header.data[id].bitUnused, inputFile, outputFile);

	//Calculate for the compressSz 
	unsigned int packedSz;
	unsigned int totalSz = 0;
	for (int i = 0; i <= id - 1; i++)
		totalSz += header.data[i].compressSz;
	packedSz = (unsigned int)outputFile.tellp() - totalSz - header.size();
	header.data[id].compressSz = packedSz;
	
	inputFile.close();
}

void HuffmanEncoding::Decode_a_File(const char * outputFolder, int id, fstream& inputFile)
{
	char sPath[512];
	sprintf(sPath, "%s\\%s", outputFolder, header.data[id - 1].fileName);
	fstream outputFile(sPath, ios::binary | ios::out);
	convertBit_Byte(id - 1, inputFile, outputFile);
	int decodeSz = 0;
	decodeSz =(unsigned int) outputFile.tellp();
	checkSum = decodeSz == header.data[id - 1].originalSz ? true : false;
	printf("%2d. %-70s %-10s Done!\n", id, header.data[id - 1].fileName, checkSum ? "No Error" : "Error");
	outputFile.close();
}

void HuffmanEncoding::Decode_Files(const char * inputFileName, const char *outputFolder, QUEUE<int> &idList)
{
	Saving_to_header(inputFileName);
	fstream inputFile(inputFileName, ios::binary | ios::in);
	tree.initFeqTab(header.Freq);
	tree.buildTree();
	tree.createBitcode();
	char sPath[512];
	int i = 0;
	if (idList.isEmpty())
	{
		for (int i = 1; i <= header.nFile; i++)
			idList.enqueue(i);
	}
	
	while (idList.dequeue(i) == true)
	{
		Decode_a_File(outputFolder, i, inputFile);
	}
	inputFile.close();
}

void HuffmanEncoding::ListFiles(const char * fileName)
{
	Saving_to_header(fileName);
	printf("%3s %-70s %-14s %-14s\n", " ", "File name", "Original Size", "Packed Size");
	for (int i = 0; i < header.nFile; i++)
	{
		printf("%2d. %-70s %-14d %-14d\n", i + 1, header.data[i].fileName, header.data[i].originalSz, header.data[i].compressSz);
	}
}

void HuffmanEncoding::viewSavingInfo()
{
	for (int i = 0; i < header.nFile; i++)
		cout << "bit unused : " << (short)header.data[i].bitUnused << endl;
}

void HuffmanEncoding::PrepareForEncode(const char *sDir)
{
	unsigned short totalFile = getTotalFile(sDir);
	header.setNumberOfFile(totalFile);

	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	char sPath[256];
	sprintf(sPath, "%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		printf("Path not found : %s", sPath);
		return;
	}

	do
	{
		if (strcmp(fdFile.cFileName, ".") != 0
			&& strcmp(fdFile.cFileName, "..") != 0)
		{
			if (!(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
			{
				static int id = 0;
				header.setFileInfo(fdFile.cFileName, fdFile.nFileSizeLow, id++);
				sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
				tree.countChar(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);

	tree.exportFeqTab(header.Freq);
	tree.buildTree();
	tree.createBitcode();
}

void HuffmanEncoding::computeAddress()
{
	unsigned int totalSz = 0;
	for (int i = 0; i < header.nFile; i++)
	{
		if (i == 0)
			totalSz = header.size();
		else
			totalSz += header.data[i - 1].compressSz;
		header.data[i].address = totalSz;
	}
}

void HuffmanEncoding::Saving_to_header(const char * inputFileName)
{
	fstream inputFile(inputFileName, ios::binary | ios::in);
	header.read(inputFile);
	inputFile.close();
}

void HuffmanEncoding::Encode_a_Folder(const char *sDir, const char *outputFileName)
{
	PrepareForEncode(sDir);
	char outFileNameWithExt[256];
	sprintf(outFileNameWithExt, "%s.hfm", outputFileName);
	fstream outputFile(outFileNameWithExt, ios::binary | ios::out);

	header.write(outputFile);
	char sPath[256];
	for (int i = 0; i < header.nFile; i++)
	{
		sprintf(sPath, "%s\\%s", sDir, header.data[i].fileName);
		Encode_a_File(sPath, i, outputFile);
		printf("%2d. %-70s Done!\n", i + 1, header.data[i].fileName);
	}

	computeAddress();
	outputFile.seekp(ios::beg);
	header.write(outputFile);
	
	outputFile.close();
}

unsigned short getTotalFile(const char * sDir)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	char sPath[256];

	sprintf(sPath, "%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		
	}

	//Count total file in Directory
	unsigned short totalFile = 0;
	do
	{
		if (strcmp(fdFile.cFileName, ".") != 0
			&& strcmp(fdFile.cFileName, "..") != 0)
		{
			if (!(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY))
				totalFile++;
			else
			{
				sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
				totalFile += getTotalFile(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);
	return totalFile;
}


