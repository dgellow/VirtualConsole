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

  uint8_t at(uint16_t address);
  void set(uint16_t address, uint8_t value);

  unsigned int max;
  std::vector<uint16_t> state;
};

#endif /* __RAM__ */
