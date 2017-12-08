#include "HTree.h"

HTree::HTree()
{
	//src = x;
	char* temp = new char{ '0' };
	bit_cont = temp;
	shiftamount = 0;
	cout << "Name of the input text :" << endl;
	getline(cin, input_name);
	cout << "Name of the output dat : " << endl;
	//cin.get();
	getline(cin, output_name);
	read_input();
}

void HTree::read_input()
{
	try {
		in.open(input_name, fstream::binary | fstream::in);
	}
	catch (...) {
		cout << "Fail to open input text" << endl;
	}
	istreambuf_iterator<char> stream_it(in), eof;
	copy(stream_it, eof, back_inserter(src));
}

void HTree::calc_freq()
{
	for (int i = 0; i < src.size(); ++i) {
		++freq[src[i]];
	}
}

Node* HTree::buildTrie()
{
	MinPQ pq; // priority queue made specially for Huffman Tree Node
	for (int c = 0; c < 256; ++c) { // initialize priority queue
		if (freq[c] > 0) {
			Node* temp = new Node(c, freq[c]);
			pq.insert(temp);
		}
	}
	while (pq.getSize() > 1) { // merge two trees with minimum frequency
		Node* x = pq.delMin();
		Node* y = pq.delMin();
		Node* parent = new Node('\0', x->freq + y->freq, x, y);
		pq.insert(parent);
	}
	return pq.delMin(); // root node
}

void HTree::buildCode()
{
	string s;
	buildCodeHelp(root, s);
}

void HTree::buildCodeHelp(Node* x, string s)
{
	if (x->isLeaf()) {
		st[x->ch] = s;
		return;
	}
	buildCodeHelp(x->left, s + "0");
	buildCodeHelp(x->right, s + "1");
}

void HTree::bit_to_bit(int sign)
{
	if (sign == 1) {
		*bit_cont |= 1;
	}
	*bit_cont <<= 1;
	++shiftamount;
	if (shiftamount == 7) {
		out << *bit_cont;
		shiftamount = 0;
	}
}

void HTree::write_bit(char x)
{
	for (int i = 7; i >= 0; --i) {
		bool temp = (x & 1 << i);
		bit_to_bit(temp);
	}
}

void HTree::write_bit_int(int x)
{
	int temp{ x };
	while (temp != 0) {
		int judge = temp % 2;
		bit_to_bit(judge);
		temp /= 2;
	}
}

void HTree::write_bit_string(string x)
{
	for (int i = 0; i < x.size(); ++i) {
		int judge = x[i] - '0';
		bit_to_bit(judge);
	}
}

void HTree::writeTrie()
{
	out.open(output_name, fstream::binary | fstream::out);
	int s{ 0 };
	writeTrieHelp(root);
}

void HTree::writeTrieHelp(Node* x)
{
	if (x->isLeaf()) {
		//out << true;
		//bool temp{ true };
		//out.write((char*)&temp, sizeof(bool));
		bit_to_bit(1);
		write_bit(x->ch);
		//ascii_write(x->ch);
		return;
	}
	bit_to_bit(0);
	//out << false;
	writeTrieHelp(x->left);
	writeTrieHelp(x->right);
}

void HTree::ascii_write(char x)
{
	for (int i = 7; i >= 0; --i) {
		bool temp = (x & 1 << i) != 0;
		//out << temp;
		out.write((char*)&temp, sizeof(temp));
	}
}

void HTree::write_src()
{
	write_bit_int(src.size());
	for (int i = 0; i < src.size(); ++i) {
		string code = st[src[i]];
		write_bit_string(code);
	}
	out.close();
}

void HTree::compress()
{
	calc_freq();
	root = buildTrie();
	buildCode();
	writeTrie();
	write_src();
}