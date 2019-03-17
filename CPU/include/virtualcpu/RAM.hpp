#ifndef RAM_
#define RAM_

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

struct RAM {
  RAM(unsigned int registerWidth, unsigned int registers) {
    state.resize(registerWidth * registers * 1024);
    max = state.size() - 1;
  }

  ~RAM() {}

  uint8_t at(uint16_t address);
  void set(uint16_t address, uint8_t value);

  unsigned int max;
  std::vector<uint16_t> state;
};

#endif /* RAM_ */
