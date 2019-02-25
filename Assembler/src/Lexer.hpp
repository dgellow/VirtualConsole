#ifndef LEXER
#define LEXER

#include "Grammar.hpp"
#include <string>
#include <vector>

using namespace Grammar;

struct Lexeme {
  Lexeme(uint32_t position, uint32_t line, Tokens token, std::string value = "")
      : token(token), value(value), position(position), line(line) {}

  ~Lexeme() {}

  Tokens token;
  std::string value;
  uint32_t position;
  uint32_t line;
};

struct Token {
  Token() {
    token = UNASSIGNED;
    value = "";
    position = -1;
    line = -1;
  }

  Token(uint32_t position, uint32_t line, Tokens token, std::string value = "")
      : token(token), value(value), position(position), line(line) {}

  ~Token() {}

  Tokens token;
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
