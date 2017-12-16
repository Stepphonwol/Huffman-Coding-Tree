## Huffman-Coding-Tree
### 实验目的与要求
1. 要求对文件进行Huffman编码的算法,以及对一编码文件进行解码的算法。
2. 熟练掌握二叉树的应用。
3. 熟练掌握计算机系统的基本操作方法,了解如何编辑、编译、链接和运行一个C++程序及二叉树上的基本运算。
4. 上机调试程序,掌握查错、排错使程序能正确运行。
### 实验环境
- Windows 10
- Visual Studio 2017
### 算法描述
#### 压缩
1. **计算每个字符出现的频率** （采用ASCII编码，故每个字符对应freq数组的每一个特定位置）
```
	for (int i = 0; i < src.size(); ++i) {
		++freq[src[i]];
	}
```
2. **根据第一步计算出的字符频率， 建立Huffman树。**
    - 将每一个在源串中出现了的字符推入优先队列（最小堆）。
    - 弹出该优先队列最小的两个元素，这两棵树就是具有最小频率的两棵树。
    归并这两棵树，并将归并后生成的树的根结点推入优先队列。
    ```
    	while (pq.getSize() > 1) { // merge two trees with minimum frequency
			Node* x = pq.delMin();
			Node* y = pq.delMin();
			Node* parent = new Node('\0', x->freq + y->freq, x, y);
			pq.insert(parent);
		}
    ```
    - 上述过程执行完毕后，优先队列中只剩下一个元素，这就是所建立的Huffman树的根结点。
3. **建立Huffman编码表**。采用类似于前序遍历的方法遍历Hufffman树，若为内部结点，则先向左遍历并将编码串加‘0’， 再向右遍历并将编码串加‘1’，若为叶结点，则将此时的编码串写入对应的位置。
```
	if (x->isLeaf()) {
		st[x->ch] = s;
		return;
	}
	buildCodeHelp(x->left, s + "0");
	buildCodeHelp(x->right, s + "1");
```
4. **将Huffman树转换为比特流，并写入压缩文件**。同样采用类似于前序遍历的方法遍历Huffman树，若为内部结点，则写入0，并先后向左向右递归遍历，若为叶结点，则写入1，并将该叶结点表示的字符按位写入。
```
	if (x->isLeaf()) {
		bin.writeBit(1);
		bin.writeChar(x->ch); 
		return;
	}
	bin.writeBit(0);
	writeTrieHelp(x->left, bin);
	writeTrieHelp(x->right, bin);
```
5. **将源串按编码表转换为比特流，并写入压缩文件**。
	- 先将待压缩源串的长度按位写入。
	- 再遍历源串，并根据编码表，把每个字符转换为对应的编码，写入。
	 ```
	bin.writeInt(src.size());
	for (int i = 0; i < src.size(); ++i) {
		string code = st[(int)src[i]];
		bin.writeString(code);
	}
	bin.recycle(); // write the remaining bits
	```
---
#### 解压
6. **解压Huffman树**。按位读取压缩文件，若读到的二进制位为1，则说明遇到了叶结点，再向后读一个char，恢复该叶子节点；若读到的二进制位为0，则说明遇到了内部结点，恢复该内部节点，并先后对其左孩子及右孩子递归建树。
```
	if (Bin.readBit()) {
		return new Node(Bin.readChar(), 0, NULL, NULL);
	}
	return new Node('\0', 0, readTrie(Bin), readTrie(Bin));
```
7. **解压源串长度**。
```
	int n = b.readInt();
```
8. **解压源串** 。根据解压出的Huffman树，解压源串。根据读取到的比特流，定位到该比特流对应的叶子结点，并将其对应的字符输出。
```
	for (int i = 0; i < n; ++i) {
		Node* x = root;
		while (!x->isLeaf()) {
			if (b.readBit()) {
				x = x->left; // the recovered Huffman tree is reversed
			}
			else {
				x = x->right; // the recovered Huffman tree is reversed
			}
		}
		o.writeChar(x->ch);
	}
```
---
### 源程序清单
- BinaryIn.h + BinaryIn.cpp
- BinaryOut.h + BinaryOut.cpp
- MinPQ.h + MinPQ.cpp
- Node.h + Node.cpp
- HTree.h + HTree.cpp
- main.cpp
### 运行结果
- **输入端**
![](HUFFMAN1.PNG)
- **待压缩文本（节选）**
![](HUFFMAN2.PNG)
- **压缩文件**
![](HUFFMAN4.PNG)
- **解压出的文件（节选）**
![](HUFFMAN3.PNG)
---
### 实验运行情况分析
- 该算法有以下两个局限：
	- 只能压缩完全由**ASCII编码**组成的文件。
	- 至多只能压缩**2^32 - 1**个字符。
- 针对这两个局限，有如下的解决方案：
	- 由使用者指定待压缩文件的编码方式，并根据所指定好的编码方式使用**不同大小的freq以及st容器。**
	- 由使用者指定待压缩文件的大小，不同大小采用基于**不同数据类型的按位读写方式。**
