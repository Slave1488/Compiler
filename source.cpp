#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::istream;
using std::ifstream;
using std::vector;
using std::map;
using std::set;

enum Terminal
{
	FAIL = -1,
	NUM,
	PLUS,
	MINUS
};

struct Token
{
	static const Token Fail;

	const Terminal Tag;

	explicit Token(char sumbol): Token(define(sumbol))
	{
	}
protected:
	explicit Token(Terminal terminal): Tag(terminal)
	{
	}
private:
	Terminal define(char sumbol)
	{
		switch (sumbol)
		{
		case '+':
			return PLUS;
		case '-':
			return MINUS;
		}
		return FAIL;
	}
};

const Token Token::Fail = Token(FAIL);

struct Num: public Token
{
	const int Value;

	Num(int value): Token(NUM), Value(value)
	{
	}
};

struct Word: public Token
{
	const std::string Lexeme;
protected:
	Word(Terminal terminal, std::string lexeme): Token(terminal), Lexeme(lexeme)
	{
	}
};

class Lexer
{
public:
	Lexer(istream& is): is(is)
	{
		is >> peek;
	}

	Token scan()
	{
		while (PeekIsSpace())
		{
			is >> peek;
		}
		if (PeekIsDigit())
		{
			int num = peek - '0';
			is >> peek;
			while (PeekIsDigit())
			{
				num = 10 * num + peek - '0';
				is >> peek;
			}
			return Num(num);
		}
		if (PeekIsSumbol())
		{
			char sumbol = peek;
			is >> peek;
			return Token(sumbol);
		}
		return Token::Fail;
	}
private:
	istream& is;
	char peek;
	map<std::string, Word> WordTable;

	bool PeekIsSpace() const
	{
		return PeekIsSumbol() && peek == ' ';
	}

	bool PeekIsDigit() const
	{
		return PeekIsSumbol() && '0' <= peek && peek <= '9';
	}

	bool PeekIsSumbol() const
	{
		return !is.eof();
	}
};

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

int main()
{
	ifstream ifs;
	ifs.open("source.my");
	Lexer lexer(ifs);
	int buf;
	while((buf = lexer.scan().Tag) != -1)
		cout << buf << '\n';
}
