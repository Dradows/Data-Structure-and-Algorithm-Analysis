#include <iostream>
#include <fstream>
using namespace std;
struct BlockChain {
	char svalue[5000];
	int len;
	BlockChain *pre, *next;
};

ofstream fout;
ifstream fin;
bool fend = true;
char a[5000], b[5000],inputfile[100],c;
BlockChain *p, *p1, *p2,*ps;
int pv = -1, i, pn=-1;

void newBC(BlockChain& a) {
	a.svalue[0] = '\0';
	a.len = 0;
	a.next = NULL;
	a.pre = NULL;
}

void mov(BlockChain& p, char *c2) {
	int i;
	for (i = 0; c2[i] != '\0'; i++) p.svalue[i] = c2[i];
	p.svalue[i] = c2[i];
	p.len = i;
}

void get(char *c) {
	int i=0;
	if ((c[i] = cin.get()) != '\n') i++;;
	while ((c[i++] = cin.get())!= '\n');
	c[i - 1] = '\0';
}

void showNow() {
	if (pv == -1) {
		cout << "Buffer is empty.\n" << "Next command: ";
		return;
	}
	cout << pn << " : " << p->svalue << "\n"<<"Next command: ";
}

void methodR() {	
	if (pv>-1) {
		cout << "Buffer is not empty and will be destroyed, is it alright?\nIf it is ok, please enter yes: ";
		get(b);
		if (b[0] != 'y' && b[0] != 'Y') {
			showNow();
			return;
		}
	}
	fin.open(inputfile);
	p = new BlockChain;
	newBC(*p);
	ps = p;
	pv = -1;
	pn = -1;
	while (true) {
		for (c = fin.get(); c != '\n'&&c != EOF; c = fin.get())
			p->svalue[p->len++] = c;
		if (c == EOF) {
			p->svalue[p->len] = '\0';
			pv++;
			pn = pv;
			break;
		}
		p->svalue[p->len] = '\0';
		pv++;
		p1 = new BlockChain;
		newBC(*p1);
		p1->pre = p;
		p->next = p1;
		p = p1;
	}
	fin.close();
	showNow();
}

void methodW() {
	int i;
	p1 = ps;
	for (i = 0; i < pv; i++) {
		fout << p1->svalue<<"\n";
		p1 = p1->next;
	}
	fout << p1->svalue << endl;
	showNow();
}

void methodC() {
	int i=0,j=0,k,len1,len2;
	if (pv == -1) {
		showNow();
		return;
	}
	cout << "Please enter the string you want to replace: ";
	get(a);
	cout << "please enter the string you want to add in: ";
	get(b);
	for (len1 = 0; a[len1] != '\0'; len1++);
	for (len2 = 0; b[len2] != '\0'; len2++);
		while (p->svalue[i + j] != '\0')
			if (a[j] == '\0') {
				if (len1 == len2) {
					for (k = i; k < i + len1; k++)
						p->svalue[k] = b[k - i];
				}
				else if (len1 > len2) {
					for (k = i + len2; k <= p->len + len2 - len1; k++)
						p->svalue[k] = p->svalue[k + len1 - len2];
					for (k = i; k < i + len2; k++)
						p->svalue[k] = b[k - i];
					p->len -= len1 - len2;
					p->svalue[p->len] = '\0';
				}
			else {
				for (k = p->len + len2 - len1; k >= i + len2; k--)
					p->svalue[k] = p->svalue[k + len1 - len2];
				for (k = i; k < i + len2; k++)
					p->svalue[k] = b[k - i];
				p->len += len2 - len1;
				p->svalue[p->len] = '\0';
			}
				i+=len2;
				j = 0;
			}
				else if (p->svalue[i + j] == a[j])
					j++;   
				else
				{
					i++;
					j = 0;
				}
		if (a[j] == '\0') {
			if (len1 == len2) {
				for (k = i; k < i + len1; k++)
					p->svalue[k] = b[k - i];
			}
			else if (len1 > len2) {
				for (k = i + len2; k <= p->len + len2 - len1; k++)
					p->svalue[k] = p->svalue[k + len1 - len2];
				for (k = i; k < i + len2; k++)
					p->svalue[k] = b[k - i];
				p->len -= len1 - len2;
				p->svalue[p->len] = '\0';
			}
			else {
				for (k = p->len + len2 - len1; k >= i + len2; k--)
					p->svalue[k] = p->svalue[k + len1 - len2];
				for (k = i; k < i + len2; k++)
					p->svalue[k] = b[k - i];
				p->len += len2 - len1;
				p->svalue[p->len] = '\0';
			}
			i += len2;
			j = 0;
		}

	showNow();
}

