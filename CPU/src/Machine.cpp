#include "Machine.hpp"

#include "RunFlags.hpp"
#include "Utils.hpp"
#include <iostream>

using namespace std;
using namespace Utils;

void printHeader() {
  cout << "  pc  |"
       << "  a |"
       << "  x |"
       << "  y |"
       << " c |"
       << " z |"
       << " i |"
       << " d |"
       << " b |"
       << " v |"
       << " n |" << endl;
}

string boolToStr(bool b) { return b ? "✓" : " "; }

void Machine::printState() {
  cout << " " << sstreamHexByte(cpu.pc, 4).str() << " |"
       << " " << sstreamHexByte(cpu.a).str() << " |"
       << " " << sstreamHexByte(cpu.x).str() << " |"
       << " " << sstreamHexByte(cpu.y).str() << " |"
       << " " << boolToStr(cpu.c) << " |"
       << " " << boolToStr(cpu.z) << " |"
       << " " << boolToStr(cpu.i) << " |"
       << " " << boolToStr(cpu.d) << " |"
       << " " << boolToStr(cpu.b) << " |"
       << " " << boolToStr(cpu.v) << " |"
       << " " << boolToStr(cpu.n) << " |" << endl;
}

void Machine::printExit() {
  cout << endl << "End of the rom reached" << endl << cpu.ostream().str() << memory.ostream().str() << endl;
}

void Machine::run(Instructions instructions) {
  auto machine = Machine();
  machine.rom.load(instructions);
  machine.run();
}

void Machine::run(unsigned int steps) {
  unsigned int nbInstructions = steps;
  RunFlags::testOutput ? printHeader() : (void)0;

  while (cpu.pc < rom.size()) {
    auto instruction = rom.at(cpu.pc);
    cpu.compute(instruction, memory);

    RunFlags::testOutput ? printState() : (void)0;

    if (steps != 0) {
      nbInstructions--;
      if (nbInstructions == 0) {
        break;
      }
    }
  }

  RunFlags::testOutput ? printExit() : (void)0;
}

std::ostringstream Machine::ostream() {
  std::ostringstream os;
  os << "Machine()";
  return os;
}
