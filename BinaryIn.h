#pragma once
#ifndef BINARYIN_H
#define BINARYIN_H
#include <iostream>
#include <fstream>

using namespace std;

class HTree;

class BinaryIn {
	friend class HTree;
	private:
		BinaryIn(fstream &x) : in(x) { 
			fillBuffer();
		}
		~BinaryIn();
		void fillBuffer();
		bool readBit();
		char readChar();
		int readInt();
		fstream &in;
		unsigned char buffer;
		int n;
};
#endif

