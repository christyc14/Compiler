#include "ast/ast_variable.hpp"


Variable::Variable(std::string *in){
  std::cerr << "variable std::string, variable" << std::endl;
  id = *in;
  delete in;
 std::cerr << "variable constructor entered " << std::endl;
}
void Variable::printPython(std::ostream &o) { o << id; }
std::string Variable::getId() { return id; }

std::string Variable::getType(){

  return type;
}

void Variable::printAssembly(Part* sub, std::ostream &o, Binding *binds){

  std::cerr << " PrintAssembly for Variable " << '\n';
  Part* part = binds->getPart(id);


    std::cerr << " PrintAssembly for Variable Part found" << '\n';

  int sub_reg = sub->load();

  std::cerr << " PrintAssembly for Variable Sub_reg loaded" << '\n';




  int part_reg = part->load();

  std::cerr << " PrintAssembly for Variable Part_reg loaded" << '\n';



    o << "\n";
    o << "\t" << "move" << "\t" << "$" << sub_reg << ", " << "$" << part_reg;
  sub->save();

  std::cerr << " PrintAssembly for Variable sub saved" << '\n';

  part->clear();
  std::cerr << " PrintAssembly for Variable part cleared" << '\n';
}




void Variable::storevector(std::vector<std::string>& v){
  v.push_back(id);
}
