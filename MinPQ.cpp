#include "MinPQ.h"

void  MinPQ::insert(Node* t)
{
	src.push_back(t);
	int n = src.size();
	build_min_heap(n);
}

Node* MinPQ::delMin()
{
	Node* ans = new Node(src[0]->ch, src[0]->freq, src[0]->left, src[0]->right);
	swap(0, src.size() - 1);
	src.erase(src.end() - 1);
	int n = src.size();
	build_min_heap(n);
	return ans;
}

int MinPQ::getSize()
{
	return src.size();
}

void MinPQ::swap(int i, int j)
{
	Node temp = *src[i];
	*src[i] = *src[j];
	*src[j] = temp;
}

bool MinPQ::less(int i, int j)
{
	if (*src[i] < *src[j]) {
		return true;
	}
	else {
		return false;
	}
}

void MinPQ::build_min_heap(int n)
{
	for (int k = n / 2 - 1; k >= 0; --k) {
		sink(k, n);
	}
}

void MinPQ::sink(int k, int n)
{
	while (2 * k + 1 < n) {
		int j = 2 * k + 1; // j : left son; k : root
		if (j < n - 1 && !less(j, j + 1)) {
			++j;
		}
		if (less(k, j)) {
			break;
		}
		swap(k, j);
		k = j;
	}
}