void methodD() {
	if (pv == -1) {
		showNow();
		return;
	}
	if (p->next == NULL&&p->pre == NULL) {
		p1 = new BlockChain;
		newBC(*p1);
		p = p1;
		ps = p;
		pv--;
		pn--;
		showNow();
		return;
	}
	if (p->pre == NULL) {
		p->next->pre = NULL;
		p = p->next;
		ps = p;
		pv--;
		showNow();
		return;
	}
	if (p->next == NULL) {
		p->pre->next = NULL;
		p = p->pre;
		pn--;
		pv--;
		showNow();
		return;
	}
	p->pre->next = p->next;
	p->next->pre = p->pre;
	p = p->pre;
	pv--;
	pn--;
	showNow();
}

void methodG() {
	int t;
	if (pv == -1) {
		showNow();
		return;
	}
	cout << "Please enter the number of line you want to goto:";
	cin >> t;
	if (t > pv) {
		cout << "Too big\nNext command: ";
		return;
	}
	if (t < 0) {
		cout << "Too small\nNext command: ";
		return;
	}
	while (pn > t) {
		p = p->pre;
		pn--;
	}
	while (pn < t) {
		p = p->next;
		pn++;
	}
	showNow();
}

void methodB() {
	if (pv == -1) {
		showNow();
		return;
	}
	p = ps;
	pn = 0;
	showNow();
}

void methodE() {
	if (pv == -1) {
		showNow();
		return;
	}
	p = ps;
	while (p->next != NULL) p = p->next;
	pn = pv;
	showNow();
}

void methodI() {
	int i,t;
	cout << "Please enter the number of line you want to insert: ";
	cin >> t;
	cout << "Please enter the string you want to insert: ";
	get(a);
	if (pv == -1 && t==0) {
		mov(*p, a);
		pv++;
		pn++;
		showNow();
		return;
	}
	if (t < 0) {
		cout << "Too small\n";
		showNow();
		return;
	}
	if (t > pv+1) {
		cout << "Too big\n";
		showNow();
		return;
	}
	pn = t;
	if (t == 0) {
		p = new BlockChain;
		newBC(*p);
		mov(*p, a);
		ps->pre = p;
		p->next = ps;
		ps = p;
		pv++;
		pn = 0;
		showNow();
		return;
	}
	p = ps;	
	for (i = 0; (t!=pv+1&&i < t)||(t==pv+1&&i<t-1); i++) p = p->next;
	if (t == pv + 1) {
		p1 = new BlockChain;
		newBC(*p1);
		mov(*p1, a);		
		p->next = p1;
		p1->pre = p;
		p = p1;
		pv++;
		pn = pv;
		showNow();
		return;
	}
	p1 = new BlockChain;
	newBC(*p1);
	mov(*p1, a);
	p1->next = p;
	p1->pre = p->pre;
	p->pre->next = p1;
	p->pre = p1;
	p = p1;
	pv++;
	showNow();
}

void methodV() {
	int i=0;
	if (pv == -1) {
		showNow();
		return;
	}
	p1 = ps;
	cout << i++ << " : " << p1->svalue << endl;
	while (p1->next != NULL) {
		p1 = p1->next;
		cout << i++ << " : " << p1->svalue << endl;
	}
	cout << endl;
	showNow();
}

