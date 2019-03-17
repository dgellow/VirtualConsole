#pragma once

#include <string>

#include "Parser.hpp"

namespace Compiler {
std::string compile(Instructions instructions);
void debug(Instructions instructions);
} // namespace Compiler
