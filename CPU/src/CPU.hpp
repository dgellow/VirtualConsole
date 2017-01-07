#ifndef __CPU__
#define __CPU__

#include "Memory.hpp"
#include "Instruction.hpp"

using namespace Instruction6502;

struct CPU {
  CPU() {}
  ~CPU() {}

  void compute(Instruction instruction, Memory memory);

  // Registers
  uint16_t pc = 0;
  uint8_t stack = 0;
  uint8_t a = 0;
  uint8_t x = 0;
  uint8_t y = 0;
  bool c = false;
  bool z = false;
  bool i = false;
  bool d = false;
  bool b = false;
  bool v = false;
  bool s = false;
};

#endif /* __CPU__ */
