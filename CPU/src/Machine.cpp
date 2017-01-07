#include "Machine.hpp"

void Machine::load(Instructions instructions) {
  this->rom = instructions;
}

void Machine::run(Instructions instructions) {
  auto machine = Machine();
  machine.load(instructions);
  machine.run();
}

void Machine::run() {
  while(true) {
    auto instruction = rom.at(cpu.pc);
    cpu.compute(instruction, memory);
  }
}
