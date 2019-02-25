#ifndef __ROM__
#define __ROM__

#include "Instruction.hpp"

#include <vector>

using namespace Instruction6502;

struct ROM {
  ROM() {}
  ~ROM() {}

  void load(Instructions instructions) { this->instructions = instructions; }

  uint16_t size() {
    auto i = 0;
    for (auto instruction : instructions) {
      i++;
      i += instruction.dataLength;
    }
    return i;
  }

  Instruction at(uint16_t pc) {
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
    throw std::runtime_error("ROM error: instruction not found " + to_string(pc));
  }

  Instructions instructions;
};

#endif /* __ROM__ */
