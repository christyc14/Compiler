#include "ast/ast_node.hpp"

Node::Node(){};
Node::~Node(){};

void Node::settype(std::string in){};
int scope = 0;
bool function_scope;
extern bool global = true;
std::string return_label;

//This is the ultimate hack lmao
void Node::printAssembly(std::ostream &o, Binding *binds){};
void Node::printAssembly(Part* sub, std::ostream &o, Binding *binds){};
void Node::printAssembly(Part* sub){};
void Node::transferArgs(std::vector<Part*> &v, Binding *binds){};
void Node::allocateVars(std::ostream &o, Binding *binds){};
void Node::allocateVar(std::ostream &o, Binding *binds){};

void increase_scope(){

  scope++;
}

void decrease_scope(){

  scope--;
}

void indent(std::ostream& o){

  std::string indentations = std::string(scope, '\t');
  o << indentations;
}
void Node::insert(NodePtr in){};
void Node::insert(std::string *in){};
void Node::getglobal(std::vector<std::string>&vec){};
std::string Node::getId(){};

std::vector<std::string> globalvariablenames;
//Binding printAssembly(std::ostream &o, Binding binds){};

int label_number = 0;
std::string makeLabel(std::string input){

  std::stringstream ss;

  ss << input;
  ss << label_number;

  label_number++;

  return ss.str();

}

std::string makeSameLabel(std::string input){

  std::stringstream ss;

  ss << input;
  ss << (label_number-1);

  return ss.str();
}

std::string getLabel(){

  std::stringstream ss;

  ss << label_number;
  label_number++;

  return  ss.str();
}
