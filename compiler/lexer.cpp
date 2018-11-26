#include "lexer.h"

lexer::lexer(string filename)
{
	std::ifstream infile;
	infile.open(filename.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	string sourcecode;
	while (getline(cin, sourcecode))
	{
		for (int i = 0; i < sourcecode.length(); i)
		{
			int j = 0;  //letter  标识符
			int l = 0;   //digit  常数
			int k = 0;   //operators  运算符

			int	TYPE = 0;   //类型编号

			string tnum;
			char word[10] = "";
			if (isBlank(sourcecode[i]))
			{
				++i;
			}//去空格
			else
			{
				if (isLetter(sourcecode[i]))         //是否为字母
				{                                             //是
					do
					{
						if (j < 10)
						{
							word[j] = sourcecode[i];
							j++;
						}
					} while (isDigit(sourcecode[++i]) || isLetter(sourcecode[i]));//常数||标识符

					int a = 0;
					while (a < 12)
					{
						if (strcmp(key[a], word) == 0)
						{
							TYPE = 3;
							break;
						}
						else
						{
							TYPE = 1;
							++a;
							//否
						}
					}
					if (TYPE == 3)
					{
						sym.push_back(128 + a);
					}
					if (TYPE == 1)
					{
						int m = 0;
						bool flag = false;
						for (m = 0; m < keep.size(); ++m)
						{
							if (strcmp(word, keep[m].c_str()) == 0)
							{
								flag = true;
								break;
							}
						}
						sym.push_back(IDENT);
						if (flag)
						{
							id.push_back(m);
						}
						else
						{
							string tmp;
							for (m = 0; m < j; ++m)
							{
								tmp.push_back(word[m]);
							}
							keep.push_back(tmp);
							id.push_back(keep.size() - 1);
						}
					}
				}
				else if (isDigit(sourcecode[i]))//常数
				{
					while (isDigit(sourcecode[i]))
					{

						tnum.push_back(sourcecode[i]);
						++i;
					}
					sym.push_back(NUMBER);
					num.push_back(tnum);
				}
				else if (isDelimiter(sourcecode[i]))//界符
				{
					sym.push_back(sourcecode[i]);
					++i;
				}
				else if (isOperators(sourcecode[i]))//运算符
				{

					if (sourcecode[i] == ':' && sourcecode[i + 1] == '=')
					{
						sym.push_back(ASSIN);
						i += 2;
					}
					else if (sourcecode[i] == '<' && sourcecode[i + 1] == '=')
					{
						sym.push_back(LE);
						++i;
					}
					else if (sourcecode[i] == '>' && sourcecode[i + 1] == '=')
					{
						sym.push_back(GE);
						++i;
					}
					else
					{
						sym.push_back(sourcecode[i]);
						++i;
					}
				}
				else
				{
					if (sourcecode[i] != '\0')
					{
						printf("(error,%c)\n", sourcecode[i]);
						if (sourcecode[i + 1] != '\0')
							++i;
					}
					else
						break;
				}
			}
		}
	}
	infile.close();             //关闭文件输入流
}

std::map<string, int> lexer::getIndex()
{
	int j = 0, k = 0;
	int cnt = 0;
	for (int i = 0; i < sym.size(); ++i)
	{
		if (sym[i] == IDENT)
		{
			index[keep[id[j]]] = id[j];
			++j;
		}
		else if (sym[i] == NUMBER)
		{
			if (!index.count(num[k]))
				index[num[k]] = cnt++;
			++k;
		}
	}
	return index;
}

std::vector<string> lexer::getNum()
{
	return num;
}

std::vector<int> lexer::getId()
{
	return id;
}

std::vector<int> lexer::getSym()
{
	return sym;
}