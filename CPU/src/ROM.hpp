#ifndef ROM_
#define ROM_

#include "Instruction.hpp"

#include <vector>

struct ROM {
  ROM() {}
  ~ROM() {}

  void load(Instruction6502::Instructions instructions) { this->instructions = instructions; }

  uint16_t size() {
    auto i = 0;
    for (auto instruction : instructions) {
      i++;
      i += instruction.dataLength;
    }
    return i;
  }

  Instruction6502::Instruction at(uint16_t pc) {
    auto i = 0;
    for (auto instruction : instructions) {
      if (i == pc) {
        return instruction;
      }
      // increment once per instruction
      i++;
      // ... then based on data length
      i += instruction.dataLength;
    }
    throw std::runtime_error("ROM error: instruction not found " + std::to_string(pc));
  }

  Instruction6502::Instructions instructions;
};

#endif /* ROM_ */
