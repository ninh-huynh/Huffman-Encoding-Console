#include"Static Huffman.h"
#include<iostream>
using namespace std;
int main()
{
	char buff[256], buff1[256];
	int choice;
	HuffmanEncoding HFE;
	cout << "Huffman Compression Program\n";
	cout << "1. Compress files in folder\n";
	cout << "2. View compressed filed info\n";
	cout << "3. Uncompress all file\n";
	cout << "4. Uncompress specific file\n";
	cout << "5. Exit\n";
	cin >> choice;
	while (choice != 0)
	{
		switch (choice)
		{
		case 1:
			cout << "Enter the path to folder contain files :";
			cin.ignore();
			cin.getline(buff, 1024);
			cout << "Enter the result file name :";
			//cin.ignore();
			cin.getline(buff1, 1024);
			HFE.Encode_a_Folder(buff, buff1);
			break;
		case 2:
			cout << "Enter the path to compressed file:";
			cin.ignore();
			cin.getline(buff, 1024);
			HFE.ListFiles(buff);
			break;
		case 3:
			cout << "Enter the path to folder contain compressed file:";
			cin.ignore();
			cin.getline(buff, 1024);
			cout << "Enter the folder contain uncompress files:";
			//cin.ignore();
			cin.getline(buff1, 1024);
			HFE.Decode_a_File(buff, buff1);
			break;
		case 4:
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