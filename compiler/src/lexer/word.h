#include "token.h"

namespace lexer
{
    struct Word: public Token
    {
        const std::string lexeme;
    protected:
        Word(const Terminal& terminal, const std::string& lexeme);
    };
}
