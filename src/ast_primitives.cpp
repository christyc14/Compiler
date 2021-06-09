#include "ast/ast_primitives.hpp"

Integer::Integer(int input){

  value = input;
}

int& Integer::access(){
  return value;
}
int Integer::get_size(){
  return bytesize;
}
void Integer::printPython(std::ostream &o) { o << value; }

void Floating::printPython(std::ostream &o){ o<< value;}

void Integer::printAssembly(std::ostream& o, Binding *binds){
  //Sub a = new sub();
  //use this to call void Integer::printAssembly(Sub &sub, std::ostream &o, Binding *binds)???
}

void Integer::printAssembly(Part* sub, std::ostream &o, Binding *binds){

  std::cerr << " Trying to work in an Integer in printasm " << '\n';

  int sub_reg = sub->load();

  o << "\n";
  o << "\t";
  o << "li" << "\t" << "$" << sub_reg << ", " << access(); //I guess $2, but it is for return values only I read it is used on internet? quick note to self to fix in future if wrong

  sub->save();
  //o << "sw" << "\t" << "$2" << ", " << bindings.getFrameStackIndex() << "($fp)"; //need to rec


  //remember to always \n when beginning new row.and always indent with \t !!! except for label and subroutines :)
}

std::string Integer::getType(){

  return type;
}

void Integer::storevector(std::vector<std::string>& v){
  v.push_back(std::to_string(value));
}

void Floating::storevector(std::vector<std::string>& v){
  v.push_back(std::to_string(value));
}

void Character::storevector(std::vector<std::string>& v){
  std::string tmp(1,value);
  v.push_back(tmp);
}

void String::storevector(std::vector<std::string>& v){
  v.push_back(value);
}
