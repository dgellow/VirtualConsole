#ifndef __Parser__
#define __Parser__

#include "Instruction.hpp"
#include <string>

using namespace std;

namespace Parser {
Instruction6502::Instructions parseFile(ifstream &file);
Instruction6502::Instructions parse(string filepath);
} // namespace Parser

#endif /* __Parser__ */
