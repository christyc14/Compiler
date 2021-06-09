#include "ast/ast_bitwise.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_function.hpp"


void BitwiseOp::printPython(std::ostream& o){
  o << "(";
  left->printPython(o);
  printPythonOp(o);
  right->printPython(o);
  o << ")";
}

void BitwiseOp::storevector(std::vector<std::string>& v){
  left->storevector(v);
  v.push_back(operatorr);
  right->storevector(v);
}

void BitwiseOp::printPythonOp(std::ostream& os){
    if (operatorr == "&&") {
      os << ") and (";
    } else if (operatorr == "||") {
      os << ") or (";
    } else {
      os << ") " << operatorr << " (";
    }
}

void BitwiseOp::printAssembly(std::ostream &o, Binding *binds){

  if (auto x = dynamic_cast<Variable*>(left)){

    std::cerr << "\t\t\t BitWise printASM dynamic cast successful " << '\n';

    std::string name = x->getId();
    std::cerr << "left get id" << '\n';
  //  int rego = binds->findRegister(name);
    Part* rleft = binds->getPart(name);
    //int rleft = binds->regs.findRegister(name);
    //std::cerr << "binds->regs.findreg" << '\n';
    //Gonna implement the algorithm for correct arithmethic here tmrw. Then first test should
    //Work since it will be called upon correctly.w
    std::string rname = makeLabel("_RightPartLabel");
    Part* rright = binds->makeSubPart(rname);

    std::cerr << "  printing right in Bitwise" << '\n';

    if (right){
      std::cerr << "Right in bitwise is not NULL" << std::endl;
      right->printAssembly(rright, o, binds);
    }

    std::cerr << "Loading left in bitwise" << std::endl;
    int reg1 = rleft->load();
    std::cerr << "Loading right in bitwise" << std::endl;
    int reg2 = rright->load();

    printAssemblyOp(o, binds, reg1, reg2);
//Remember void allocate(int in_register, int val, std::string name);
    std::cerr << "Saving left in bitwise" << std::endl;
    rleft->save();
    std::cerr << "Clearing right in bitwise" << std::endl;
    rright->clear();
  //  binds->regs.allocate(LReg, right->access(), left->getId());
  //  binds->regs.allocate(RReg, right->access(), "temp")://remember to name all non-importnt temp registers to temp.

  }
  else
  {
    std::cerr << "Not implemented other type than right being Integer yet" << std::endl;
  }

}

void BitwiseOp::printAssembly(Part* sub, std::ostream &o, Binding *binds){

  std::cerr << "\t\t\t BitWiseOP printing" << '\n';
  // Sub rleft(binds->get_stack(), o, binds);
  // Sub rright(binds->get_stack(), o, binds);
  std::string lname = makeLabel("_LeftPartLabel");
  std::string rname = makeLabel("_RightPartLabel");


  Part* rleft = binds->makeSubPart(lname);
  Part* rright = binds->makeSubPart(rname);

  std::cerr << "\ttrying to print left in Bitwise" << '\n';

  if (left){
    std::cerr << "left printasm in bitwise" << '\n';
    left->printAssembly(rleft, o, binds);
  }
  std::cerr << "\ttrying to print right in Bitwise" << '\n';
  if (right){
    std::cerr << "right printasm in bitwise" << '\n';
    right->printAssembly(rright, o, binds);
  }

  std::cerr << "\t\t Loading reg1, reg2, reg3 in BitWiseOp Print asm" << '\n';
  int reg1 = sub->load();
  int reg2 = rleft->load();
  int reg3 = rright->load();


  printAssemblyOp(o, binds, reg1, reg2, reg3);

  std::cerr << "\t\t clearing reg2, reg3 - Saving reg1 in BitWiseOp Print asemmbly" << '\n';
  rleft->clear();
  rright->clear();
  sub->save();

std::cerr << "\t\t Ending of bitwise printasmop 3regs" << '\n';

}

