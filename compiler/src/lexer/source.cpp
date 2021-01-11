#include <iostream>
#include <fstream>

#include "lexer.h"

using std::cout;
using std::ifstream;

/* namespace compiler
{
	bool derive_terminal(vector<Token>& string, int& lookahead, Terminal terminal)
	{
		if (string[lookahead].Tag == terminal)
		{
			++lookahead;
			return true;
		}
		return false;
	}

	bool derive_digit(vector<Token>& string, int& lookahead)
	{
		return false;
	}

	bool derive_list(vector<Token>& string, int& lookahead)
	{
		return derive_digit(string, lookahead) &&
			(	(	derive_terminal(string, lookahead, PLUS) ||
					derive_terminal(string, lookahead, MINUS)) &&
				derive_list(string, lookahead) ||
				true);
	}

	bool derive(vector<Token>& string)
	{
		int lookahead = 0;
		return derive_list(string, lookahead) && lookahead == string.size();
	}
} */

using namespace lexer;

int main()
{
	ifstream ifs;
	ifs.open("source.my");
	Lexer lexer(ifs);
	Terminal buf;
	while((buf = lexer.scan().tag) != Terminal::EOF_)
		cout << int(buf) << '\n';
	cout << int(buf) << '\n';
}
