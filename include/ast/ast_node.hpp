#ifndef ast_node_hpp
#define ast_node_hpp

#include "binding.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>



//Ok so here we COULD define some sort of "base" class for every other thing like AST_FUNCTION e.t.c. This just reduces ambiguitiy as stuff liddat later on.

class Node {


private:


protected:

public:

typedef Node* NodePtr;

  Node();
  virtual ~Node();

  virtual void printPython(std::ostream &o) = 0;

  virtual void printAssembly(std::ostream &o, Binding *binds);
  virtual void printAssembly(Part* sub, std::ostream &o, Binding *binds);
  virtual void printAssembly(Part* sub);




  //void access(); // { return value } Override this and make it return the 'private' value for example in the primitive types (check it out m8).
  //virtual void printAssembly(std::ostream &o) = 0;
  //virtual double& access(){};
  //virtual char& access(){};

  virtual void storevector(std::vector<std::string>& v){};
  virtual void insert(NodePtr in);
  virtual void settype(std::string in);
  virtual void insert(std::string* in);
  virtual void getglobal(std::vector<std::string> &vec);
  virtual std::string getId();
  virtual void allocateVars(std::ostream &o, Binding *binds);
  virtual void allocateVar(std::ostream &o, Binding *binds);
//  virtual void variableregisters(){};
  //virtual void count_variables(int32_t&var){std::cerr << "node count variable" << '\n';};
  virtual void transferArgs(std::vector<Part*> &v, Binding *binds);
//  virtual void variableregisters(std::ostream& o, Binding binds){};
//  virtual void singlereg(std::ostream& o, Binding binds){};

};

extern int scope;
extern bool function_scope;
extern bool global;
extern void increase_scope();
extern void decrease_scope();
extern void indent(std::ostream& o);
extern std::string return_label;
extern int label_number;
extern std::string makeLabel(std::string input);
extern std::string makeSameLabel(std::string input);
extern std::string getLabel();
extern std::vector<std::string> globalvariablenames;
#endif