void BitwiseOp::printAssemblyOp(std::ostream &o, Binding *binds, int reg1, int reg2){

  std::cerr << "\t\t Finding Operator in BitwiseOpPrintAssemblyOp" << '\n';

  if (operatorr == "="){

    o << "\n";
    o << "\t";
    o << "move" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;

  }
  else if(operatorr == "+=")
  {
    o << "\n";
    o << "\t";
    o << "addu" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
  }
  else if(operatorr == "-=")
  {
    o << "\n";
    o << "\t";
    o << "subu" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
  }
  else if(operatorr == "*=")
  {
    o << "\n";
    o << "\t";
    o << "multu" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
    o << "\n";
    o << "\t" << "mflo" << "\t" << "$" << reg1;
  }
  else if(operatorr == "/=")
  {
    o << "\n";
    o << "\t";
    o << "divu" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
    o << "\n";
    o << "\t" << "mflo" << "\t" << "$" << reg1;
  }
  else if(operatorr == "%=")
  {
    o << "\n";
    o << "\t";
    o << "multu" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
    o << "\n";
    o << "\t" << "mfhi" << "\t" << "$" << reg1;
  }
  else if(operatorr == "<<=")
  {
    o << "\n";
    o << "\t";
    o << "sllv" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;

  }
  else if(operatorr == ">>=")
  {
    o << "\n";
    o << "\t";
    o << "srlv" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
  }
  else if(operatorr == "&=")
  {
    o << "\n";
    o << "\t";
    o << "and" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
  }
  else if(operatorr == "|=")
  {
    o << "\n";
    o << "\t";
    o << "or" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
  }
  else if(operatorr == "^=")
  {
    o << "\n";
    o << "\t";
    o << "xor" << "\t";
    o << "$" << reg1 << ", ";
    o << "$" << reg1 << ", ";
    o << "$" << reg2;
  }
}

//http://www.cburch.com/cs/330/reading/mips-ref.pdf
//yo christy you can use this table to implement everything.

