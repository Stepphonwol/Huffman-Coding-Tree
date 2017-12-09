#include "HTree.h"

HTree::HTree()
{
	//src = x;
	char* temp = new char{ '0' };
	bit_cont = temp;
	shiftamount = 0;
	cout << "Name of the input text :" << endl;
	getline(cin, input_name);
	cout << "Name of the buffer dat : " << endl;
	//cin.get();
	getline(cin, buffer_name);
	cout << "Name of the output text: " << endl;
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

/*void HTree::bit_to_bit(int sign)
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
*/

void HTree::writeTrie(BinaryOut& bin)
{
	//out.open(output_name, fstream::binary | fstream::out);
	//int s{ 0 };
	//BinaryOut o{ out };
	writeTrieHelp(root, bin);
}

void HTree::writeTrieHelp(Node* x, BinaryOut& bin)
{
	if (x->isLeaf()) {
		//out << true;
		//bool temp{ true };
		//out.write((char*)&temp, sizeof(bool));
		//bit_to_bit(1);
		bin.writeBit(1);
		bin.writeChar(x->ch); // send real value of x->ch
		//ascii_write(x->ch);
		return;
	}
	bin.writeBit(0);
	//out << false;
	writeTrieHelp(x->left, bin);
	writeTrieHelp(x->right, bin);
}

/*void HTree::ascii_write(char x)
{
	for (int i = 7; i >= 0; --i) {
		bool temp = (x & 1 << i) != 0;
		//out << temp;
		out.write((char*)&temp, sizeof(temp));
	}
}*/

void HTree::write_src(BinaryOut& bin)
{
	//write_bit_int(src.size());
	bin.writeInt(src.size());
	for (int i = 0; i < src.size(); ++i) {
		string code = st[src[i]];
		//write_bit_string(code);
		bin.writeString(code);
	}
	bin.recycle();
	/*if (shiftamount > 0) {
		*bit_cont <<= 8 - shiftamount;
		out << *bit_cont;
		shiftamount = 0;
	}*/
}

/*bool HTree::read_bit()
{
	out >> *bit_cont; // read 8 bits
	char temp = *bit_cont; // get the first bit
	temp &= 128; // get the first bit
	temp >>= 7; // get the first bit
	*bit_cont <<= 1; // first bit processed
	if (temp == '1') {
		char* next_bit_cont;
		out >> *next_bit_cont;
		return true;
	}
	else if (temp == '0') {
		return false;
	}
}*/

Node* HTree::readTrie(BinaryIn& Bin)
{
	if (Bin.readBit()) {
		return new Node(Bin.readChar(), 0, NULL, NULL);
	}
	return new Node('\0', 0, readTrie(Bin), readTrie(Bin));
}

void HTree::compress()
{
	out.open(buffer_name, fstream::binary | fstream::out);
	BinaryOut o( out );
	calc_freq();
	root = buildTrie();
	buildCode();
	writeTrie(o);
	write_src(o);
	// deconstructor of o will close fstream out
}

void HTree::decompress()
{
	out.open(buffer_name, fstream::binary | fstream::in);
	out.seekg(0, fstream::beg);
	ans.open(output_name, fstream::out);
	BinaryIn b(out);
	BinaryOut o(ans);
	root = readTrie(b);
	int n = b.readInt();
	for (int i = 0; i < n; ++i) {
		Node* x = root;
		while (!x->isLeaf()) {
			if (b.readBit()) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		o.writeChar(x->ch);
	}
	// deconstructor of b and o will close the fstream
}