#include "BinaryIn.h"

BinaryIn::~BinaryIn()
{
	in.close();
}

void BinaryIn::fillBuffer()
{
	try {
		//in >> buffer;
		in.read((char*)&buffer, sizeof(unsigned char));
		n = 8;
	}
	catch (...) {
		cout << "File stream error!!!" << endl;
		buffer = EOF;
		n = -1;
	}
}

bool BinaryIn::readBit()
{
	--n;
	bool bit = ((buffer >> n) & 1) == 1; // get the first bit
	if (n == 0) {
		fillBuffer();
	}
	return bit;
}

char BinaryIn::readChar()
{
	if (n == 8) {
		unsigned char ans = buffer;
		fillBuffer();
		return ans;
	} // special case when aligned byte

	// combine last n bits of currrent buffer with first (8-n) bits of new buffer
	unsigned char x = buffer; // ascii code for buffer; unsigned in case of overflow
	x <<= (8 - n);
	int oldn = n;
	fillBuffer();
	n = oldn;
	x |= (buffer >> n);
	return x;
}

int BinaryIn::readInt()
{
	int x{ 0 };
	for (int i = 0; i < 4; ++i) {
		char c = readChar();
		x <<= 8;
		x |= c;
	} // read the next 32 bits from standard input and return as an int

	return x;
}
