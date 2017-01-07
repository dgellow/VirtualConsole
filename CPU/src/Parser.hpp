#ifndef __Parser__
#define __Parser__

#include <string>
#include "Instruction.hpp"

using namespace std;

namespace Parser {
  Instruction6502::Instructions parse(string filepath);
}

#endif /* __Parser__ */
