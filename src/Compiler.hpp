#ifndef __Compiler__
#define __Compiler__

#include <string>
#include "Parser.hpp"

class Compiler {
public:
  static std::string compile(Instructions instructions);

private:
  Compiler() {}
  ~Compiler() {}
};

#endif /* __Compiler__ */
