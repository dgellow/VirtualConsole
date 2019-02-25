#ifndef __Compiler__
#define __Compiler__

#include "Parser.hpp"
#include <string>

namespace Compiler {
std::string compile(Instructions instructions);
void debug(Instructions instructions);
} // namespace Compiler

#endif /* __Compiler__ */
