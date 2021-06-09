#ifndef ast_unary_hpp
#define ast_unary_hpp

#include "ast_node.hpp"

//like . ++x and x++ are stuff here but they are different.
class UnaryOp : public Node {
private:
  std::string oppa;
  Node* ex;
public:
  UnaryOp(std::string*op, Node* exp);
  void printPython(std::ostream& o);
  void insert(NodePtr n){};
  void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
};

class PostFix_Exp: public Node {
private:
  std::string oppa;
  Node* ex;
public:
  PostFix_Exp(Node* exp, std::string *oppa);
  void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
};
#endif
