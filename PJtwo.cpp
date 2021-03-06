#include <iostream>
#include <utility>
#include <stack>
#include <string>
using namespace std;

class Calculator {
public:
	void Run(string str);
	bool fault = false;
	//执行表达式
private:
	stack<double> OPND;         //操作数栈 
	stack<char> OPTR;              //操作符栈  
	int isp(char op);                        //栈内优先数
	int icp(char op);                        //栈外优先数
	void DoOperator(double x, char op, double y);	//形成运算指令，进行运算
//	double GetDouble(string s);
	bool IsOperator(char ch);         //判断ch是否为操作符 	
	void Clear();
};

void Calculator::Run(string str) {
	int i=0;
	double x,y;
	char operation;
	str += "=";
	OPTR.push('=');
	while (!fault&&str[i] != '='||OPTR.top()!='=') {
		if (isdigit(str[i])){
			OPND.push(atof(&str[i]));
			while (isdigit(str[i])||str[i]=='.') i++;
		}
		else if (!IsOperator(str[i])) fault=true;
		else {
			operation = OPTR.top();
			if (isp(operation) < icp(str[i])) {
				OPTR.push(str[i]);
				i++;
			}
			else if (isp(operation) > icp(str[i])) {
				OPTR.pop();
				if (OPND.empty()) {
					fault = true;
					break;
				}
				y = OPND.top();
				OPND.pop();
				if (OPND.empty()) {
					fault = true;
					break;
				}
				x = OPND.top();
				OPND.pop();
				DoOperator(x, operation, y);
			}
			else {
				OPTR.pop();
				if (operation == '(')i++;
			}
		}
	}
	if (fault) {
		cout << "Wrong expression.\n";
		Clear();
		return;
	}
	cout << "Answer: " << OPND.top()<<endl;
	Clear();
	
}

int Calculator::isp(char op) {
	switch (op) {
	case '=':return 0; break;
	case '(':return 1; break;
	case '*':;
	case '/':;return 5; break;
	case '+':;
	case '-':return 3; break;
	case ')':return 6; break;
	}
}

int Calculator::icp(char op) {
	switch (op) {
	case '=':return 0; break;
	case '(':return 6; break;
	case '*':;
	case '/':;return 4; break;
	case '+':;
	case '-':return 2; break;
	case ')':return 1; break;
	}
}

void Calculator::DoOperator(double x, char op, double y) {
	double value;
	switch (op) {
	case '+':value = x + y; OPND.push(value); break;
	case '-':value = x - y; OPND.push(value); break;
	case '*':value = x * y; OPND.push(value); break;
	case '/':if (y == 0.0) {
		cerr << "Divide by 0!" << endl;
		fault = true;
	}
			 else { value = x / y; OPND.push(value); }
			 break;
	}
}

/**
double Calculator::GetDouble(string s) {
	int i=0;
	double news;
	if (s[i] == 0) i++;
	while (!IsOperator(s[i])) i++;
	news=atof(&s.substr(0, i)[0]);
	s.erase(0, i);
	return(news);
}
*/

void Calculator::Clear() {
	while (!OPND.empty()) OPND.pop();
	while (!OPTR.empty()) OPTR.pop();
}

bool Calculator::IsOperator(char ch) {
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' ||  ch == '+' || ch == '-' || ch == ')')
		return true;
	else
		return false;
}

int main()
{
	Calculator cal;
	string s;
	cout << "Please enter the expression:\n";
	cin >> s;
	while (s != "q") {
		cal.Run(s);
		cal.fault = false;
		cin >> s;
	}
    return 0;
}

