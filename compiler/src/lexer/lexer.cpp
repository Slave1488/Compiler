#include <iostream>

#include "lexer.h"
#include "num.h"

using namespace lexer;

Lexer::Lexer(std::istream& is)
: is(is)
{
    is >> peek;
}

const Token Lexer::scan()
{
    while (!is.eof() && peek == ' ')
    {
        is >> peek;
    }
    if (!is.eof() && isdigit(peek))
    {
        int num = peek - '0';
        is >> peek;
        while (!is.eof() && isdigit(peek))
        {
            num = 10 * num + peek - '0';
            is >> peek;
        }
        return Num(num);
    }
    if (!is.eof())
    {
        char sumbol = peek;
        is >> peek;
        return Token(sumbol);
    }
    return Token::Eof;
}
