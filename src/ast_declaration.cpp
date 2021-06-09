#include "ast/ast_declaration.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_primitives.hpp"

#include <iostream>
#include <ostream>

DirectDeclarator::DirectDeclarator(NodePtr decl, NodePtr param){

  declarations = decl;
  parameters = param;
}

void DirectDeclarator::printPython(std::ostream& o){

  if (declarations){

    declarations->printPython(o);
  }

  o << "(";

  if (parameters){

    parameters->printPython(o);
  }

  o << "):";
  o << "\n";
}

void DirectDeclarator::getglobal(std::vector<std::string>& vec){
  if(dynamic_cast<Variable *>(declarations)){
    vec.push_back(declarations->getId());
  }
}

void DirectDeclarator::allocateVars(std::ostream &o, Binding *binds){
  std::cerr << "allocated DirectDeclarator Vars" << std::endl;
  if (parameters){
    parameters->allocateVars(o, binds);
  }
}

std::string DirectDeclarator::getId() {return declarations->getId();}

// void DirectDeclarator::printAssembly(std::ostream &o, Binding *binds){
// /*  if(declarations){
//     declarations->printAssembly(o, binds);
//   }
//   o << "\n";
//   if(parameters){
//     parameters->printAssembly(o,binds);
//   }
//   o << "\n"; */
//   std::cerr << "DirectDeclarator print asse" << '\n';
//
// }
/*
void DirectDeclarator::variableregisters(){
  if(declarations!=NULL){
    declarations->variableregisters();
  }
}*/

void DirectDeclarator::storevector(std::vector<std::string>& v){
    if(declarations != NULL){
      declarations->storevector(v);
    }
    if(parameters != NULL){
      parameters->storevector(v);
    }
}
////////////////////////////////////////////////////////////////////////
void Declare::printPython(std::ostream& o){
  if(declist != NULL){
    declist->printPython(o);
  }
}

void Declare::getglobal(std::vector<std::string>& vec){
  declist->getglobal(vec);
}

void Declare::printAssembly(std::ostream &o, Binding *binds){

  if (declist){
    declist->printAssembly(o, binds);
  }
}

void Declare::allocateVars(std::ostream &o, Binding *binds){

  if (declist){
    declist->allocateVars(o, binds);
  }
}
/*
void Declare::variableregisters(){
  if(declist!=NULL){
    declist->variableregisters();
  }
}*/

void Declare::storevector(std::vector<std::string>& v){
  if(declist != NULL){
    declist->storevector(v);
  }
}
////////////////////////////////////////////////////////////////////////
void InitDeclare::printPython(std::ostream& o){
  std::cerr << "entered initdeclare printpython" << '\n';
  if(initial != NULL){
    declarator->printPython(o);
    o << " = ";
    initial->printPython(o);
  }
  else{
    declarator->printPython(o);
    o << " = 0";
  }
}

void InitDeclare::getglobal(std::vector<std::string>& vec){
  std::cerr << "Starting InitDeclare getGlobal" << std::endl;
  if(dynamic_cast<Variable *>(declarator)){
    vec.push_back(declarator->getId());
  }
}

  void InitDeclare::printAssembly(std::ostream &o, Binding *binds){

    std::cerr << "Starting InitDeclare printAssembly" << std::endl;

    if (dynamic_cast<Variable*> (declarator)){

      std::string id = declarator->getId();
      int value = 0;


    if (Integer* vol = dynamic_cast<Integer*> (initial)){

      value = vol->access();
      }

      o << "\n";
      o << "\t" << ".globl " << id << "\n";
      o << "\t" << ".data" << "\n";
      o << "\t" << ".align 2" << "\n";
      o << "\t" << ".type " << id << ", " << "@object" << "\n";
      o << "\t" << ".size " << id << ", " << "4" << "\n";
      o << "\t" << id << ":" << "\n";
      o << "\t" << ".word " << value << "\n";

    }
  }

  void InitDeclare::allocateVar(std::ostream &o, Binding *binds){
    std::cerr << "AllocatingVar in InitDeclare" << std::endl;

    std::string id = declarator->getId();
    Part* part;

    std::cerr << "allocate var in InitDeclare" << std::endl;

    if (dynamic_cast<Variable*> (declarator) && dynamic_cast<Integer*> (initial))
    {
      Integer* x = dynamic_cast<Integer*>(initial);
      int value = x->access();

      if (global){ //see if to allocate a global var or not.
        std::cerr << "isGlobal in allocateVar inside Initdeclare" << std::endl;
        part = binds->makeSuperPart(id);
      }
      else
      {
        std::cerr << "isNotGlobal in allocate var inside InitDeclare" << std::endl;
        part = binds->makeSubPart(id);
      }

      int reg = part->load();
      std::cerr << "printing output for allocate var in initdeclare" << std::endl;
      o << "\n";
      o << "\t" << "li" << "\t" << "$" << reg << ", " << value;
      o << "\n";
      std::cerr << "Saving part in AllocateVar inside initdeclare" << std::endl;
      part->save();
    }
    else if (dynamic_cast<DirectDeclarator*> (declarator))
    {
      std::cerr << "dirctdeclarator in allocatevar inside InitDeclare" << std::endl;
    }
    else if (dynamic_cast<Variable*> (declarator) &&  initial == NULL)
    {
      std::cerr << "dirctdeclarator in allocatevar inside Variable is decl and init=NULL" << std::endl;
      if (global){ //see if to allocate a global var or not.
        part = binds->makeSuperPart(id);
      }
      else
      {
        part = binds->makeSubPart(id);
      }
    }
    else
    {
      part = binds->makeSubPart(id);
      initial->printAssembly(o, binds);
    }

  }

/*void InitDeclare::singlereg(std::ostream& o, Binding binds){
  if(declarator && !initial){
    //idk find the right variable and load it idk
    //o << "\tli " <<
  }
}*/

void InitDeclare::storevector(std::vector<std::string>& v){
  if(initial != NULL){
    declarator->storevector(v);
    v.push_back("=");
    initial->storevector(v);
  }
  else{
    declarator->storevector(v);
  }
}
//////////////////////////////////////////////////////////////////////////
void Paramdeclare::printPython(std::ostream& o){
  if(dec){
    dec->printPython(o);
  }
}

void Paramdeclare::printAssembly(std::ostream &o, Binding *binds){
  std::cerr << "Starting Paramdeclare printAssembly" << std::endl;
  if(dec){
    std::cerr << "paramdeclare print assemb" << '\n';
    dec->printAssembly(o,binds);
  }
}

void Paramdeclare::allocateVar(std::ostream &o, Binding *binds){
  std::cerr << "Starting Paramdeclare AllocateVar" << std::endl;
  std::string id = dec->getId();
  Part* part = binds->makeArgPart(id);
}

void Paramdeclare::storevector(std::vector<std::string>& v){
  if(dec){
    dec->storevector(v);
  }
}
