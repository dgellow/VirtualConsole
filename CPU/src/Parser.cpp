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

void parseFile(ifstream &file) {
  vector<Instruction::Operation> operations;

  // Two first bytes specify the memory location of the program
  char lsbProgramLocation;
  char hsbProgramLocation;
  file.get(lsbProgramLocation);
  file.get(hsbProgramLocation);

  cout << "Program location in memory: ";
  printHexByte(hsbProgramLocation);
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

    // Add to the vector
    operations.push_back(operation);

    // Log
    cout << Instruction::opsnames[int(operation.ops)]
         << " "
         << Instruction::addressModeSym[int(operation.addressMode)]
         << " ";
    if (dataLength > 0) {
      printHexByte(msb);
      printHexByte(lsb);
    }
    cout << endl;
  }
}

void Parser::parse(string filepath) {
  cout << "Parsing ... " << endl;

  ifstream file;
  file.open(filepath, ios::binary);

  if (!file.is_open()) {
    throw runtime_error("Parsing error: cannot read input file: " + filepath);
  }

  parseFile(file);
  file.close();
}
