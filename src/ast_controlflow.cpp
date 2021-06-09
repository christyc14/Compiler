#include "ast/ast_controlflow.hpp"
#include "ast/ast_encapsulation.hpp"
#include "ast/ast_function.hpp"

  void While_Loop::printPython(std::ostream& o){
    o << "while (";
    condition->printPython(o);
    o << "):\n";
  //  increase_scope();
    //indent(o);
    statement->printPython(o);
    //decrease_scope();
  }

void While_Loop::storevector(std::vector<std::string>& v){
  v.push_back("while");
  condition->storevector(v);
  statement->storevector(v);
}



void While_Loop::printAssembly(std::ostream &o, Binding *binds){

  std::string startLabel = makeLabel("_StartWhile");
  std::string endLabel = makeSameLabel("_EndWhile");

  Part* part = binds->makeSubPart(makeLabel("_WhileLoop"));

  o << "\n";
  o << startLabel << ":";

  condition->printAssembly(part, o, binds);
  int recpart = part->load();

  o << "\n";
  o << "\t" << "beq" << "\t" << "$" << recpart << ", $0" << ", " << endLabel;

  statement->printAssembly(o, binds);

  o << "\n";
  o << "\t" << "b" << "\t" << startLabel;
  o << "\n";
  o << "\t" << "nop";
  o << "\n";
  o << endLabel << ":";

  part->clear();
}




void Do_While_Loop::printPython(std::ostream& o){
  throw("but wait, that's illegal (dowhile loop, print python)");
}

void Do_While_Loop::storevector(std::vector<std::string>& v){
  v.push_back("do");
  statement->storevector(v);
  v.push_back("while");
  condition->storevector(v);
}

void Forloop::printPython(std::ostream& o){
 throw("no for loop in specificiation hahahahahaahha jokes, for loop, print python");
}

void Forloop::storevector(std::vector<std::string>& v){
  v.push_back("for");
  l->storevector(v);
  m->storevector(v);
  r->storevector(v);
  statement->storevector(v);
}

void Conditional::printPython(std::ostream& o){
  throw("bruh wyd, conditional print python");
}

void Conditional::storevector(std::vector<std::string>& v){
  condition->storevector(v);
  v.push_back("?");
  truex->storevector(v);
  falsex->storevector(v);
}

void Ifelse::printPython(std::ostream& o){
  o<< "if(";
  condition->printPython(o);
  o << "):\n";
  if(truex){
    if(dynamic_cast<Encapsulate*>(truex)){
      truex->printPython(o);
    }
    else{
      increase_scope();
      indent(o);
      truex->printPython(o);
      decrease_scope();
    }
  }
  if(falsex){
    o << "\n";
    indent(o);
    o<< "else:\n";
    if(dynamic_cast<Encapsulate *>(truex)){
      falsex->printPython(o);
    }
    else{
      increase_scope();
      indent(o);
      falsex->printPython(o);
      decrease_scope();
    }
  }
}

void Ifelse::printAssembly(std::ostream &o, Binding *binds){

  if (falsex)
  {

    std::string proto_elselabel = "__else_label_";
    std::string proto_endiflabel = "__endif_label";
    std::string proto_iflabel = "__if_label_";

    std::string iflabel = makeLabel(proto_iflabel);
    std::string elselabel = makeSameLabel(proto_elselabel);
    std::string endiflabel = makeSameLabel(proto_endiflabel);

    Part* part = binds->makeSubPart(makeLabel("_IfLabel"));


    condition->printAssembly(part, o, binds);

    int regpart = part->load(); //Loading from stack into regs with a simple method is the dream :)

    o << "\n";
    o << "\t" << "beq" << "\t" << "$" << regpart << ", $0" << ", " << elselabel;
    o << "\n";
    o << "\t" << "nop";

    truex->printAssembly(o,binds);

    o << "\n";
    o << "\t" << "j" << "\t" << endiflabel;
    o << "\n";
    o << "\t" << "nop";

    o << "\n";
    o << elselabel << ":";

    falsex->printAssembly(o,binds);

    o << "\n";
    o << endiflabel << ":";


  }
  else
  {

    Part* part = binds->makeSubPart(makeLabel("_IfLabel"));
    //std::string proto_iflabel = "__if_label_";
    std::string proto_endiflabel = "__endif_label";
    //std::string iflabel = makeLabel(proto_iflabel);
    std::string endiflabel = makeLabel(proto_endiflabel);

    condition->printAssembly(part, o, binds);

    int regpart = part->load(); //Loading from stack into regs with a simple method is the dream :)

    o << "\n";
    o << "\t" << "beq" << "\t" << "$" << regpart << ", $0" << ", " << endiflabel;
    o << "\n";
    o << "\t" << "nop";

    truex->printAssembly(o,binds);

    o << "\n";
    o << endiflabel << ":";


  }

}

void Ifelse::storevector(std::vector<std::string>& v){
  v.push_back("if");
  condition->storevector(v);
  truex->storevector(v);
  falsex->storevector(v);
}

void Return::printPython(std::ostream& o){
    o << "return ";
    returnex->printPython(o);
}

void Return::storevector(std::vector<std::string>& v){
  v.push_back("return");
  returnex->storevector(v);
}

void Return::printAssembly(std::ostream& o, Binding *binds){
  std::cerr << "return printAssembly" << '\n';
//  o << "lw\t$2,8($fp)";

  if (returnex != NULL){

    std::cerr << "\tReturnex != NULL" << '\n';
    Part* part = binds->makeSubPart(makeLabel("_ReturnLabel"));


    returnex->printAssembly(part, o, binds);
    std::cerr << "\t Done printing RETURNEX, now loading it." << '\n';
    int partreg = part->load();

    if (!dynamic_cast<CallFunction*>(returnex)){

      std::cerr << "Returnex is CallFunctioon" << '\n';
      o << "\n";
      o << "\t" << "move" << "\t" << "$2" << ", $" << partreg;
      part->save();
    }
  }

  o << "\n";
  o << "\t" << "b" << "\t" << return_label << "\n";

}
