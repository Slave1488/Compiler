#include "word.h"

using namespace lexer;

Word::Word(const Terminal& terminal, const std::string& lexeme)
: Token(terminal), lexeme(lexeme)
{}
