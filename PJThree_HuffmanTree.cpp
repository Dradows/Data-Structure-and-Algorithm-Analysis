#include <iostream>  
#include <fstream>
#include <string>  
#include <cstdio>
using namespace std;
ofstream fout, codeout;
ifstream fin, codein;
int ct[1000], root, blen=0;
char bin;
string code[1000];
//std中存在count函数，全局变量不宜以count为名

class Huffman {
public:
	Huffman() {
		data = -1;
		weight = 0;
		lchild = -1;
		rchild = -1;
		parent = -1;
	}
	Huffman(char c, int w) {
		data = c;
		weight = w;
		lchild = -1;
		rchild = -1;
		parent = -1;
	}
	Huffman(char c, int w, int x, int y) {
		data = c;
		weight = w;
		lchild = x;
		rchild = y;
		parent = -1;
	}
	int lchild, rchild, parent, weight;
	char data;
};


Huffman huff[1000];

int encode(int x,int i) {
	int y = huff[x].parent;
	if (y == -1) return 0;
	encode(y, i);
	if (huff[y].lchild == x)
		code[i] += '0';
	else
		code[i] += '1';
}

void binOutput(string s) {
	int i = 0;
	for (i = 0; i < s.length(); i++) {
		bin <<= 1;
		blen++;
		if (s[i]=='1') bin |= 1;
		if (blen == 8) {
			fout << bin;
			blen=bin = 0;
		}
	}
}

void compress() {
	string inputfile;
	string outputfile;
	string s="";
	int i, j, k, l, x, len = 0;
	char c;
	cout << "Please input source file name:";
	cin >> inputfile;
	cout << "Please input output file name:";
	cin >> outputfile;
	fout.open(outputfile);
	fin.open(inputfile);
	for (i = 0; i < 1000; i++) {
		ct[i] = 0;
		code[i] = "";
	}
	k = 0;
	while (fin.get(c)) {
		if (ct[c] == 0) k++;
		ct[c]++;
	}
	fout << k << endl;
	for (i=0;i<1000;i++)
		if (ct[i] != 0) 
			fout << (char)i <<" " << ct[i] <<endl;
	for (i = 0; i < 1000; i++) 
		if (ct[i] > 0)
			huff[len++]=Huffman(i, ct[i]);
	k = len;
	for (l = 0; l < len - 1; l++) {
		i = -1; j = -1;
		for (x = 0; x < k; x++) {
			if (huff[x].parent == -1 && (i == -1 || huff[x].weight < huff[i].weight)) {
				j = i; i = x;
			}
			else if (huff[x].parent == -1 && (j == -1 || huff[x].weight < huff[j].weight))
				j = x;
		}
		huff[i].parent = k;
		huff[j].parent = k;
		huff[k++] = Huffman(-1, huff[i].weight + huff[j].weight, i, j);
	}
	root = k-1;
	for (i = 0; i < len; i++)
			encode(i, huff[i].data);
	fin.clear();
	fin.seekg(0, ios::beg); 
	while (fin.get(c))
		s+= code[c];
	fout << s.length() << endl;
	binOutput(s);
	i = 0;
	fin.close();
	fout.close();
}

void decompress(){
	string inputfile;
	string outputfile;
	int i, j, k, l, len = 0, x;
	char c = 0;
	cout << "Please input source file name:";
	cin >> inputfile;
	cout << "Please input output file name:";
	cin >> outputfile;
	fout.open(outputfile);
	fin.open(inputfile);
	fin >> k;
	for (i = 0; i < 1000; i++) {
		ct[i] = 0;
		code[i] = "";
	}
	for (i = 0; i < k; i++) {
		fin.get(c);
		fin.get(c);
		fin >> ct[c];
	}
	k = 0;
	for (i = 0; i < 1000; i++)
		if (ct[i] > 0)
			huff[len++] = Huffman(i, ct[i]);
	k = len;
	for (l = 0; l < len - 1; l++) {
		i = -1; j = -1;
		for (x = 0; x < k; x++) {
			if (huff[x].parent == -1 && (i == -1 || huff[x].weight < huff[i].weight)) {
				j = i; i = x;
			}
			else if (huff[x].parent == -1 && (j == -1 || huff[x].weight < huff[j].weight))
				j = x;
		}
		huff[i].parent = k;
		huff[j].parent = k;
		huff[k++] = Huffman(-1, huff[i].weight + huff[j].weight, i, j);
	}
	root = k - 1;
	for (i = 0; i < len; i++)
		encode(i, huff[i].data);
	k = root;
	fin >> l;
	fin.get();
	while (fin.get(c)) {
		for (i = 0; i < (l>8 ? 8 : l); i++) {
			if (c&(1<<7)) k = huff[k].rchild;
			else k = huff[k].lchild;
			c <<= 1;
			if (huff[k].data != -1) {
				fout << huff[k].data;
				k = root;
			}
		}
		l -= 8;
	}
	fin.close();
	fout.close();
}

int main()
{ 
	int i, j;
	do {
		cout << "1.Huffman compress.\n2.Huffman decompress.\n3.Exit.\n";
		cin >> i;
		if (i == 1) compress();
		else if (i == 2) decompress();
	} while (i != 3);
    return 0;
}

