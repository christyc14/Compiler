#ifndef ast_declaration_hpp
#define ast_declaration_hpp


#include "ast_node.hpp"
#include "ast_primitives.hpp"

//Declarators and stuff rememember to change the name meimei.


class DirectDeclarator : public Node {

private:

  NodePtr declarations;
  NodePtr parameters = NULL;
protected:

public:
  DirectDeclarator(NodePtr decl): declarations(decl) {  std::cerr << "DirectDeclarator done" << std::endl;};
  DirectDeclarator(NodePtr decl, NodePtr param);
  void printPython(std::ostream& o);
  void getglobal(std::vector<std::string>& vec);
  void allocateVars(std::ostream &o, Binding *binds);
  std::string getId();

  //void printAssembly(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);

//  void variableregisters();
};

class Declare : public Node {
public:
  Declare(std::string *sp, NodePtr list_in): spec(*sp),declist(list_in){delete sp;}
  void insert(Node* in){};
  void printPython(std::ostream& o);
  void getglobal(std::vector<std::string>& vec);
  void allocateVars(std::ostream &o, Binding *binds);
  void printAssembly(std::ostream &o, Binding *binds);
//  void variableregisters();
  void storevector(std::vector<std::string>& v);
private:
  std::string spec;
  NodePtr declist;
};

class InitDeclare : public Node{
public:
  InitDeclare(NodePtr dec, NodePtr init): declarator(dec), initial(init){};
  void printPython(std::ostream& o);
  void getglobal(std::vector<std::string> &vec);
  void printAssembly(std::ostream &o, Binding *binds);
  void allocateVar(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
  //void singlereg(std::ostream& o, Binding binds);
private:
  NodePtr declarator;
  NodePtr initial = NULL;
};

class Paramdeclare: public Node{
public:
  Paramdeclare(std::string *st, NodePtr de): decsp(*st), dec(de){delete st;}
  void insert(NodePtr in){}
  void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds);
  void allocateVar(std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
private:
  std::string decsp;
  NodePtr dec;
};


#endif
