#ifndef __Machine__
#define __Machine__

#include "CPU.hpp"
#include "Instruction.hpp"
#include "Memory.hpp"
#include "ROM.hpp"

#include <sstream>

using namespace Instruction6502;

struct Machine {
  Machine() {
    cpu = CPU();
    memory = Memory();
  }
  ~Machine() {}

  static void run(Instructions instructions);
  void run(unsigned int steps = 0);
  std::ostringstream ostream();

  CPU cpu;
  ROM rom;
  Memory memory;

private:
  void printState();
  void printExit();
};

#endif /* __Machine__ */
