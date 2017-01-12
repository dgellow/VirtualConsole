#include "Memory.hpp"

#include <math.h>

uint8_t Memory::at(uint16_t address) {
  if (address <= ramLastAddress) {
    return ram.at(address);
  } else if (address <= screenLastAddress) {
    return screen.at(address);
  } else {
    throw std::out_of_range("Memory error: address "
                            + std::to_string(address)
                            + " out of range");
  }
}

void Memory::set(uint16_t address, uint8_t value) {
  if (address <= ramLastAddress) {
    ram.set(address, value);
  } else if (address <= screenLastAddress) {
    screen.set(address, value);
  } else {
    throw std::out_of_range("Memory error: address "
                            + std::to_string(address)
                            + " out of range");
  }
}
