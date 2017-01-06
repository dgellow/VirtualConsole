#ifndef __RAM16k__
#define __RAM16k__

#include <cstdint>
#include <limits>
#include <vector>
#include <string>

// Memory of 2^14 registers, each 16 bit-wide.
class RAM16k {
public:
  RAM16k() {
    short registerWidth = 16;
    short registers = 16384; // 2^14
    state.resize(registerWidth * registers);
    max = state.size() - 1;
  }

  ~RAM16k() {}

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

private:
  unsigned int max;
  std::vector<uint16_t> state;
};

#endif /* __RAM16k__ */
