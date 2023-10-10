//소스코드3.5: Postfix Expression
//token의 변수가 char 1개를 문자 숫자로 된 일반 변수가 처리되도록 구현
//operator도 >=, && 연산자가 가능하도록 확장 구현

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
		return 8;//가장 낮은 우선 순위
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
	else if (a == '!')//unary minus를 추가한다
		return 1;
	else if (a == '*' || a == '/' || a == '%')
		return 2;
	else if (a == '+' || a == '-')
		return 3;
	else if (a == '<' || a == '>')// <=, >=를 추가한다 
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
//prefix() 알고리즘 구현
Expression& Postfix(Expression& e)
/*
화면에서 입력된 infix expression e로 부터 postfix를 구한다
NextToken()함수는 다음 토큰을 가져오는 함수이고 stack<>를 사용한다
infix expression의 마지막은 null 문자이고 생성된 postfix expression의 마지막 문자는 #이다.
stack의 bottom에 입력된 #를 사용하여 isp(), icp() 함수값의 규칙을 정의한다.
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
	postfix expression e를 evaluate한다.
	토큰은 operator, operand 또는 #이고 마지막 토큰은 #이다.
	함수 NextToken()이 e 로부터 다음 토큰을 가져온다.
	변수 값은 난수로 생성된 inputData[] 배열 값을 사용하여 가져 온다.
	*/
	index = 0;
	stack<int> st;
	st.push(99);
	int result = 0;
	cout << "EVAL 시작::" << endl;
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
		if (isOperand(x)) {
			int num = inputData[x - 'a']; cout << "변수값:: " << num;
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
			//연산자 >=, && 등이 구현되도록 확장 구현
			st.push(result);
		
		}
	result = st.top();
	st.pop();
	cout << "Eval 값은 " << result << endl;
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
	cout << endl << "infix 표기의 expression 입력: ";
	scanf("%s", input);
	cout << input << endl;
	postfix = Postfix(input);
	cout << postfix << endl;
	Eval(postfix);
	cin >> ch;
}
