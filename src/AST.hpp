#ifndef __AST__
#define __AST__

#include <string>

using namespace std;

enum ASTNodeTypes {
};

class ASTNode {
public:
  virtual ~ASTNode() {}
};

class LabelNode : public ASTNode {
public:
  string label;
  uint32_t position;
};

class InstructionNode : public ASTNode {

};

class AST {
public:
  AST() {}
  ~AST() {}


};

#endif /* __AST__ */
