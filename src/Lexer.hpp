#ifndef __Lexer__
#define __Lexer__

#include <vector>
#include <string>
#include "Grammar.hpp"

using namespace Grammar;

struct Lexeme {
  Lexeme(uint32_t position, uint32_t line,
         Tokens token, std::string value="")  {
    this->position = position;
    this->line = line;
    this->token = token;
    this->value = value;
  }

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
  }

  Token(Tokens token, std::string value="")  {
    this->token = token;
    this->value = value;
  }

  ~Token() {}

  Tokens token;
  std::string value;
};

using LexemesList = std::vector<std::vector<Lexeme>>;
using TokensList = std::vector<std::vector<Token>>;

namespace Lexer {
  TokensList lex(std::ifstream &file);
  LexemesList scan(std::ifstream &file);
  TokensList eval(LexemesList tokens);
}

#endif /* __Lexer__ */
