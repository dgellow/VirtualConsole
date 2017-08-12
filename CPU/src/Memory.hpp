#ifndef __Memory__
#define __Memory__

#include "RAM.hpp"
#include "Screen.hpp"

#include <sstream>

struct Memory {
  Memory () : ram(8, 32), screen(8, 32) {
  }

  ~Memory() {}

  uint8_t at(uint16_t address);
  void set(uint16_t address, uint8_t value);
  void debugPrint(uint16_t from, uint16_t count);
  std::ostringstream ostream();

  unsigned int ramLastAddress = 0x7ffd;
  unsigned int screenLastAddress = 0xfffe;
  unsigned int keyboardAddress = 0xffff;
  unsigned int stackStartAddress = 0x0100;
  unsigned int stackLastAddress = 0x01ff;

  RAM ram;
  Screen screen;
};

#endif /* __Memory__ */
