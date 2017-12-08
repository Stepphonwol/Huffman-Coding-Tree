#pragma once
#ifndef HTREE_H
#define HTREE_H
#include "Node.h"
#include "MinPQ.h"

class HTree {
	public:
		HTree();
		void compress();
	private:
		void read_input();
		void calc_freq(); // calculate the frequency for each letter
		Node* buildTrie(); // build the Huffman tree
		void buildCode(); // build the compiling table of this Huffman tree
		void buildCodeHelp(Node* x, string s);
		void bit_to_bit(int sign);
		void write_bit(char x);
		void write_bit_int(int x);
		void write_bit_string(string x);
		void writeTrie();
		void writeTrieHelp(Node* x);
		void ascii_write(char x);
		void write_src();
		Node* root;
		int freq[256]; // ASCII Code as index
		string src; // source string
		string st[256]; // compiling table for Huffman tree
		string output_name;
		string input_name;
		fstream in;
		fstream out;
		//bitset<8> bit_cont;
		int shiftamount;
		char* bit_cont; // pointer on bit_cont
};
#endif
