#include "token.h"

using namespace lexer;

const Token Token::Fail(Terminal::FAIL);
const Token Token::Eof(Terminal::EOF_);

Token::Token(const char& sumbol)
: Token(define(sumbol))
{}

Token::Token(const Terminal& terminal)
: tag(terminal)
{}

const Terminal Token::define(const char& sumbol) const
{
    switch (sumbol)
    {
    case '+':
        return Terminal::PLUS;
    case '-':
        return Terminal::MINUS;
    }
    return Terminal::FAIL;
}
