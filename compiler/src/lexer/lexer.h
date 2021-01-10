#include <map>

#include "token.h"
#include "word.h"

namespace lexer
{
    class Lexer
	{
	public:
		Lexer(std::istream& is);

		const Token scan();
	private:
		std::istream& is;
		char peek;
		std::map<std::string, Word> WordTable;
	};
}
