#ifndef __RAM__
#define __RAM__

#include <cstdint>
#include <limits>
#include <vector>
#include <string>

struct RAM {
  RAM(unsigned int registerWidth, unsigned int registers) {
    state.resize(registerWidth * registers);
    max = state.size() - 1;
  }

  ~RAM() {}

  void write (uint32_t address, uint16_t value) {
    if (address > max) {
      std::string msg = std::string("Tried to write in an address exceeding the addressable RAM.") +
        " address=" + std::to_string(address) +
        ", RAM.max=" + std::to_string(max);
      throw std::invalid_argument(msg);
    }

    state[address] = value;
  }

  uint16_t read(uint32_t address) {
    if (address > max) {
      std::string msg = std::string("Tried to read an address exceeding the addressable RAM.") +
        " address=" + std::to_string(address) +
        ", RAM.max=" + std::to_string(max);
      throw std::invalid_argument(msg);
    }

    return state[address];
  }

  unsigned int max;
  std::vector<uint16_t> state;
};

#endif /* __RAM__ */
