#ifndef __Screen__
#define __Screen__

#include "RAM.hpp"

struct Screen : RAM {
  Screen(unsigned int registerWidth, unsigned int registers)
    : RAM(registerWidth, registers) {
  }

  ~Screen() {}
};

#endif /* __Screen__ */