void BitwiseOp::printAssemblyOp(std::ostream &o, Binding *binds, int reg1, int reg2, int reg3){

  if (operatorr == "+")
  {
    o << "\n";
    o << "\t" << "addu" << "\t" << "$" << reg1 << ", ";
    o << "$" << reg2 << ", " << "$" << reg3;
  }
  else if (operatorr == "-")
  {
    o << "\n";
    o << "\t" << "subu" << "\t" << "$" << reg1 << ", ";
    o << "$" << reg2 << ", " << "$" << reg3;
  }
  else if (operatorr == "*")
  {
    o << "\n";
    o << "\t" << "multu" << "\t" << "$" << reg2 << ", " << "$" << reg3;
    o << "\n";
    o << "\t" << "mflo" << "\t" << "$" << reg1;
  }
  else if (operatorr == "/")
  {
    o << "\n";
    o << "\t" << "divu" << "\t" << "$" << reg2 << ", " << "$" << reg3;
    o << "\n";
    o << "\t" << "mflo" << "\t" << "$" << reg1;
  }
  else if (operatorr == "%")
  {
    o << "\n";
    o << "\t" << "divu" << "\t" << "$" << reg2 << ", " << "$" << reg3;
    o << "\n";
    o << "\t" << "mfhi" << "\t" << "$" << reg1;
  }
  else if (operatorr == "<<")
  {
    o << "\n";
    o << "\t" << "sllv" << "\t" << "$" << reg1 << ", $" << reg2 << ", $" << reg3;
  }
  else if (operatorr == ">>")
  {
    o << "\n";
    o << "\t" << "srlv" << "\t" << "$" << reg1 << ", $" << reg2 << ", $" << reg3;
  }
  else if (operatorr == "^")
  {
    o << "\n";
    o << "\t" << "xor" << "\t" << "$" << reg1 << ", $" << reg2 << ", $" << reg3;
  }
  else if (operatorr == "&")
  {
    o << "\n";
    o << "\t" << "and" << "\t" << "$" << reg1 << ", $" << reg2 << ", $" << reg3;
  }
  else if (operatorr == "|")
  {
    o << "\n";
    o << "\t" << "or" << "\t" << "$" << reg1 << ", $" << reg2 << ", $" << reg3;
  }
  else if (operatorr == "=="){

    std::string UnEqualLabel = makeLabel("_UnEqualLabel");
    std::string EndLabel = makeLabel("_EndLabel");

    o << "\n";
    o << "\t" << "subu" << "\t" << "$" << reg2 << ", $" << reg2 << ", $" << reg3;
    o << "\n";
    o << "\t" << "bne" << "\t" << "$0" << ", $" << reg2 << ", " << UnEqualLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";
    o << "\t" << "addiu" << "\t" << "$" << reg1 << ", $0" << ", 1";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";
    o << UnEqualLabel << ":";
    o << "\n";
    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";
    o << "\n";
    o << EndLabel << ":";

  }
  else if (operatorr == "!=")
  {

    std::string EqualLabel = makeLabel("_UnEqualLabel");
    std::string EndLabel = makeLabel("_EndLabel");

    o << "\n";
    o << "\t" << "subu" << "\t" << "$" << reg2 << ", $" << reg2 << ", $" << reg3;
    o << "\n";
    o << "\t" << "beq" << "\t" << "$0" << ", $" << reg2 << ", "<< EqualLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";
    o << "\t" << "addiu" << "\t" << "$" << reg1 << ", $0" << ", 1";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";
    o << EqualLabel << ":";
    o << "\n";
    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";
    o << "\n";
    o << EndLabel << ":";

  }
  else if (operatorr == "<")
  {

    o << "\n";
    o << "\t" << "slt" << "\t" << "$" << reg1 << ", $" << reg2 << ", $" << reg3;


  }
  else if (operatorr == ">")
  {

    o << "\n";
    o << "\t" << "slt" << "\t" << "$" << reg1 << ", $" << reg3 << ", $" << reg2;

  }
  else if (operatorr == ">=")
  {

    std::string EndLabel = makeLabel("_endLabel");
    std::string metCond = makeLabel("_metLabel");

    o << "\n";
    o << "\t" << "bge" << "\t" << "$" << reg2 << ", $" << reg3 << ", " << metCond;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";

    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";

    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";

    o << metCond << ":";
    o << "\n";
    o << "\t" << "addiu" << "\t" << "$" << reg1 << ", $0" << ", " << "1";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";

    o << EndLabel << ":";

  }
  else if (operatorr == "<=")
  {

    std::string EndLabel = makeLabel("_endLabel");
    std::string metCond = makeLabel("_metLabel");

    o << "\n";
    o << "\t" << "ble" << "\t" << "$" << reg2 << ", $" << reg3 << ", " << metCond;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";

    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";

    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";

    o << metCond << ":";
    o << "\n";
    o << "\t" << "addiu" << "\t" << "$" << reg1 << ", $0" << ", " << "1";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";

    o << EndLabel << ":";

  }
  else if (operatorr == "||")
  {

    std::string MetLabel = makeLabel("_MetLabel");
    std::string EndLabel = makeLabel("_EndLabel");

    o << "\n";
    o << "\t" << "addu" << "\t" << "$" << reg2 << ", $" << reg2 << ", $" << reg3;
    o << "\n";
    o << "\t" << "beq" << "\t" << "$" << reg2 << ", $0" << ", " << MetLabel;
    o << "\n";
    o << "\t" << "nop" << "\n";
    o << "\t" << "addiu" << "\t" << "$" << reg1 << ", $0" << ", " << "1";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop";
    o << "\n";
    o << MetLabel << ":";
    o << "\n";
    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";
    o << "\n";
    o << EndLabel << ":";

  }
  else if (operatorr == "&&")
  {
    std::string CheckLabelFirst = makeLabel("_FirstLabel");
    std::string CheckLabelSecond = makeLabel("_SecondLabel");
    std::string EndLabel = makeLabel("_EndLabel");

    o << "\n";
    o << "\t" << "bne" << "\t" << "$" << reg2 << ", $0" << ", " << CheckLabelFirst;
    o << "\n";
    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << CheckLabelFirst << ":";
    o << "\n";
    o << "\t" << "nop" << "\n";
    o << "\n";
    o << "\t" << "bne" << "\t" << "$" << reg3 << ", $0" << ", " << CheckLabelSecond;
    o << "\n";
    o << "\t" << "move" << "\t" << "$" << reg1 << ", $0";
    o << "\n";
    o << "\t" << "j" << "\t" << EndLabel;
    o << "\n";
    o << "\t" << "nop" << "\n";
    o << "\n";
    o << CheckLabelSecond << ":";
    o << "\n";
    o << "\t" << "addiu" << "\t" << "$" << reg1 << ", $0" << ", " << "1";
    o << "\n";
    o << EndLabel << ":";
  }


  //add more  for print assembly
}

void SizeOf::storevector(std::vector<std::string>& v){
  v.push_back("SizeOf");
}
