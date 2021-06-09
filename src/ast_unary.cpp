#include "ast/ast_unary.hpp"

UnaryOp::UnaryOp(std::string*op, Node* exp): oppa(*op), ex(exp){
  //std::cerr << "unary" << '\n';
delete op;
}
void UnaryOp::printPython(std::ostream& o){
  o << oppa << "(";
  if(ex){
    ex->printPython(o);
  }
  o << ")";
}

void UnaryOp::printAssembly(std::ostream &o, Binding *binds){
  std::cerr << "unaryop print assembly" << '\n';
  if(ex != NULL){
    //std::cerr << "herro" << '\n';
    ex->printAssembly(o,binds);
  }
}

void UnaryOp::storevector(std::vector<std::string>& v){
  v.push_back(oppa);
  if(ex){
    ex->storevector(v);
  }
}

//////////////////////////////////////////////////////////////////////////////////// put my mind at ease, pretty please


PostFix_Exp::PostFix_Exp(Node* exp, std::string* op):ex(exp), oppa(*op){delete op;}

void PostFix_Exp::printPython(std::ostream& o){}

void PostFix_Exp::printAssembly(std::ostream &o, Binding *binds){

  ex->printAssembly(o, binds);
}

void PostFix_Exp::storevector(std::vector<std::string>& v){
  v.push_back(oppa);
  if(ex){
    ex->storevector(v);
  }
}
