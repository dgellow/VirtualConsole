#ifndef __Utils__
#define __Utils__

#include <iostream>
#include <iomanip>

using namespace std;

namespace Utils {
  uint16_t to_uint16(char c);
  void printDecByte(uint16_t v, unsigned int w = 4);
  void printHexByte(char c, unsigned int w = 2);
}

#endif /* __Utils__ */
