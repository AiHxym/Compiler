#pragma once

#include <iostream>
#include <string>
#include "lexer.h"
using namespace std;

lexer lex = lexer("test.txt");

int program();
int block();
int conDeclare();
int conHandle();
int varDeclare();
int proc();
int body();
int statement();
int condition();
int expression();
int term();
int factor();



int main()
{
	cout << "fdfs";
	if (!program())
		cout << "That's good";
	return 0;
}

int program()
{
	int tmp = block();
	if (lex.keepToken() < lex.getSym().size())
		return -1;
	else
		return tmp;
}

int block()
{
	conDeclare();
	varDeclare();
	proc();
	return statement();
}

int conDeclare()
{
	int reset = lex.keepToken();
	int tmp;
	if (lex.getToken() != CONSTSYM)
	{
		lex.resetToken(reset);
		return -1;
	}
	do
	{
		if (conHandle())
		{
			lex.resetToken(reset);
			return -1;
		}
	} while ((tmp = lex.getToken()) == (int)',');
	if (tmp == ';')
		return 0;
	lex.resetToken(reset);
	return -1;
}

int conHandle()
{
	int reset = lex.keepToken();
	if (lex.getToken() != IDENT)
	{
		lex.resetToken(reset);
		return -1;
	}
	if (lex.getToken() != (int)'=')
	{
		lex.resetToken(reset);
		return -1;
	}
	if (lex.getToken() != NUMBER)
	{
		lex.resetToken(reset);
		return -1;
	}
	return 0;
}

int varDeclare()
{
	int reset = lex.keepToken();
	int tmp;
	if (lex.getToken() != VARSYM)
	{
		lex.resetToken(reset);
		return -1;
	}
	do
	{
		if (lex.getToken() != IDENT)
		{
			lex.resetToken(reset);
			return -1;
		}
	} while ((tmp = lex.getToken()) == (int)',');
	if (tmp == ';')
		return 0;
	lex.resetToken(reset);
	return -1;
}

int proc()
{
	int reset = lex.keepToken();
	if (lex.getToken() != PROSYM)
	{
		lex.resetToken(reset);
		return -1;
	}
	if (lex.getToken() != IDENT)
	{
		lex.resetToken(reset);
		return -1;
	}
	if (lex.getToken() != (int)';')
	{
		lex.resetToken(reset);
		return -1;
	}
	if (block())
	{
		lex.resetToken(reset);
		return -1;
	}
	if (lex.getToken() != (int)';')
	{
		lex.resetToken(reset);
		return -1;
	}
	proc();
	return 0;
}


int body()
{
	int reset = lex.keepToken();
	int tmp;
	if (lex.getToken() != BEGINSYM)
	{
		lex.resetToken(reset);
		return -1;
	}
	do
	{
		if (statement())
		{
			lex.resetToken(reset);
			return -1;
		}
	} while ((tmp = lex.getToken()) == (int)';');
	lex.pushToken();
	if (lex.getToken() != ENDSYM)
	{
		lex.resetToken(reset);
		return -1;
	}
	return 0;
}

int statement()
{
	int reset = lex.keepToken();
	if (lex.getToken() == IDENT)
	{
		if (lex.getToken() == ASSIN)
		{
			if (!expression())
				return 0;
		}
	}
	lex.resetToken(reset);
	if (lex.getToken() == IFSYM)
	{
		if (!condition())
		{
			if (lex.getToken() == THENSYM)
			{
				if (!statement())
					return 0;
			}
		}
	}
	lex.resetToken(reset);
	if (lex.getToken() == WHILESYM)
	{
		if (!condition())
		{
			if (lex.getToken() == DOSYM)
			{
				if (!statement())
					return 0;
			}
		}
	}
	lex.resetToken(reset);
	if (lex.getToken() == CALLSYM)
	{
		if (lex.getToken() == IDENT)
			return 0;
	}
	lex.resetToken(reset);
	int tmp;
	bool flag = true;
	if (lex.getToken() == READSYM)
	{
		if (lex.getToken() == '(')
		{
			do
			{
				if (lex.getToken() != IDENT)
				{
					flag = false;
					break;
				}
			} while ((tmp = lex.getToken()) == (int)',');
			if (flag)
			{
				if (tmp == (int)')')
					return 0;
			}
		}
	}
	lex.resetToken(reset);
	flag = true;
	if (lex.getToken() == WRITESYM)
	{
		if (lex.getToken() == '(')
		{
			do
			{
				if (lex.getToken() != IDENT)
				{
					flag = false;
					break;
				}
			} while ((tmp = lex.getToken()) == (int)',');

			if (flag)
			{
				if(tmp == (int)')')
					return 0;
			}
		}
	}
	lex.resetToken(reset);
	if (!body())
		return 0;
	lex.resetToken(reset);
	return 0;
}

int condition()
{
	int reset = lex.keepToken();
	int tmp;
	if (!expression())
	{
		tmp = lex.getToken();
		if (tmp == (int)'=' || tmp == (int)'#' || tmp == (int)'<' || tmp == (int)'>' || tmp == LE || tmp == GE)
		{
			if (!expression())
				return 0;
		}
	}
	lex.resetToken(reset);
	if (lex.getToken() == ODDSYM)
	{
		if (!expression())
			return 0;
	}
	lex.resetToken(reset);
	return -1;
}

int expression()
{
	int reset = lex.keepToken();
	int tmp = lex.getToken();
	bool flag = true;
	if (tmp == (int)'+' || tmp == (int)'-')
	{
		do
		{
			if (term())
			{
				flag = false;
				break;
			}
			tmp = lex.getToken();
		} while (tmp == (int)'+' || tmp == (int)'-');
		
		if (flag)
		{
			lex.pushToken();
			return 0;
		}
	}
	lex.resetToken(reset);
	flag = true;
	do
	{
		if (term())
		{
			flag = false;
			break;
		}
		tmp = lex.getToken();
	} while (tmp == (int)'+' || tmp == (int)'-');
	if (flag)
	{
		lex.pushToken();
		return 0;
	}
	lex.resetToken(reset);
	return -1;
}

int term()
{
	int reset = lex.keepToken();
	int tmp;
	bool flag = true;
	do
	{
		if (factor())
		{
			flag = false;
			break;
		}
		tmp = lex.getToken();
	} while (tmp == (int)'*' || tmp == (int)'/');
	if (flag)
	{
		lex.pushToken();
		return 0;
	}
	return -1;
}

int factor()
{
	int reset = lex.keepToken();
	if (lex.getToken() == IDENT)
		return 0;
	lex.resetToken(reset);
	if (lex.getToken() == NUMBER)
		return 0;
	lex.resetToken(reset);
	if (lex.getToken() == (int)'(')
	{
		if (!expression())
		{
			if (lex.getToken() == (int)')')
				return 0;
		}
	}
	lex.resetToken(reset);
	return -1;
}

