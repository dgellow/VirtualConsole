#ifndef __Compiler__
#define __Compiler__

#include <string>
#include "Parser.hpp"

class Compiler {
public:
  static std::string compile(Instructions instructions);
  // static void compile(Instructions instructions, std::string filepath);
  // static void compile(Instructions instructions, std::ofstream &file);

private:
  Compiler() {}
  ~Compiler() {}
};

#endif /* __Compiler__ */
