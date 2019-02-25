#include "Parser.hpp"
#include "Lexer.hpp"
#include <fstream>
#include <map>

using namespace std;

Instructions Parser::parse(string filepath) {
  ifstream file;
  file.open(filepath);
  auto tokens = Lexer::lex(file);
  file.close();

  auto parser = Parser();
  auto symbols = parser.collectSymbols(tokens);
  auto instructions = parser.generateInstructions(tokens, symbols);

  return instructions;
}

SymMap Parser::collectSymbols(TokensList tokensList) {
  auto symbols = makeSymbolsMap();

  // First pass for labels declaration, to handle forward declaration
  auto i = 0;
  for (auto tokens : tokensList) {
    if (tokens.front().token == LABEL) {
      if (symbols.count(tokens.front().value) == 0) {
        symbols.emplace(tokens.front().value, i);
      } else {
        throw std::invalid_argument(string("Parsing error at line ") + to_string(tokens.front().line) + ", position " +
                                    to_string(tokens.front().position) + ": The label " + tokens.front().value +
                                    " already exists");
      }
    } else {
      i++;
    }
  }

  // Second pass for variables declaration
  for (auto tokens : tokensList) {
    for (auto token : tokens) {
      if (token.token == VARIABLE) {
        if (!std::all_of(token.value.begin(), token.value.end(), ::isdigit)) {
          if (symbols.find(token.value) == symbols.end()) {
            symbols.emplace(token.value, nextFreeAddress());
          }
        }
      }
    }
  }

  return symbols;
}

SymMap Parser::makeSymbolsMap() {
  SymMap symbols;
  for (auto i = 0; i <= 15; i++) {
    symbols.emplace("R" + to_string(i), i);
  }
  symbols.emplace("SP", 0);
  symbols.emplace("LCL", 1);
  symbols.emplace("ARG", 2);
  symbols.emplace("THIS", 3);
  symbols.emplace("THAT", 4);
  symbols.emplace("SCREEN", 0x4000);
  symbols.emplace("KBD", 0x6000);
  return symbols;
}

Instructions Parser::generateInstructions(TokensList tokensList, SymMap symbols) {
  auto instructions = Instructions();
  for (auto tokens : tokensList) {
    // A instruction
    if (tokens.front().token == LABEL) {
      continue;
    }

    if (tokens.front().token == VARIABLE) {
      auto ainstr = Instruction(tokens.front().position, tokens.front().line);
      try {
        ainstr.make_A(symbols.at(tokens.front().value));
      } catch (const std::out_of_range e) {
        ainstr.make_A(std::stoi(tokens.front().value));
      }
      instructions.push_back(ainstr);
      continue;
    }

    // C instruction
    auto cinstr = Instruction(tokens.front().position, tokens.front().line);
    cinstr.type = CInstruction;
    auto eqpos = find_if(tokens.begin(), tokens.end(), [](const Token &t) -> bool { return t.token == EQ_SYM; });
    auto semicolonpos =
        find_if(tokens.begin(), tokens.end(), [](const Token &t) -> bool { return t.token == SEMICOLON_SYM; });

    // dest
    if (eqpos == tokens.begin() + 1) {
      auto token = tokens.front();
      cinstr.dest = token;
    } else if (eqpos != tokens.end()) {
      throw invalid_argument(
          string("Parsing error at line ") + to_string(eqpos->line) + ", position " + to_string(eqpos->position) +
          ": '=' is at an invalid position. A valid C instruction should be formatted as 'dest=cond;jump'");
    }

    // jump
    if (semicolonpos == tokens.end() - 2) {
      auto token = tokens.back();
      cinstr.jump = token;
    } else if (semicolonpos != tokens.end()) {
      throw invalid_argument(
          string("Parsing error at line ") + to_string(semicolonpos->line) + " position " +
          to_string(semicolonpos->position) +
          ": ';' is at an invalid position. A valid C instruction should be formatted as 'dest=cond;jump'");
    }

    // cond
    vector<Token> cond(eqpos != tokens.end() ? tokens.begin() + 2 : tokens.begin(),
                       semicolonpos != tokens.end() ? tokens.end() - 2 : tokens.end());
    cinstr.cond = cond;
    instructions.push_back(cinstr);
  }
  return instructions;
}
