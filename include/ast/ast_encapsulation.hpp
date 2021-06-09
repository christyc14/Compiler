#ifndef ast_encapsulation_hpp
#define ast_encapsulation_hpp

#include "ast_node.hpp"
#include <vector>


class Encapsulate : public Node {

private:
  NodePtr declarlist = NULL;
  NodePtr statementList = NULL;

protected:
public:

  void printAssembly(std::ostream &o, Binding *binds);
  Encapsulate(NodePtr node): statementList(node){};
  void printPython(std::ostream &o);
  void insert(NodePtr in){};
  Encapsulate(NodePtr lone, NodePtr ltwo);
//  void count_variables(int32_t&var);
//void variableregisters(std::ostream& o, Binding binds);
void storevector(std::vector<std::string>& v);
};

class StatementList : public Node {

private:

  std::vector<NodePtr> list;
  std::string type;

protected:

public:

  StatementList();
  void printPython(std::ostream &o);
  void insert(NodePtr node_in);
  void settype(std::string t);
  void getglobal(std::vector<std::string> &vec);
  void printAssembly(std::ostream &o, Binding *binds);
  //void count_variables(int32_t& var);
  void transferArgs(std::vector<Part*>& v,Binding *binds);
  void allocateVars(std::ostream &o, Binding *binds);
//  void variableregisters(std::ostream& o, Binding binds);
  void storevector(std::vector<std::string>& v);
};

class ExpressionList: public Node {

private:

  std::vector<NodePtr> list;

protected:

public:

  ExpressionList();
  void printPython(std::ostream &o);
  void insert(NodePtr node_in);
  void printAssembly(std::ostream &o, Binding *binds){};
  void storevector(std::vector<std::string>& v);

};



class IdList : public Node{
public:
  IdList();
  void insert(NodePtr in){}
  void insert(std::string *in);
  void printPython(std::ostream& o);
  void printAssembly(std::ostream &o, Binding *binds){};
  void storevector(std::vector<std::string>& v);
private:
  std::vector<std::string> ids;
};

#endif
