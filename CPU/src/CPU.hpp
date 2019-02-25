#ifndef CPU_
#define CPU_

#include "Instruction.hpp"
#include "Memory.hpp"

#include <sstream>

using namespace Instruction6502;

struct CPU {
  CPU() {}
  ~CPU() {}

  void compute(Instruction instruction, Memory &memory);
  std::ostringstream ostream();

  // Registers
  uint16_t pc = 0;
  uint8_t stack = 0xff;
  uint8_t a = 0;
  uint8_t x = 0;
  uint8_t y = 0;
  bool c = false; // Carry
  bool z = false; // Zero
  bool i = false; // Interrupt
  bool d = false; // Decimal
  bool b = false; // Break
  bool v = false; // Overflow
  bool n = false; // Negative
};

#endif /* CPU_ */
