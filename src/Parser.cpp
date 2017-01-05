#include "Parser.hpp"
#include "Lexer.hpp"
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

Instructions Parser::parse(string filepath) {
  ifstream file;
  file.open(filepath);
  auto tokens = Lexer::lex(file);
  file.close();

  auto parser = Parser();
  auto symbols = parser.collectSymbols(tokens);
  auto instructions = parser.generateInstructions(tokens, symbols);

  cout << "Symbols table" << endl;
  cout << "=============" << endl;
  for (auto s : symbols) {
    cout << s.first << ": " << s.second << endl;
  }
  cout << endl;

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
        throw std::invalid_argument("Parsing error: The label " + tokens.front().value + " already exists");
      }
    } else {
      i++;
    }
  }

  // Second pass for variables declaration
  for (auto tokens : tokensList) {
    for (auto token : tokens) {
      if (token.token == VARIABLE) {
        if (symbols.find(token.value) == symbols.end()) {
          symbols.emplace(token.value, nextFreeAddress());
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
      auto ainstr = Instruction();
      ainstr.make_A(symbols.at(tokens.front().value));
      instructions.push_back(ainstr);
      continue;
    }

    // C instruction
    auto cinstr = Instruction();
    cinstr.type = CInstruction;
    auto eqpos = find_if(tokens.begin(), tokens.end(),
                         [](const Token & t) -> bool {return t.token == EQ_SYM;});
    auto semicolonpos = find_if(tokens.begin(), tokens.end(),
                                [](const Token & t) -> bool {return t.token == SEMICOLON_SYM;});

    // dest
    if (eqpos == tokens.begin() + 1) {
      auto token = tokens.front();
      if (token.value.find_first_not_of("ADM") == string::npos) {
        cinstr.dest = token;
      } else {
        throw invalid_argument("Parsing error: C instruction destination can only be a combination of A, D or M");
      }
    } else if (eqpos != tokens.end()) {
      throw invalid_argument("Parsing error: '=' is at an invalid position. A valid C instruction should be formatted as 'dest=cond;jump'");
    }

    // jump
    if (semicolonpos == tokens.end() - 2) {
      auto token = tokens.back();
      if (token.value == "JMP" || token.value == "JEQ" || token.value == "JNE"
          || token.value == "JGT" || token.value == "JGE" || token.value == "JLT"
          || token.value == "JLE") {
        cinstr.jump = token;
      } else {
        throw invalid_argument("Parsing error: C instruction jump can only be one of JMP, JEQ, JNE, JGT, JGE, JLT, JLE");
      }
    } else if (semicolonpos != tokens.end()) {
      throw invalid_argument("Parsing error: ';' is at an invalid position. A valid C instruction should be formatted as 'dest=cond;jump'");
    }

    // cond
    vector<Token> cond (eqpos != tokens.end() ? tokens.begin() + 2 : tokens.begin(),
                        semicolonpos != tokens.end() ? tokens.end() - 1 : tokens.end());
    cinstr.cond = cond;
    instructions.push_back(cinstr);
  }
  return instructions;
}
