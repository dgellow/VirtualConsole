#ifndef __Machine__
#define __Machine__

#include "Instruction.hpp"
#include "CPU.hpp"
#include "Memory.hpp"

using namespace Instruction6502;

struct Machine {
  Machine() {
    cpu = CPU();
    memory = Memory();
  }
  ~Machine() {}

  static void run(Instructions instructions);
  void run();
  void load(Instructions instructions);

  CPU cpu;
  Memory memory;

  Instructions rom;
};

#endif /* __Machine__ */
