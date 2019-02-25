#include "Lexer.hpp"

#include <fstream>
#include <regex>

TokensList Lexer::lex(std::ifstream &file) {
  auto lexemes = scan(file);
  return eval(lexemes);
}

LexemesList Lexer::scan(std::ifstream &file) {
  file.seekg(file.beg);
  auto lexemes = LexemesList();
  lexemes.emplace_back();

  bool beginComment = false;
  bool inComment = false;
  bool inDigit = false;
  bool inAlpha = false;

  std::string digit = "";
  std::string alpha = "";

  uint32_t position = 0;
  uint32_t line = 1;

  char c;
  while (file.get(c)) {
    position++;

    if (c == '\n') {
      inComment = false;
      line++;
      position = 1;
    }

    if (inComment) {
      continue;
    }

    if (c == '/') {
      if (beginComment) {
        beginComment = false;
        inComment = true;
      } else {
        beginComment = true;
      }
      continue;
    }

    if (std::isdigit(c)) {
      if (inDigit) {
        digit += c;
      } else {
        digit = c;
        inDigit = true;
      }
    } else {
      if (inDigit) {
        lexemes.back().push_back(Lexeme(position, line, Grammar::DIGIT, digit));
      }
      inDigit = false;
    }

    if (std::isalpha(c)) {
      if (inAlpha) {
        alpha += c;
      } else {
        alpha = c;
        inAlpha = true;
      }
    } else {
      if (inAlpha) {
        lexemes.back().push_back(Lexeme(position, line, Grammar::ALPHA, alpha));
      }
      inAlpha = false;
    }

    if (c == ' ') {
      inDigit = false;
      inAlpha = false;
      continue;
    }

    if (c == '@') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::AT_SYM));
      continue;
    }

    if (c == '=') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::EQ_SYM));
      continue;
    }

    if (c == ':') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::COLON_SYM));
      continue;
    }

    if (c == ';') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::SEMICOLON_SYM));
      continue;
    }

    if (c == '&') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::AND_SYM));
      continue;
    }

    if (c == '|') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::OR_SYM));
      continue;
    }

    if (c == '+') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::PLUS_SYM));
      continue;
    }

    if (c == '-') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::MINUS_SYM));
      continue;
    }

    if (c == '!') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::BANG_SYM));
    }

    if (c == '(') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::PARENTOPEN_SYM));
      continue;
    }

    if (c == ')') {
      lexemes.back().push_back(Lexeme(position, line, Grammar::PARENTCLOSE_SYM));
      continue;
    }

    if (c == '\n') {
      lexemes.emplace_back();
    }
  }

  return lexemes;
}

TokensList Lexer::eval(LexemesList lexemesList) {
  auto tokens = TokensList();

  for (auto lexemes : lexemesList) {
    if (lexemes.empty()) {
      continue;
    }

    bool variable = false;
    bool label = false;
    std::string value = "";

    for (size_t i = 0; i < lexemes.size(); i++) {
      auto lexeme = lexemes[i];

      if (lexeme.token == Grammar::AT_SYM) {
        variable = true;
        continue;
      } else if (variable) {
        if (lexeme.token == Grammar::DIGIT || lexeme.token == Grammar::ALPHA) {
          value += lexeme.value;
        } else {
          auto msg = "Lexing error at position " + std::to_string(lexeme.position) + " , line " +
                     std::to_string(lexeme.line) + " : A variable can only use alphanumeric";
          throw std::invalid_argument(msg);
        }
      } else if (lexeme.token == Grammar::PARENTOPEN_SYM) {
        label = true;
        continue;
      } else if (label) {
        if (lexeme.token == Grammar::DIGIT || lexeme.token == Grammar::ALPHA) {
          value += lexeme.value;
        } else if (lexeme.token == Grammar::PARENTCLOSE_SYM) {
          if (i != lexemes.size() - 1) {
            auto l = lexemes[i + 1];
            auto msg = "Lexing error at position " + std::to_string(l.position) + " , line " + std::to_string(l.line) +
                       " : Unexpected character after label declaration";
            throw std::invalid_argument(msg);
          }
        } else {
          auto msg = "Lexing error at position " + std::to_string(lexeme.position) + " , line " +
                     std::to_string(lexeme.line) + " : A label can only use alphanumeric";
          throw std::invalid_argument(msg);
        }
      }
    }

    auto v = std::vector<Token>();
    if (label) {
      v.push_back(Token(lexemes.front().position, lexemes.front().line, Grammar::LABEL, value));
    } else if (variable) {
      v.push_back(Token(lexemes.front().position, lexemes.front().line, Grammar::VARIABLE, value));
    } else {
      for (auto lexeme : lexemes) {
        v.push_back(Token(lexeme.position, lexeme.line, lexeme.token, lexeme.value));
      }
    }
    tokens.push_back(v);
  }

  return tokens;
}
