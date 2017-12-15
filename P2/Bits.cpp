#include "Bits.h"

BITS::BITS()
{
	bit = 0;
	length = 0;
}


BITS::~BITS()
{
	bit = 0;
	length = 0;
}

int BITS::size()
{
	return length;
}

bool BITS::isByte()
{
	if (length >= 8)
		return true;
	return false;
}

void BITS::pop_a_Byte(unsigned char &out)
{
	if (length == 0)
		return;
	out = bit >> (8 * 3);
	if (length >= 8)
		removeBit(8);
}

void BITS::push_back(unsigned char uChar, char bitUnused)
{
	int i = 0, j = length, bitEnd;
	bitEnd = bitUnused == 0 ? 8 : bitUnused;
	for ( ; i < bitEnd; i++, j++)
	{
		if (((uChar >> (7 - i)) & 1) == 1)
			bitOn(j);
	}
	length = bitUnused == 0 ? length + 8 : length + bitUnused;
}

int BITS::operator[](int pos)
{
	if (pos < 0 || pos >length)
		return -1;

	unsigned int tmp = bit;
	tmp = (tmp >> (4 * 8 - 1 - pos)) & 1;
	return tmp;
}

BITS BITS::operator+(char _1_0)
{
	BITS tmp(*this);
	tmp += _1_0;
	return tmp;
}

BITS & BITS::operator+=(char _1_0)
{
	if (_1_0 == 1)
		this->bitOn(length);
	this->length++;
	return *this;
}

BITS & BITS::operator+=(BITS bits2)
{
	int i = 0, j = length;
	for (; i < bits2.length; i++, j++)
	{
		if (bits2[i] == 1)
			bitOn(j);
	}
	length += bits2.length;
	return *this;
}


bool BITS::bitOn(int pos)
{
	if (pos < 0 || pos > 8 * 4)
		return false;

	bit |= (1 << (8 * 4 - 1 - pos));
	return true;
}

void BITS::removeBit(int nBit)
{
	if (nBit <= length)
	{
		bit = bit << nBit;
		length -= nBit;
	}
}

void BITS::toString()
{
	for (int i = 0; i < length; i++)
		cout << this->operator[](i);
}
