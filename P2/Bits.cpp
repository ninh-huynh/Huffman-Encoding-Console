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
	if (bitUnused == 0)
		bitUnused = 8;
	if (length + bitUnused >= 8 * 4)
		return;
	bit += (unsigned int) uChar << (8 * 3 - length);
	length += bitUnused;
}

int BITS::operator[](int pos)
{
	if (pos < 0 || pos >length)
		return -1;

	return (bit >> (4 * 8 - 1 - pos)) & 1;
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
	bit += bits2.bit >> length;
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
