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
#define CONSTSYM 128 
#define VARSYM 129
#define PROSYM 130
#define BEGINSYM 131
#define ENDSYM 132
#define IFSYM 133
#define THENSYM 134
#define CALLSYM 135
#define WHILESYM 136
#define DOSYM 137
#define READSYM 138
#define WRITESYM 139
#define ODDSYM 140

using namespace std;

class lexer
{
public:
	lexer(std::string filename);
	std::map<string, int> getIndex();
	std::vector<string> getNum();
	std::vector<int> getId();
	std::vector<int> getSym();
	int getToken();
	int keepToken();
	void resetToken(int reset);
	void pushToken();
private:
	int tokenInx = 0;
	std::vector<string> num, keep;
	std::vector<int> sym, id;
	std::map<string, int> index;
};