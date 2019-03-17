#pragma once

#include <string>

#include "Instruction.hpp"

namespace Parser {
Instruction6502::Instructions parseFile(std::ifstream &file);
Instruction6502::Instructions parse(std::string filepath);
} // namespace Parser

