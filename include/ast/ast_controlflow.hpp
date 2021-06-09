#ifndef ast_controlflow_hpp
#define ast_controlflow_hpp

#include "ast_node.hpp"


//loops and conditionals and reutnr,
//yes spelling

//while loop

class While_Loop : public Node{
public:
  While_Loop(NodePtr c, NodePtr s): condition(c), statement(s){};
  virtual void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
private:
  NodePtr condition;
  NodePtr statement;
};
//do while loops

class Do_While_Loop : public Node{
public:
  Do_While_Loop(NodePtr c, NodePtr s): condition(c), statement(s){};
  virtual void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds){};
  void storevector(std::vector<std::string>& v);
private:
  NodePtr condition;
  NodePtr statement;
};
//for loops
class Forloop: public Node{
public:
  Forloop(NodePtr left, NodePtr right, NodePtr middle, NodePtr state):l(left), m(middle), r(right), statement(state){};
  virtual void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds){};
  void storevector(std::vector<std::string>& v);
private:
  NodePtr l;
  NodePtr m;
  NodePtr r;
  NodePtr statement;
};

//conditionals
class Conditional: public Node{

public:
  Conditional(NodePtr c, NodePtr t, NodePtr f): condition(c),truex(t),falsex(f){};
  virtual void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds){};
  void storevector(std::vector<std::string>& v);

private:
  NodePtr condition;
  NodePtr truex;
  NodePtr falsex;
};


//if statements
class Ifelse : public Node{

private:
  NodePtr condition;
  NodePtr truex;
  NodePtr falsex = NULL;

public:
  Ifelse(NodePtr c, NodePtr t, NodePtr f): condition(c), truex(t), falsex(f){};
  virtual void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);



};

//jumps
class Return : public Node{

private:
  NodePtr returnex;

public:
  Return(NodePtr r): returnex(r){ std::cerr <<"entered return"<<std::endl; };
  virtual void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);

};


#endif
