#pragma once
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
	if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
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
char key[13][10] = { "const","var", "procedure", "begin", "end", "if", "then",
					 "call", "while", "do", "read", "write", "odd" };