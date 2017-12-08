#pragma once
#ifndef MINPQ_H
#define MINPQ_H
#include <vector>
#include "Node.h"

using namespace std;

class MinPQ {
	public:
		MinPQ() {}
		void insert(Node* t);
		Node* delMin();
		int getSize();
	private:
		vector<Node*> src;
		void swap(int i, int j);
		bool less(int i, int j);
		void build_min_heap(int n);
		void sink(int k, int n);
};
#endif