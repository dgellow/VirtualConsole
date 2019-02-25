#ifndef PARSER
#define PARSER

#include "Instruction.hpp"
#include <string>

namespace Parser {
Instruction6502::Instructions parseFile(std::ifstream &file);
Instruction6502::Instructions parse(std::string filepath);
} // namespace Parser

#endif /* PARSER */
