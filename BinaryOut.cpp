#include "BinaryOut.h"

BinaryOut::~BinaryOut()
{
	out.close();
	//delete buffer;
}

void BinaryOut::clearBuffer()
{
	if (n == 0) {
		return;
	}
	if (n > 0) {
		buffer <<= (8 - n);
	}
	try {
		out << buffer;
	}
	catch (...) {
		cout << "Bit writing error!!!" << endl;
		exit(1);
	}
	n = 0;
	buffer = '0' - '0';
	//*buffer = '1';
}

void BinaryOut::writeBit(bool bit)
{
	//cout << bit << " ";
	buffer <<= 1;
	if (bit) {
		buffer |= 1;
	}
	++n;
	if (n == 8) {
		clearBuffer();
	}
}

void BinaryOut::writeChar(char t)
{
	// t : ascii code for char
	// optimized if byte-aligned
	if (n == 0) {
		try {
			out << t;
		}
		catch (...) {
			cout << "Bit writing error!!!" << endl;
		}
		return;
	}
	for (int i = 0; i < 8; ++i) {
		//bool temp = (c & (1 << i));
		bool temp = ((t >> (8 - i - 1)) & 1) == 1;
		writeBit(temp);
	}
}

void BinaryOut::writeInt(int x)
{
	/*int temp{ x };
	while (temp != 0) {
		int judge = temp % 2;
		writeBit(judge);
		temp /= 2;
	}*/
	writeChar((x >> 24) & 0xff);
	writeChar((x >> 16) & 0xff);
	writeChar((x >> 8) & 0xff);
	writeChar((x >> 0) & 0xff);
}

void BinaryOut::writeString(string x)
{
	for (int i = 0; i < x.size(); ++i) {
		//bool judge = x[i];
		if (x[i] == '1') {
			writeBit(1);
		}
		else {
			writeBit(0);
		}
	}
}

void BinaryOut::recycle()
{
	if (n != 0) {
		//buffer <<= 8 - n; // put zeroes after the remaining bits
		clearBuffer();
		n = 0;
	}
}