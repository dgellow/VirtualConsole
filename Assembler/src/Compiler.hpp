#ifndef COMPILER
#define COMPILER

#include "Parser.hpp"
#include <string>

namespace Compiler {
std::string compile(Instructions instructions);
void debug(Instructions instructions);
} // namespace Compiler

#endif /* COMPILER */
