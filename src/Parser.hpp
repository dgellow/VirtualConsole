#ifndef __Parser__
#define __Parser__

#include <string>
#include <map>
#include <vector>
#include "Lexer.hpp"

using namespace std;

using SymMap = map<string, uint32_t>;

enum InstructionTypes {
  CInstruction,
  AInstruction,
};

struct Instruction {
  Instruction() {};
  ~Instruction() {};

  void make_A(uint32_t address) {
    this->type = AInstruction;
    this->address = address;
  }

  void make_C(Token dest, vector<Token> cond, Token jump) {
    this->type = CInstruction;
    this->dest = dest;
    this->cond = cond;
    this->jump = jump;
  }


  InstructionTypes type;

  uint32_t address = 0; // <- A

  Token dest; // <- C
  vector<Token> cond; // <- C
  Token jump; // <- C
};

using Instructions = vector<Instruction>;

class Parser {
public:
  static Instructions parse(string filepath);

  SymMap makeSymbolsMap();
  SymMap collectSymbols(TokensList tokens);

  Instructions parseLine(string line);
  Instructions generateInstructions(TokensList tokens, SymMap symbols);

private:
  Parser() {};
  ~Parser() {};

  uint32_t nextFreeAddress () {
    freeAddress++;
    return freeAddress;
  }

  uint32_t freeAddress = 15;
};

#endif /* __Parser__ */
