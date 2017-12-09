#pragma once
#ifndef HTREE_H
#define HTREE_H
#include "Node.h"
#include "MinPQ.h"
#include "BinaryIn.h"
#include "BinaryOut.h"

class HTree {
	public:
		HTree();
		void compress();
		void decompress();
	private:
		void read_input();
		void calc_freq(); // calculate the frequency for each letter
		Node* buildTrie(); // build the Huffman tree
		void buildCode(); // build the compiling table of this Huffman tree
		void buildCodeHelp(Node* x, string s);
		/*void bit_to_bit(int sign);
		void write_bit(char x);
		void write_bit_int(int x);
		void write_bit_string(string x);*/
		void writeTrie(BinaryOut& bin);
		void writeTrieHelp(Node* x, BinaryOut& bin);
		//void ascii_write(char x);
		void write_src(BinaryOut& bin);
		//bool read_bit();
		Node* readTrie(BinaryIn& Bin);
		Node* root;
		int freq[256]; // ASCII Code as index
		string src; // source string
		string st[256]; // compiling table for Huffman tree
		string input_name;
		string buffer_name;
		string output_name;
		fstream in;
		fstream out;
		fstream ans;
		//bitset<8> bit_cont;
		int shiftamount;
		char* bit_cont; // pointer on bit_cont
};
#endif
