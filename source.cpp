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

namespace compiler
{
	enum Terminal
	{
		FAIL = -1,
		NUM,
		PLUS,
		MINUS,
		EOF_
	};

	struct Token
	{
		static const Token Fail;
		static const Token Eof;

		const Terminal Tag;

		explicit Token(char sumbol): Token(define(sumbol))
		{
		}
	protected:
		explicit Token(const Terminal& terminal): Tag(terminal)
		{
		}
	private:
		const Terminal define(const char& sumbol) const
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
	const Token Token::Eof = Token(EOF_);

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
			if (!EndOfFile())
			{
				char sumbol = peek;
				is >> peek;
				return Token(sumbol);
			}
			return Token::Eof;
		}
	private:
		istream& is;
		char peek;
		map<std::string, Word> WordTable;

		bool PeekIsSpace() const
		{
			return !EndOfFile() && peek == ' ';
		}

		bool PeekIsDigit() const
		{
			return !EndOfFile() && '0' <= peek && peek <= '9';
		}

		bool EndOfFile() const
		{
			return is.eof();
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
}

using namespace compiler;

int main()
{
	ifstream ifs;
	ifs.open("source.my");
	Lexer lexer(ifs);
	Terminal buf;
	while((buf = lexer.scan().Tag) != EOF_)
		cout << buf << '\n';
	cout << buf << '\n';
}
