#ifndef ast_functions_hpp
#define ast_functions_hpp

#include <cmath>
#include "ast_node.hpp"

class Function : public Node {
private:

  std::string return_type;
  NodePtr par = NULL;
  NodePtr compound_statement = NULL;

public:
  Function(std::string* rttype, NodePtr par_in, NodePtr comp_stat);
  void printAssembly(std::ostream &o, Binding *binds);
  void printPython(std::ostream& o);
  void storevector(std::vector<std::string>& v);
};
/*
class parameterlist: public Node{
private:
  std::vector<const Node*> param_list;
public:
  parameterlist(){};
  parameterlist(const NodePtr par);
  void storevector(std::vector<std::string>& v);
};*/

class CallFunction : public Node{

private:
  NodePtr args = NULL;
  NodePtr id;

public:
  CallFunction(NodePtr idi, NodePtr args_in): id(idi), args(args_in){};
  void printAssembly(std::ostream &o, Binding *binds);
  void printAssembly(Part* part, std::ostream &o, Binding *binds);
  void printPython(std::ostream &o);
  void storevector(std::vector<std::string>& v);


};

#endif
