#include "Node.h"

bool Node::isLeaf()
{
	return left == NULL && right == NULL;
}

bool Node::operator<(Node x) {
	if (this->freq < x.freq) {
		return true;
	}
	else {
		return false;
	}
}