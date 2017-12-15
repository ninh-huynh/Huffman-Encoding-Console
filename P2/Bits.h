#pragma once
#include <iostream>
using namespace std;


class BITS {
private:
	unsigned int bit;
	unsigned char length;
public:
	BITS();
	~BITS();
	int size();
	bool isByte();
	void pop_a_Byte(unsigned char &out);
	void push_back(unsigned char uChar, char bitUnused = 0);
	int operator [](int pos);
	BITS operator + (char _1_0);
	BITS& operator += (char _1_0);
	BITS& operator += (BITS bits2);
	bool bitOn(int pos);
	void removeBit(int nBit);
	void toString();
};