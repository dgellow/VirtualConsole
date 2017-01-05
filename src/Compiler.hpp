#ifndef __Compiler__
#define __Compiler__

#include <string>
#include "Parser.hpp"

namespace Compiler {
  std::string compile(Instructions instructions);
  void debug(Instructions instructions);
}

#endif /* __Compiler__ */
