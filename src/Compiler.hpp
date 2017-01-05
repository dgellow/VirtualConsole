#ifndef __Compiler__
#define __Compiler__

#include <string>
#include "AST.hpp"

class Compiler {
public:
  static std::string compile(AST ast);
  static void compile(AST ast, std::string filepath);
  static void compile(AST ast, std::ofstream &file);

private:
  Compiler() {}
  ~Compiler() {}
};

#endif /* __Compiler__ */
