#include "Machine.hpp"

#include <iostream>
#include "Utils.hpp"
#include "RunFlags.hpp"

using namespace std;
using namespace Utils;

void printHeader() {
  cout
    << "  pc  |"
    << "   a  |"
    << "   x  |"
    << "   y  |"
    << endl;
}

void printState(CPU &cpu) {
  cout << " ";
  printDecByte(cpu.pc); cout << " | ";
  printHexByte(cpu.a, 4); cout << " | ";
  printHexByte(cpu.x, 4); cout << " | ";
  printHexByte(cpu.y, 4); cout << " |";
  cout << endl;
}

void Machine::load(Instructions instructions) {
  this->rom = instructions;
}

void Machine::run(Instructions instructions) {
  auto machine = Machine();
  machine.load(instructions);
  machine.run();
}

void Machine::run(unsigned int steps) {
  unsigned int nbInstructions = steps;
  RunFlags::testOutput ? printHeader() : (void) 0;

  while(cpu.pc < rom.size()) {
    auto instruction = rom.at(cpu.pc);
    cpu.compute(instruction, memory);

    RunFlags::testOutput ? printState(cpu) : (void) 0;

    if (steps != 0) {
      nbInstructions--;
      if (nbInstructions == 0) {
        break;
      }
    }
  }
}
