#include <iostream>
#include <fstream>
#include <vector>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"

using namespace std;

int main () {
  std::string filepath = "./test.asm";

  std::ifstream file;
  file.open(filepath);
  auto tokens = Lexer::lex(file);
  file.close();

  cout << "Lexer" << std::endl;
  cout << "==================="
       << std::endl;

  for (auto line : tokens) {
    for (auto lexeme : line) {
      if (lexeme.value == "") {
        std::cout << lexeme.token;
      } else {
        std::cout << "{" << lexeme.token << ", " << lexeme.value << "}";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
  cout << endl;

  auto instructions = Parser::parse(filepath);

  cout << "Parser" << endl;
  cout << "==================="
       << endl;

  for (auto instruction : instructions) {
    if (instruction.type == CInstruction) {
      std::string cond = "";
      for (auto c : instruction.cond) {
        cond += (c.value == "" ? "_" +  to_string(c.token) + "_" : c.value);
      }
      cout << instruction.dest.value
           << (instruction.dest.value == "" ? "" :  "=")
           << cond
           << (instruction.jump.value == "" ? "" : ";")
           << instruction.jump.value
           << endl;
    } else if (instruction.type == AInstruction) {
      cout << "@" << instruction.address << endl;
    } else {
      cerr << "cannot cast" << endl;
    }
  }
  cout << endl;

  cout << "Compiler" << endl;
  cout << "==================="
       << endl;
  cout << Compiler::compile(instructions);
  cout << endl;

  // cout << Compiler::compile(ast);
  return 0;
}