void methodL() {
	cout << "There are " << pv+1 << " lines in the buffer.\n"<<"Current line length is "<<p->len<<".\n";
	showNow();
}

void methodF() {
	int i,j=0,k,len;
	bool find = false;
	if (pv == -1) {
		showNow();
		return;
	}
	cout << "Please enter the string you want to find: ";
	get(a);
	for (i = 0; i < 5000; i++) b[i] = ' ';
	for (len = 0; a[len] != '\0'; len++);
	i = 0;
	while (p->svalue[i + j] != '\0')
		if (a[j] == '\0') {
			find = true;
			for (k = i; k < i + len; k++) b[k] = '^';
			i += len;
			j = 0;
		}
		else if (p->svalue[i + j] == a[j])
			j++;
		else
		{
			i++;
			j = 0;
		}
	if (!find) {
		cout << "String was not found.\n";
		showNow();
		return;
	}
	cout << p->svalue << endl;
	for (i = 0; i < p->len; i++)
		cout << b[i];
	cout << endl;
	showNow();
}

void methodP() {
	if (pv == -1) {
		showNow();
		return;
	}
	if (pn == 0)
		cout << "It is already the first.\n";
	else {
		pn--;
		p = p->pre;
	}
	showNow();
}

void methodN() {
	if (pv == -1) {
		showNow();
		return;
	}
	if (pn == pv)
		cout << "It is already the last.\n";
	else {
		pn++;
		p = p->next;
	}
	showNow();
}

void methodH() {
	cout << "Valid commands are : b(egin) c(hange) d(el) e(nd)\nf(ind) g(o) h(elp) i(nsert) l(ength) n(ext) p(rior)\nq(uit) r(ead) s(ubstitute) v(iew) w(rite)\n";
	showNow();
}

void methodS() {
	int len,i,t;
	if (pv == -1) {
		showNow();
		return;
	}
	cout << "Please enter the number of line you want to substitute for: "; 
	cin >> t;
	if (t > pv) {
		cout << "Too big\nNext command: ";
		return;
	}
	if (t < 0) {
		cout << "Too small\nNext command: ";
		return;
	}
	while (pn > t) {
		p = p->pre;
		pn--;
	}
	while (pn < t) {
		p = p->next;
		pn++;
	}
	cout << "Please enter the string you want to substitute with: ";
	get(a);
	for (len = 0; a[len] != '\0'; len++);
	for (i = 0; i < len; i++) p->svalue[i] = a[i];
	p->svalue[i] = '\0';
	showNow();
}

void main() {
	cout << "Please enter inputfile name: ";
	cin >> inputfile;
	cout << "please enter ouputfile name: ";
	cin >> a;
	cout << "Next command: ";
	fout.open(a); 
	p = new BlockChain;
	newBC(*p);
	ps = p;
	while (fend) {
		get(a);
		switch (a[0]) {
		case 'Q':case 'q': fend = false; break;
		case 'R':case 'r':methodR(); break;
		case 'W':case 'w':methodW(); break;
		case 'B':case 'b':methodB(); break;
		case 'C':case 'c':methodC(); break;
		case 'D':case 'd':methodD(); break;
		case 'G':case 'g':methodG(); break;
		case 'E':case 'e':methodE(); break;
		case 'I':case 'i':methodI(); break;
		case 'V':case 'v':methodV(); break;
		case 'L':case 'l':methodL(); break;
		case 'F':case 'f':methodF(); break;
		case 'P':case 'p':methodP(); break;
		case 'N':case 'n':methodN(); break;
		case 'S':case 's':methodS(); break;
		case 'H':case 'h':methodH(); break;
		default:cout << "Wrong command.\n"; showNow();
		}
	}
	fout.close();

}