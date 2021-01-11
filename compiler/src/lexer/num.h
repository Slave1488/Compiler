#pragma once
#include "token.h"

namespace lexer
{
    struct Num: public Token
    {
        const int value;

        Num(const int& value);
    };
}
