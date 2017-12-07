#include"Static Huffman.h"

int main()
{
	char buff[1024], buff1[1024], choice;
	HuffmanEncoding HFE;
	printf("Huffman Compression Program\n");
	printf("1. Compress files in folder\n");
	printf("2. View compressed filed info\n");
	printf("3. Uncompress all file\n");
	printf("4. Uncompress specific file\n");
	printf("5. Exit\n");
	cin >> choice;
	while (choice)
	{
		switch (choice)
		{
		case 1:
			printf("Enter the path to folder contain files :");
			cin.getline(buff, 1024);
			printf("Enter the result file name :");
			cin.getline(buff1, 1024);
			HFE.Encode_a_Folder(buff, buff1);
			break;
		case 2:
			printf("Enter the path to compressed file:");
			cin.getline(buff, 1024);
			HFE.ListFiles(buff);
			break;
		case 3:
			printf("Enter the path to folder contain compressed file:");
			cin.getline(buff, 1024);
			printf("Enter the folder contain uncompress files:");
			cin.getline(buff1, 1024);
			HFE.Decode_a_File(buff, buff1);
			break;
		case 4:
			break;
		}
		system("pause");
		system("cls");
		printf("Huffman Compression Program\n");
		printf("1. Compress files in folder\n");
		printf("2. View compressed file info\n");
		printf("3. Uncompress all file\n");
		printf("4. Uncompress specific file\n");
		printf("0. Exit\n");
	}
	return 0;
}