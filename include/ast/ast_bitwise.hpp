#ifndef ast_bitwise_hpp
#define ast_bitwise_hpp
#include "ast_node.hpp"

//bitwise stuff
class BitwiseOp : public Node{

private:

  NodePtr left;
  NodePtr right;
  std::string operatorr;

public:

  BitwiseOp(NodePtr l, std::string *opPoint, NodePtr r): left(l), right(r), operatorr(*opPoint){
  delete opPoint;
  };

  void printPython(std::ostream& o);
  void printPythonOp(std::ostream &os);

  void insert(NodePtr n) {};

  void printAssembly(std::ostream &o, Binding *binds);
  void printAssembly(Part* sub, std::ostream &o, Binding *binds);
  void printAssemblyOp(std::ostream &o, Binding *binds, int reg1, int reg2, int reg3);
  void printAssemblyOp(std::ostream &o, Binding *binds, int reg1, int reg2);
  void storevector(std::vector<std::string>& v);
};

class SizeOf : public Node{

public:

  SizeOf(){};
  virtual void printPython(std::ostream& o){};
  void printAssembly(std::ostream &o, Binding *binds){};
  void storevector(std::vector<std::string>& v);
};


#endif
