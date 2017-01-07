#include "Parser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <iomanip>

using namespace Instruction6502;

uint16_t to_uint16(char c) {
  unsigned char uc = c;
  return uint16_t(uc);
}

void printHexByte(char c) {
  cout << setfill('0') << setw(2) << hex << to_uint16(c);
}

void printInstruction(Instruction instruction) {
    cout << opsnames[int(instruction.operation.ops)]
         << " "
         << addressModeSym[int(instruction.operation.addressMode)]
         << " ";
    if (instruction.dataLength > 0) {
      printHexByte(instruction.dataMsb);
      printHexByte(instruction.dataLsb);
    }
    cout << endl;
}

Instructions parseFile(ifstream &file) {
  Instructions instructions;

  // Two first bytes specify the memory location of the program
  char lsbProgramLocation;
  char msbProgramLocation;
  file.get(lsbProgramLocation);
  file.get(msbProgramLocation);

  instructions.push_back(Instruction(Operation(ops::programLocation, opsgroup::other,
                                               addressMode::implied, opsoperand::none),
                                     0, lsbProgramLocation, msbProgramLocation));

  cout << "Program location in memory: ";
  printHexByte(msbProgramLocation);
  printHexByte(lsbProgramLocation);
  cout << endl;

  char c;

  while (file.get(c)) {
    auto ic = to_uint16(c);

    // Get operation based on opcode
    Operation operation;
    try {
      operation = opscodes.at(ic);
    } catch (out_of_range e) {
      cerr << "Parsing error: the byte " << hex << ic
           << " isn't a supported opcode" << endl;
      continue;
    }

    // Read operation data
    int dataLength = 0;
    try {
      dataLength = Instruction6502::dataLength.at(operation.addressMode);
    } catch (out_of_range e) {
      cerr << "Parsing error: no data length found for addressMode "
           << addressModeSym[int(operation.addressMode)]
           << endl;
      continue;
    }

    char lsb = 0;
    char msb = 0;
    if (dataLength == 1) {
      file.get(lsb);
    } else if (dataLength == 2) {
      file.get(lsb);
      file.get(msb);
    }

    // Add instruction to the vector
    auto instruction = Instruction(operation, lsb, msb);
    instructions.push_back(instruction);
    printInstruction(instruction);
  }

  return instructions;
}

Instructions Parser::parse(string filepath) {
  cout << "Parsing ... " << endl;

  ifstream file;
  file.open(filepath, ios::binary);

  if (!file.is_open()) {
    throw runtime_error("Parsing error: cannot read input file: " + filepath);
  }

  auto instructions = parseFile(file);
  file.close();

  return instructions;
}
