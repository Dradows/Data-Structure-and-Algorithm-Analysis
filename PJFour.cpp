#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const string num[20]={"","一","二","三","四","五","六","七","八"};

//ct表示前继课程数，son[0]表示后继课程数，son[1..son[0]]表示后继课程
struct Course {
	int id, semester, son[100], ct;
	char name[100];
}course[100];

int main()
{
	string s, inputfile, outputfile;
	stringstream stream;
	//clen[x]表示第x学期所需课程数。semester[x][0]表示第x学期已有课程数，其后表示课程。
	int clen[9], i, j, t, x, y, semester[9][100], ct=0, sum;
	char c;
	ifstream fin;
	ofstream fout;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 100; j++)
			semester[i][j] = 0;
	cout << "Please enter the input file:";
	cin >> inputfile;
	cout << "Please enter the output file:";
	cin >> outputfile;
	fin.open(inputfile);
	fout.open(outputfile);
	getline(fin,s);
	while (s[0]=='/'||s=="")
		getline(fin,s);
	j = 0;
	stream << s;
	for (i = 1; i < 9; i++)
		stream >> clen[i];
	stream.str("");
	stream.clear();
	getline(fin, s);
	while (s[0] == '/' || s == "")
		getline(fin, s);
	j = 1;
	while (s[0] == 'c') {
		x = 0; y = 0;
		ct++;
		stream << s;
		stream >> c >> course[j].id >> course[j].name >> t >> course[j].semester >> c >> x >> c >> y;
		if (x != 0) {
			course[x].son[0]++;
			course[x].son[course[x].son[0]] = j;
			course[j].ct++;
		}
		if (y != 0) {
			course[y].son[0]++;
			course[y].son[course[y].son[0]] = j;
			course[j].ct++;
		}		
		j++;
		stream.str("");
		stream.clear();
		getline(fin, s);
	}
	sum = ct;
	for (i = 1; i <= ct; i++) {
		x = course[i].semester;
		if (x != 0) {
			course[i].ct = -1;
			semester[x][++semester[x][0]] = i;
			sum--;
		}
	}

	t = 1;
	for (int ii=0;ii<sum;ii++) {
		for (i=1;i<=ct;i++)
			if (course[i].ct == 0) {
				course[i].ct = -1;
				for (j = 1; j <= course[i].son[0]; j++)
					course[course[i].son[j]].ct--;
				semester[t][++semester[t][0]] = i;
				if (semester[t][0] == clen[t]) t++;
				break;
			}
	}

	for (i = 1; i < 9; i++) {
		fout << num[i] << "学期：";
		for (j = 1; j <= clen[i]; j++)
			fout << course[semester[i][j]].name << ' ';
		fout << endl;
	}

	fin.close();


	fout.close();
}

