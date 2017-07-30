#include "Memory.hpp"
#include "Utils.hpp"

#include <math.h>
#include <iostream>

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

void Memory::debugPrint(uint16_t from, uint16_t count) {
  std::cout << "==========  Debug memory: from=" << from
            << ", count=" << count
            << "  ==========" << std::endl;
  for (auto i = 0; i < count; i++) {
    if (i % 10 == 0) {
      Utils::printHexByte(from + i, 4);
      std::cout << ": ";
    }

    Utils::printDecByte(at(from + i), 4);
    std::cout << " ";

    if (i % 10 == 9) {
      std::cout << endl;
    }
  }
  std::cout << endl;
}
