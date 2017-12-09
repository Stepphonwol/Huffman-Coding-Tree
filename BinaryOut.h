#pragma once
#ifndef BINARYOUT_H
#define BINARYOUT_H
#include <fstream>
#include <iostream>

using namespace std;

class HTree;

class BinaryOut {
	friend class HTree;
	private:
		BinaryOut(fstream& x) : out(x), buffer('0'), n(0) { }
		~BinaryOut();
		void clearBuffer();
		void writeBit(bool bit);
		void writeChar(char t);
		void writeInt(int x);
		void writeString(string x);
		void recycle();
		fstream& out;
		char buffer;
		int n;
};
#endif