#include "Compiler.hpp"

#include <bitset>

using namespace std;

string Compiler::compile(Instructions instructions) {
  string output = "";

  for (auto instruction : instructions) {
    if (instruction.type == AInstruction) {
      output += bitset<16>(instruction.address).to_string('0', '1');
    } else if (instruction.type == CInstruction) {
      // opcode
      output += "111";

      // dest
      output += instruction.dest.value.find("A") != string::npos ? "1" : "0";
      output += instruction.dest.value.find("D") != string::npos ? "1" : "0";       output += instruction.dest.value.find("M") != string::npos ? "1" : "0";

      // cond
      // TODO


      // jump
      if (instruction.jump.value == "") {
        output += "000";
      } else if (instruction.jump.value == "JMP") {
        output += "111";
      } else if (instruction.jump.value == "JGT") {
        output += "001";
      } else if (instruction.jump.value == "JEQ") {
        output += "010";
      } else if (instruction.jump.value == "JGE") {
        output += "011";
      } else if (instruction.jump.value == "JLT") {
        output += "100";
      } else if (instruction.jump.value == "JNE") {
        output += "101";
      } else if (instruction.jump.value == "JLE") {
        output += "110";
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
