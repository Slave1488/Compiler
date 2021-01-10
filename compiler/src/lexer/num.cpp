#include "num.h"

using namespace lexer;

Num::Num(const int& value)
: Token(Terminal::NUM), value(value)
{}
