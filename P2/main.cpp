#include<iostream>
using namespace std;

#include"Static Huffman.h"
#include"Queue.cpp"

int main()
{
	int choice;
	cout << "Huffman Compression Program\n";
	cout << "1. Compress files in folder\n";
	cout << "2. View compressed file info\n";
	cout << "3. Uncompress all file\n";
	cout << "4. Uncompress specific file\n";
	cout << "0. Exit\n";
	cin >> choice;
	while (choice)
	{
		char buff[256], buff1[256];
		HuffmanEncoding HFE;
		switch (choice)
		{
		case 1:
			cout << "Enter the path to directory contain files: ";
			cin.ignore();
			cin.getline(buff, 1024);
			cout << "Enter the path to result file name: ";
			cin.getline(buff1, 1024);
			HFE.Encode_a_Folder(buff, buff1);
			break;
		case 2:
			cout << "Enter the path to compressed file: ";
			cin.ignore();
			cin.getline(buff, 1024);
			HFE.ListFiles(buff);
			break;
		case 3: case 4:
			cout << "Enter the path to compressed file (with extension): ";
			cin.ignore();
			cin.getline(buff, 1024);
			cout << "Enter the path to directory contain uncompress files: ";
			cin.getline(buff1, 1024);
			QUEUE<int> idList;
			if (choice == 4)
			{
				HFE.ListFiles(buff);
				cout << "Type index file to uncompress. 0 to finish: ";
				cin >> choice;
				while (choice)
				{
					idList.enqueue(choice);
					cin >> choice;
				}
			}
			HFE.Decode_Files(buff, buff1, idList);
			break;
		}
		system("pause");
		system("cls");
		cout << "Huffman Compression Program\n";
		cout << "1. Compress files in folder\n";
		cout << "2. View compressed file info\n";
		cout << "3. Uncompress all file\n";
		cout << "4. Uncompress specific file\n";
		cout << "0. Exit\n";
		cin >> choice;
	}

	return 0;
}