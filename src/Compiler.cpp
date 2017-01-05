#include "Compiler.hpp"

#include <bitset>
#include "Grammar.hpp"

using namespace std;

string Compiler::compile(Instructions instructions) {
  string output = "";

  for (auto instruction : instructions) {
    if (instruction.type == AInstruction) {
      output += bitset<16>(instruction.address).to_string();
    } else if (instruction.type == CInstruction) {
      // opcode
      output += "111";

      // cond
      string cond = "";
      for (auto t : instruction.cond) {
        if (t.value != "") {
          cond += t.value;
        } else {
          try {
            auto keyword = Grammar::legalKeyword.at(t.token);
            cond += keyword;
          } catch(const out_of_range e) {
            throw invalid_argument("Compiler error: Invalid keyword in condition of C instruction");
          }
        }
      }

      try {
        auto bits = Grammar::legalCond.at(cond);
        output += bitset<7>(bits).to_string();
      } catch(const out_of_range e) {
        throw invalid_argument("Compiler error: Invalid condition in C instruction");
      }

      // dest
      if (instruction.dest.value.find_first_not_of(Grammar::legalDest) == string::npos) {
        output += instruction.dest.value.find(Grammar::legalDest[0]) != string::npos ? "1" : "0";
        output += instruction.dest.value.find(Grammar::legalDest[1]) != string::npos ? "1" : "0";
        output += instruction.dest.value.find(Grammar::legalDest[2]) != string::npos ? "1" : "0";
      } else {
        throw invalid_argument("Compiler error: Invalid destination in C instruction");
      }

      // jump
      try {
        auto jump = Grammar::legalJump.at(instruction.jump.value);
        output += bitset<3>(jump).to_string();
      } catch(const out_of_range e) {
        throw invalid_argument("Compiler error: Invalid jump in C instruction");
      }
    }

    output += '\n';
  }

  return output;
}

// void Compiler::compile(Instructions instructions, string filepath) {

// }

// void Compiler::compile(Instructions instructions, ofstream &file) {

// }
