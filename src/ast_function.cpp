#include "ast/ast_function.hpp"
#include "ast/ast_variable.hpp"
#include"ast/ast_encapsulation.hpp"
#include "ast/ast_primitives.hpp"


Function::Function(std::string* rttype, NodePtr par_in, NodePtr comp_stat){
  return_type = *rttype;
  delete rttype;
  par = par_in;
  compound_statement = comp_stat;
}

void Function::printPython(std::ostream& o){
  o << "def ";

  if (par){
    par->printPython(o);
  }
  for (int i = 0; i < globalvariablenames.size(); i++){
    o << "\tglobal " << globalvariablenames[i] << "\n";
  }
  if (compound_statement){
    compound_statement->printPython(o);
  }

  o << "\n";
}

void Function::printAssembly(std::ostream &o, Binding *binds){

  std::cerr << "Starting Function printAssembly" << std::endl;
  //std::cerr << "function print assembly " << '\n';
  std::string name = par->getId();
  return_label = "returnLabel_" + name;
//  std::cerr << "got id" << '\n';
  o << ".text\n"
    << ".align 2\n"
    << ".globl " << name << "\n" << "\n";

 //o << ".ent " << name << "\n"; //CHANGE! HERE xxxxxxxxxxxxxxxxxx
  o << ".type " << name << "@function" << "\n\n";

  o << name << ":" << "\n";
  o  << "\taddiu\t$sp, $sp,-8\n"
    <<"\tsw\t$fp, 4($sp)\n"
    <<"\tmove\t$fp, $sp\n";
//determining register variables
    par->allocateVars(o,binds);

    if(compound_statement != NULL){
      function_scope = true;

      o <<"\tsw\t$4, 8($fp)\n"
        <<"\tsw\t$5, 12($fp)\n"
        <<"\tsw\t$6, 16($fp)\n"
        <<"\tsw\t$7, 20($fp)\n";
        //binds->save(o,4);
        std::cerr << "Starting printASM compound statement" << std::endl;
      compound_statement->printAssembly(o,binds);
    }

  o << "\n\tmove" << "\t" << "$sp, $fp\n"
    << "\tlw $fp, 4($sp)\n"
    <<"\taddiu $sp, $sp, 8\n"
    <<"\tjr $31\n"
    <<"\tnop\n";

    binds->reset_binds();

}

void Function::storevector(std::vector<std::string>& v){
  v.push_back(return_type);
//  v.push_back("(");
  if(par){
    par->storevector(v);
  }
  //v.push_back(")");
  //v.push_back("{");
  if(compound_statement){
    compound_statement->storevector(v);
  }
//  v.push_back("}");
}
//////////////////////////////////////////////////////////////////////
/*
parameterlist::parameterlist(const NodePtr par){
  param_list.push_back(par);
}

void parameterlist::storevector(std::vector<std::string>& v){
  for (int i = 0; i < param_list.size(); i++) {
    param_list[i]->storevector(v);
  }
}*/
//////////////////////////////////////////////////////////////////////

void CallFunction::printPython(std::ostream &o){
  std::cerr << "entered call function" << '\n';

  if(dynamic_cast<Variable *>(id)){

    std::cerr << "managed to do dynamic cast in function" << std::endl;
    id->printPython(o);

    o << "(";

    if (args){
      std::cerr << "Printing args for function call" << '\n';
      args->printPython(o);
    }

    o << ")";
  }
  else{
    id->printPython(o);
  }

}

void CallFunction::printAssembly(std::ostream &o, Binding *binds){
  std::cerr << "callfunction printAssemb" << '\n';
  std::vector<Part*> v;
  std::string name = id->getId();
  std::cerr << "id get id" << '\n';

  Part* part = binds->makeSubPart(makeLabel(std::string("_callfunc")));
  std::cerr << "part*" << '\n';
  int partreg = part->load(); //here is a segfault
  std::cerr << "part load" << '\n';

  o << "\n";
  o << "\t" << "move" << "\t" << "$" << partreg << ", " << "$31" << "\n";
  part->save(); // I am  now unsure if we need to send more stuff through reference
  // So that things will add up in the end.




  if(auto x = dynamic_cast<StatementList*> (args)){
    x->transferArgs(v, binds);
  }

  binds->allocateArgs(v);

  o << "\n";
  o << "\t" << "jal" << "\t" << name << "\n" << "\t" << "nop";

  partreg = part->load();

  o << "\n";
  o << "\t" << "move" << "\t" << "$31" << ", " << partreg;

  o << "\n";
  o << "\t" << "move" << "\t" << "$" << partreg << ", " << "$2";
  o << "\n";

  part->save();



  /*int memeory = 16;
  if(v.size() > 4){
    for(int i = 4; i < v.size(); i++){
      if(dynamic_cast<Integer*>(v[i])){
        o << "\tli $2,";
        v[i]->printAssembly(o,binds);
        o << "\n";
        o << "\tsw $2," << memeory << "($sp)";
        memeory += 4;
      }
    }
  }*/
/*  o<< "\tli $7,";
  v[3]->printAssembly(o,binds);
  o << "\tli $6,";
  v[2]->printAssembly(o,binds);
  o << "\tli $5,";
  v[1]->printAssembly(o,binds);
  o << "\tli $4,";
  v[0]->printAssembly(o,binds);

  o << "\tjal " << id << "\n";
  o<< "nop"; */
}

void CallFunction::printAssembly(Part* part, std::ostream &o, Binding *binds){
  std::cerr << "callfunction printAssemb part" << '\n';
  std::vector<Part*> v;
  std::string name = id->getId();

  int partreg = part->load();

  o << "\n";
  o << "\t" << "move" << "\t" << "$" << partreg << ", " << "$31" << "\n";
  part->save(); // I am  now unsure if we need to send more stuff through reference
  // So that things will add up in the end.


  if(auto x = dynamic_cast<StatementList*> (args)){
    x->transferArgs(v, binds);
  }

  binds->allocateArgs(v);

  o << "\n";
  o << "\t" << "jal" << "\t" << name << "\n" << "\t" << "nop";

  partreg = part->load();

  o << "\n";
  o << "\t" << "move" << "\t" << "$31" << ", " << partreg;

  o << "\n";
  o << "\t" << "move" << "\t" << "$" << partreg << ", " << "$2";
  o << "\n";

  part->save();

  o << "\n";
  o << "\t" << "addiu" << "\t" << "$sp, $sp, -4" << "\n";
}

void CallFunction::storevector(std::vector<std::string>& v){
  id->storevector(v);
  //v.push_back("(");
  if(args){
    args->storevector(v);
  }
//  v.push_back(")");
}
