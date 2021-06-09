#ifndef ast_root_hpp
#define ast_root_hpp

#include "ast_node.hpp"

class TranslationUnit : public Node {

private:

  std::vector<Node*> nodes;

protected:
public:

  TranslationUnit();
  void insert(Node* input);
  void printPython(std::ostream &o);
  void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);

};

#endif
