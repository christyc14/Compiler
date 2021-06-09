#include "ast/ast_root.hpp"
#include "ast/ast_declaration.hpp"

TranslationUnit::TranslationUnit(){
  std::cerr << "constructor for translation_unit done" << std::endl;
}

void TranslationUnit::insert(Node* input){

  nodes.push_back(input);
  std::cerr << "insert done " << std::endl;
}

void TranslationUnit::printPython(std::ostream &o){
  for (int i = 0; i < nodes.size(); i++){
    if(dynamic_cast<Declare *>(nodes[i])){
      nodes[i]->getglobal(globalvariablenames);
    }
  }
  for (int i = 0; i < nodes.size(); i++){

    nodes[i]->printPython(o);

    o << "\n";

  }
}

void TranslationUnit::printAssembly(std::ostream &o, Binding *binds){

  //Christy goto http://reliant.colab.duke.edu/c2mips/ if u want to read about
  //Which things to put and to see examples of ops.
  // https://www.cs.unibo.it/~solmi/teaching/arch_2002-2003/AssemblyLanguageProgDoc.pdf
  // There is the handibook for MIPS Assembly m8. Good toilet read. Not dry at all.


  o << ".section .mdebug.abi32" << "\n";
  o  << ".previous" << "\n";
  o  << ".nan	legacy" << "\n";
  o  << ".module	fp=32" << "\n";
  o  << ".module	nooddspreg" << "\n";
  o  << ".abicalls" << "\n";


  for (auto& x : nodes){

    if (dynamic_cast<Declare*>(x))
    {
      x->allocateVars(o, binds);
    }

  }

  global = false;

  for (int i = 0; i < nodes.size(); i++){

    if (nodes[i])
    {
      nodes[i]->printAssembly(o, binds);
    }
  }

  o << "\n\n";
  o << ".set macro" << "\n";
  o << ".set reorder" << "\n";
  //o << ".end f" << "\n";  //Change HERE xxxxxxxxxxxxxxxxxx
  o << ".ident	\"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609\"" << "\n";



}

void TranslationUnit::storevector(std::vector<std::string>& v){
  for (int i = 0; i < nodes.size(); i++) {
    nodes[i]->storevector(v);
  }
}
