#pragma once
bool isLetter(char ch)
{//isLetter ��ʶ��
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	else
		return false;
}

bool isDigit(char ch)
{//isDigit ����
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool isOperators(char ch)
{// isOperators �����
	if (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '=' || ch == '#' || ch == ':' || ch == '<' || ch == '>')
		return true;
	else
		return false;
}
bool isDelimiter(char ch)
{// isDelimiter ���
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