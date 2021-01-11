#pragma once
#include "terminal.h"

namespace lexer
{
    struct Token
    {
        static const Token Fail;
        static const Token Eof;

        const Terminal tag;

        explicit Token(const char& sumbol);
    protected:
        explicit Token(const Terminal& terminal);
    private:
        const Terminal define(const char& sumbol) const;
    };
}
