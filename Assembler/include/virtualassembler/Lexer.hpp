#ifndef LEXER
#define LEXER

#include "Grammar.hpp"
#include <string>
#include <vector>

struct Lexeme {
	Lexeme(uint32_t position, uint32_t line, Grammar::Tokens token, std::string value = "")
	    : token(token), value(value), position(position), line(line) {}

	~Lexeme() {}

	Grammar::Tokens token;
	std::string value;
	uint32_t position;
	uint32_t line;
};

struct Token {
	Token() {
		token = Grammar::UNASSIGNED;
		value = "";
		position = -1;
		line = -1;
	}

	Token(uint32_t position, uint32_t line, Grammar::Tokens token, std::string value = "")
	    : token(token), value(value), position(position), line(line) {}

	~Token() {}

	Grammar::Tokens token;
	std::string value;
	uint32_t position;
	uint32_t line;
};

using LexemesList = std::vector<std::vector<Lexeme>>;
using TokensList = std::vector<std::vector<Token>>;

namespace Lexer {
TokensList lex(std::ifstream &file);
LexemesList scan(std::ifstream &file);
TokensList eval(LexemesList tokens);
} // namespace Lexer

#endif /* LEXER */
