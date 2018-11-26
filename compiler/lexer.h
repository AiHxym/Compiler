#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <cassert>

#define IDENT 256
#define NUMBER 257
#define ASSIN 258
#define LE 259
#define GE 260

enum type
{
	CONSTSYM = 128, VARSYM, PROSYM, BEGINSYM, ENDSYM, IFSYM, THENSYM, CALLSYM, WHILESYM, DOSYM, READSYM, WRITESYM
};

using namespace std;

bool isLetter(char ch)
{//isLetter 标识符
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	else
		return false;
}

bool isDigit(char ch)
{//isDigit 常数
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool isOperators(char ch)
{// isOperators 运算符
	if (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '=' || ch == '#' || ch == ':' || ch == '<' || ch == '>')
		return true;
	else
		return false;
}
bool isDelimiter(char ch)
{// isDelimiter 界符
	if (ch == ',' || ch == ';' || ch == '.' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return true;
	else
		return false;
}
bool isBlank(char ch)
{
	if (ch == ' ' || ch == '\n')
		return true;
	else
		return false;
}
char key[12][10] = { "const","var", "procedure", "begin", "end", "if", "then", 
					 "call", "while", "do", "read", "write" };

class lexer
{
public:
	lexer(std::string filename);
	std::map<string, int> getIndex();
	std::vector<string> getNum();
	std::vector<int> getId();
	std::vector<int> getSym();
private:
	std::vector<string> num, keep;
	std::vector<int> sym, id;
	std::map<string, int> index;
};