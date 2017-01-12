#include "Utils.hpp"

namespace Utils {
  uint16_t to_uint16(char c) {
    unsigned char uc = c;
    return uint16_t(uc);
  }

  void printDecByte(uint16_t v, unsigned int w) {
    cout << setfill('0') << setw(w) << dec << v;
  }

  void printHexByte(char c, unsigned int w) {
    cout << setfill('0') << setw(w) << hex << to_uint16(c);
  }
}
