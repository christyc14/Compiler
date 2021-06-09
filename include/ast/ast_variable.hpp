#ifndef ast_variable_hpp
#define ast_variable_hpp

#include <string>
#include <ostream>
#include <iostream>
#include "ast_node.hpp"

//dont be dumb

class Variable : public Node {

private:

  std::string id;
  std::string type = "Variable";

public:

  Variable(std::string *in);
  void printPython(std::ostream &o);
  std::string getId();
  std::string getType();
  void printAssembly(std::ostream& o, Binding *binds){std::cerr << "variable print assem" << '\n';};
  void printAssembly(Part* sub, std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
};

#endif
