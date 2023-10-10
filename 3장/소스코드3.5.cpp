//�ҽ��ڵ�3.5: Postfix Expression
//token�� ������ char 1���� ���� ���ڷ� �� �Ϲ� ������ ó���ǵ��� ����
//operator�� >=, && �����ڰ� �����ϵ��� Ȯ�� ����

#include <iostream>
#include <memory>
#include <stack>
#include <cstring>
#include <time.h>
#include <stdlib.h>
typedef char Expression[20];
typedef char Token;
using namespace std;

int index = 0;
int inputData[26] = { 0 };
char NextToken(char* e)
{
	char token = e[index];
	index++;
	return token;
}

bool isOperand(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' ||
		x == '(' || x == ')' || x == '%' || x == '#')
		return false;
	else
		return true;
}

int isp(char a)
{
	if (a == '#')
		return 8;//���� ���� �켱 ����
	else if (a == '!')
		return 1;
	else if (a == '*' || a == '/' || a == '%')
		return 2;
	else if (a == '+' || a == '-')
		return 3;
	else if (a == '<' || a == '>')
		return 4;
	else if (a == '(')
		return 8;
	return 0;
}

int icp(char a)
{
	if (a == '(')
		return 0;
	else if (a == '!')//unary minus�� �߰��Ѵ�
		return 1;
	else if (a == '*' || a == '/' || a == '%')
		return 2;
	else if (a == '+' || a == '-')
		return 3;
	else if (a == '<' || a == '>')// <=, >=�� �߰��Ѵ� 
		return 4;
	// ==, != :: 5
	// && :: 6
	// || :: 7
	return 0;
}
void stringAdd(Expression& ex, char ch) {
	int len;
	len = strlen(ex);
	ex[len] = ch;
	ex[len + 1] = '\0';
	
}
//prefix() �˰��� ����
Expression& Postfix(Expression& e)
/*
ȭ�鿡�� �Էµ� infix expression e�� ���� postfix�� ���Ѵ�
NextToken()�Լ��� ���� ��ū�� �������� �Լ��̰� stack<>�� ����Ѵ�
infix expression�� �������� null �����̰� ������ postfix expression�� ������ ���ڴ� #�̴�.
stack�� bottom�� �Էµ� #�� ����Ͽ� isp(), icp() �Լ����� ��Ģ�� �����Ѵ�.
*/
{
	stack<char> st;
	st.push('#');
	static char exp[20];
	for (char x = NextToken(e); x != NULL; x = NextToken(e))
	{
		char y;
		if (isOperand(x)) {
			stringAdd(exp, x);
		}
		else if (x == ')')
		{
			while (st.top() != '(')
			{
				x = st.top(); stringAdd(exp, x);
				st.pop();
			}
			st.pop();
		}
		else
		{
			while(isp(st.top()) <= icp(x)) {
				y = st.top(); stringAdd(exp, y);
				st.pop();
			}
			st.push(x);
		}
	}

	char z;
	while ((z = st.top()) != '#')
	{
		stringAdd(exp, z);
		st.pop();
	}
	stringAdd(exp, '#');
	return exp;
}

void Eval(Expression e) {
	/*
	postfix expression e�� evaluate�Ѵ�.
	��ū�� operator, operand �Ǵ� #�̰� ������ ��ū�� #�̴�.
	�Լ� NextToken()�� e �κ��� ���� ��ū�� �����´�.
	���� ���� ������ ������ inputData[] �迭 ���� ����Ͽ� ���� �´�.
	*/
	index = 0;
	stack<int> st;
	st.push(99);
	int result = 0;
	cout << "EVAL ����::" << endl;
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
		if (isOperand(x)) {
			int num = inputData[x - 'a']; cout << "������:: " << num;
			st.push(num);
		}
		else {
			//remove the correct number of operands for operator x from stack;
			//perform the operation x and store the result onto the stack;
			int num1 = st.top();
			st.pop();
			int num2 = st.top();
			st.pop();
			if (x == '*')
				result = num1 * num2;
			else if (x == '+')
				result = num1 + num2;
			//������ >=, && ���� �����ǵ��� Ȯ�� ����
			st.push(result);
		
		}
	result = st.top();
	st.pop();
	cout << "Eval ���� " << result << endl;
}

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 26; i++)
		inputData[i] = rand() % 9;
	index = 0;
	char input[20];
	char* postfix;
	char ch;
	cout << endl << "infix ǥ���� expression �Է�: ";
	scanf("%s", input);
	cout << input << endl;
	postfix = Postfix(input);
	cout << postfix << endl;
	Eval(postfix);
	cin >> ch;
}
