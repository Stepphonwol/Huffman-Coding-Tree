#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <bitset>

using namespace std;

class HTree;
class MinPQ;

class Node {
	friend class HTree;
	friend class MinPQ;
	private:
		Node(char c = NULL, int f = NULL, Node* l = NULL, Node* r = NULL) : ch(c), freq(f), left(l), right(r) {}
		bool isLeaf();
		bool operator<(Node x);
		char ch;
		int freq;
		Node* left;
		Node* right;
};
#endif