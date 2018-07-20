#include<iostream>
#include"Static Huffman.h"
#include"Queue.cpp"

int main(int argc, char* argv[])
{
	//Useage:
	//huff [Source Folder] [Result Folder] (By default, result folder is the source folder if not specify)
	//ls [Source Path]
	//unhuff [Source Path] [Filename 1] [Filename 2] ... (If you want decompress all files, leave the "Filename" blank) 
	//exit
	//

	int choice;
	std::cout << "Huffman Compression Program\n";
	std::cout << "1. Compress files in folder\n";
	std::cout << "2. View compressed file info\n";
	std::cout << "3. Uncompress all file\n";
	std::cout << "4. Uncompress specific file\n";
	std::cout << "0. Exit\n";
	std::cin >> choice;
	while (choice)
	{
		char buff[256], buff1[256];
		switch (choice)
		{
		case 1:
			std::cout << "Enter the path to directory contain files: ";
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			std::cout << "Enter the path to result file name: ";
			std::cin.getline(buff1, 1024);
			HuffmanEncoding::Encode_a_Folder(buff, buff1);
			break;
		case 2:
			std::cout << "Enter the path to compressed file: ";
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			HuffmanEncoding::ListFiles(buff);
			break;
		case 3: case 4:
			std::cout << "Enter the path to compressed file (with extension): ";
			std::cin.ignore();
			std::cin.getline(buff, 1024);
			std::cout << "Enter the path to directory contain uncompress files: ";
			std::cin.getline(buff1, 1024);
			QUEUE<int> idList;
			if (choice == 4)
			{
				HuffmanEncoding::ListFiles(buff);
				std::cout << "Type index file to uncompress. 0 to finish: ";
				std::cin >> choice;
				while (choice)
				{
					idList.enqueue(choice);
					std::cin >> choice;
				}
			}
			HuffmanEncoding::Decode_Files(buff, buff1, idList);
			break;
		}
		system("pause");
		system("cls");
		std::cout << "Huffman Compression Program\n";
		std::cout << "1. Compress files in folder\n";
		std::cout << "2. View compressed file info\n";
		std::cout << "3. Uncompress all file\n";
		std::cout << "4. Uncompress specific file\n";
		std::cout << "0. Exit\n";
		std::cin >> choice;
	}

	return 0;
}