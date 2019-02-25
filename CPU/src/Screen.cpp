#include "Screen.hpp"

uint8_t Screen::at(uint16_t address) {}

void Screen::set(uint16_t address, uint8_t value) {}

std::ostringstream Screen::ostream() {
  std::ostringstream os;
  os << "Screen()";
  return os;
}
