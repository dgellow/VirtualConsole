#ifndef __Memory__
#define __Memory__

#include "RAM.hpp"
#include "Screen.hpp"

struct Memory {
  Memory () : ram(8, 64), screen(8, 8) {
  }

  ~Memory() {}

  RAM ram;
  Screen screen;
};

#endif /* __Memory__ */
