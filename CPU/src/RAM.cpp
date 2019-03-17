#include "virtualcpu/RAM.hpp"

uint8_t RAM::at(uint16_t address) {
  if (address > max) {
    std::string msg = std::string("RAM error: tried to read an address exceeding the addressable RAM.") +
                      " address=" + std::to_string(address) + ", RAM.max=" + std::to_string(max);
    throw std::invalid_argument(msg);
  }

  return state[address];
}

void RAM::set(uint16_t address, uint8_t value) {
  if (address > max) {
    std::string msg = std::string("RAM error: tried to write in an address exceeding the addressable RAM.") +
                      " address=" + std::to_string(address) + ", RAM.max=" + std::to_string(max);
    throw std::invalid_argument(msg);
  }
  state[address] = value;
}
