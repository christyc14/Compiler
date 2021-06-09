#include "binding.hpp"
#include "ast.hpp"
#include <ostream>


/////////////////////////Register//////////////////////////

Register::Register(int in_val = 0, std::string in_name = "", bool in_allocated = false){

  val = in_val;
  name = in_name;
  allocated = in_allocated;
}

int& Register::access_val(){

  return val;
}
std::string Register::access_name(){
//  std::cerr << "register access name" << '\n';
  return name;
}
bool& Register::access_allocated(){
  std::cerr << "register::access_allocated()" << '\n';

  return allocated;
}


void Register::clear(){

  val = 0;
  name = "";
  allocated = false;
}

/////////////////////////Registers/////////////////////////

Registers::Registers(){

  std::vector<Register> regvec;

 for (int i = 0; i < 32; i++){
   Register reg;
   regvec.push_back(reg);
 }

 registers = regvec;

}

Register Registers::getRegister(int input){

  return registers[input];
}

int Registers::findRegister(std::string input){
//std::cerr << "findregister" << '\n';
  for (int i = 0; i < 32; i++){
    //std::cerr << "loop entered " << i << '\n';
  //std::cerr << "registers[i].access_name " << registers[i].access_name() << "\n";
  //std::cerr << "here done" << '\n';
    if (registers[i].access_name() == input){
    //  std::cerr << "access name registers loop: " << i << '\n';
      return i;
    }
  }

  return -1;
}

void Registers::allocate(int in_register, int val, std::string name){

  registers[in_register].access_val() = val;
  registers[in_register].access_name() = name;
  registers[in_register].access_allocated() = true;
}
void Registers::clear(int input){

  registers[input].clear();
}
void Registers::clearAll(){

  for (int i = 0; i < 32; i++){

    registers[i].clear();
  }
}

void Registers::printRegs(){
  std::cerr << "Printing registers" << std::endl;

  for (int i = 0; i < registers.size(); i++){
    std::cerr << "Register " << i << " allocated: " << registers[i].access_allocated() << std::endl;
  }
}

int Registers::findTempReg(){
  std::cerr << "registers::findtempreg" << '\n';

  if (registers[8].access_allocated() == false)
  {
    std::cerr << "if registers[8].access_allocated() == false " << '\n';
    registers[8].access_allocated() = true;
    std::cerr << "access allocate 8" << std::endl;
    return 8;
  }
  else if (registers[9].access_allocated() == false)
  {
    std::cerr << "if registers[9].access_allocated() == false " << '\n';

    registers[9].access_allocated() = true;
    std::cerr << "access allocate 9" << std::endl;
    return 9;
  }
  else if (registers[10].access_allocated() == false)
  {
    std::cerr << "if registers[10].access_allocated() == false " << '\n';

    registers[10].access_allocated() = true;
    std::cerr << "access allocate 10" << std::endl;
    return 10;
  }
  else if (registers[11].access_allocated() == false)
  {
    std::cerr << "if registers[11].access_allocated() == false " << '\n';

    registers[11].access_allocated() = true;
    return 11;
  }
  else if (registers[12].access_allocated() == false)
  {
    std::cerr << "if registers[12].access_allocated() == false " << '\n';

    registers[12].access_allocated() = true;
    return 12;
  }
  else if (registers[13].access_allocated() == false)
  {
    std::cerr << "if registers[13].access_allocated() == false " << '\n';

    registers[13].access_allocated() = true;
    return 13;
  }
  else if (registers[14].access_allocated() == false)
  {
    registers[14].access_allocated() = true;
    return 14;
  }
  else if (registers[15].access_allocated() == false)
  {
    registers[15].access_allocated() = true;
    return 15;
  }
  else if (registers[24].access_allocated() == false)
  {
    registers[24].access_allocated() = true;
    return 24;
  }
  else if (registers[25].access_allocated() == false)
  {
    registers[25].access_allocated() = true;
    return 25;
  }
  else
  {
    std::cerr << "else statement in registers allocated" << '\n';
    return -1;
  }

}
int Registers::findPersistReg(){

  if (registers[16].access_allocated() == false)
  {
    registers[16].access_allocated() = true;
    return 16;
  }
  else if (registers[17].access_allocated() == false)
  {
    registers[17].access_allocated() = true;
    return 17;
  }
  else if (registers[18].access_allocated() == false)
  {
    registers[18].access_allocated() = true;
    return 18;
  }
  else if (registers[19].access_allocated() == false)
  {
    registers[19].access_allocated() = true;
    return 19;
  }
  else if (registers[20].access_allocated() == false)
  {
    registers[20].access_allocated() = true;
    return 20;
  }
  else if (registers[21].access_allocated() == false)
  {
    registers[21].access_allocated() = true;
    return 21;
  }
  else if (registers[22].access_allocated() == false)
  {
    registers[22].access_allocated() = true;
    return 22;
  }
  else if (registers[23].access_allocated() == false)
  {
    registers[23].access_allocated() = true;
    return 23;
  }
  else
  {
    std::cerr << "Implement register spilling for Persistregs to fix" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/////////////////////////Stack/////////////////////////////

Stack::Stack(){

  stack_pointer = 0;
}

void Stack::pushToStack(std::string input){

  increaseStack();
  storage[input] = stack_pointer;
}

int Stack::locatedAt(std::string input){

  return storage[input];
}

void Stack::increaseStack(){

  stack_pointer += 4;
}

void Stack::decreaseStack(){

  stack_pointer -=4;
}

int Stack::getStack(){

  return stack_pointer;
}


/////////////////////////Scope/////////////////////////////

Scope::Scope(){

  count = 0;

}

void Scope::increaseScope(){

  count++;
}
void Scope::decreaseScope(){

  count--;
}
bool Scope::isGlobal(){

  if (count == 0){
    return true;
  }
  else
  {
    return false;
  }

}

/////////////////////////Part*//////////////////////////////

Part::Part(){
  std::cerr << "Hello I am of type Part" << std::endl;
}

Part::~Part(){}


/////////////////////////Sub///////////////////////////////
Sub::Sub(std::ostream &o, Binding *binds){

  std::cerr << "Initializing new Sub::Sub" << std::endl;
  current_binding = binds;
  ov = &o;
  address = binds->get_stack();


  // o << "\n";
  // o << "\t" << "addiu" << "\t" << "$sp, $sp, -4";

}
int& Sub::access_address(){

  return address;
}
void Sub::clear(){

  current_binding->clear(*reg);
  reg = NULL;

  // current_binding->decreaseStack();
  // (*ov) << "\n";
  // (*ov) << "\t" << "addiu" << "\t" << "$sp, $sp, 4";
}
void Sub::save(){

  int offset = access_address();

  (*ov) << "\n";
  (*ov) << "\t" << "sw" << "\t" << "$" << *reg << ", " << -offset << "($fp)";
  (*ov) << "\n";


  clear();
}
int Sub::load(){
  std::cerr << "Loading Sub part." << '\n';

  if (reg){
    std::cerr << "Reg is already assigned (Sub::Load) so returning it: " << *reg << std::endl;
    return *reg;

  }
std::cerr << "Reg is not assigned (Sub::Load) so finding TempReg" << '\n';
// std::cerr << "currentbinding" << current_binding->findTempReg() << '\n';


  reg = new int(current_binding->findTempReg()); //segfault here

  std::cerr << "found temp reg (Sub::Load) " << *reg << '\n';
  std::cerr << "Assigning the found temp reg to the sub" << '\n';
   //here is thee segfault
  std::cerr << "temp reg assigned" << '\n';

  int offset = access_address();
  (*ov) << "\n";
  (*ov) << "\t" << "lw" << "\t" << "$" << *reg << ", "  << -offset << "($fp)";
  (*ov) << "\n";
  return *reg;

}

int& Sub::access_reg(){
  return *reg;
}

void Sub::kopia(Part *part){

  int reg1 = load();
  int reg2 = part->load();

  current_binding->stream() << "\n";
  current_binding->stream() << "\t" << "move" << "\t" << "$" << reg1 << ", $" << reg2;
  current_binding->stream() << "\n";

  part->clear();
  save();

}

/////////////////////////Super/////////////////////////////

Super::Super(std::string id_in, std::ostream &o, Binding *binds){


  id = id_in;
  ov = &o;
  current_binding = binds;

}
int& Super::access_reg(){

  return *reg;
}
void Super::clear(){
  current_binding->regs.clear(*reg);
  reg = NULL;
}
void Super::save(){

  int tmpreg = current_binding->findTempReg();

  if  (tmpreg != -1)
  {

    (*ov) << "\n"; // Using the global offset table function to get the offset of the var label .data
    (*ov) << "\t" << "lw" << "\t" << "$" << tmpreg << ", " << "%got" << "(" << id << ")" << "$(gp)";
    (*ov) << "\n";
    (*ov) << "\n";
    (*ov) << "\t" << "sw" << "\t" << "$" << *reg << ", 0" << "(" << tmpreg << ")";
    (*ov) << "\n";

    current_binding->clear(tmpreg);

  }
  else
  {
    std::cerr << "Ran out of regs in Super save. Implemnt spilling dumbdumb" << std::endl;
    exit(EXIT_FAILURE);
  }
}
int Super::load(){

  if (reg != NULL){
    return *reg;
  }

  *reg = current_binding->findTempReg();
  int tmp_reg = current_binding->findTempReg();

  (*ov) << "\n"; // Using the global offset table function to get the mem offset of the var label .data
  (*ov) << "\t" << "lw" << "\t" << "$" << tmp_reg << ", " << "%got" << "(" << id << ")" << "$(gp)";
  (*ov) << "\n";
  (*ov) << "\n";
  (*ov) << "\t" << "lw" << "\t" << "$" << *reg << ", 0" << "(" << tmp_reg << ")";
  (*ov) << "\n";

    return *reg;
}

void Super::kopia(Part *part){

  int reg1 = load();
  int reg2 = part->load();

  current_binding->stream() << "\n";
  current_binding->stream() << "\t" << "move" << "\t" << "$" << reg1 << ", $" << reg2;
  current_binding->stream() << "\n";

  part->clear();
  save();

}

int& Super::access_address(){
  return tmp;
}

/////////////////////////Binding///////////////////////////

Binding::Binding(std::ostream &o){

  ov = &o;
  std::cerr << "Binding allocated and Initliazed" << std::endl;
  Registers tmpregs;
  regs = tmpregs;

  regs.printRegs();


}

int Binding::findTempReg(){
  std::cerr << "Starting Binding::findTempReg" << '\n';
  int out = regs.findTempReg();
  std::cerr << "Found: " << out << '\n';
  return out; //segfault here
}

int Binding::findPersistReg(){

  return regs.findPersistReg();
}

void Binding::save(std::ostream &o, int input){

  o << "\n";
  o << "\t" <<"sw" << "$" << input << ", " << "-" << the_stack.getStack() << "($fp)";

  regs.clear(input);
}

int Binding::load(std::ostream &o, int input){
  int rego;

  if (!regs.getRegister(input).access_allocated()){



  rego = findTempReg();

  if (rego != -1){

    o << "\n";
    o << "\t" << "lw" << "\t" << "$" << rego << ", " << "-" << the_stack.getStack();
    o << "($fp)";
      return rego;
    }
  }

  else
  {
    return input;
  }
}

int Binding::get_stack(){

  std::cerr << "Getting the stack" << std::endl;
  //return the_stack.getStack();
  int count = 0;

  for (auto &x : sub_Parts){
    count += x.size()*4;
  }

  return count;

}

int Binding::getScope(){
  std::cerr << "Getting scope" << std::endl;
  return sub_Parts.size()-1;
}
void Binding::increaseScope(){
  std::unordered_map<std::string, Part*> tmp;
  sub_Parts.push_back(tmp);
}
void Binding::decreaseScope(){

  int val = getStackDepth(getScope());
  std::cerr << "DecreasingScope. Currently: "<< val << std::endl;

  (*ov) << "\n";
  (*ov) << "\t" << "addiu" << "\t" << "$sp, $sp, " << val;


  sub_Parts.pop_back();
}
int Binding::getStackDepth(int index){
  std::cerr << "Getting stackDepth" << std::endl;
  int depth = sub_Parts[index].size()*4;
  return depth;
}
void Binding::addVariable(std::string name){

  variables[name] = memory_addr;
  memory_addr += 4;
}



int Binding::findVariable(std::string name){

  for (auto &x : variables){

    if (x.first == name){
      return x.second;
    }
    else
    {
      return -1;
    }

  }
}

std::ostream& Binding::stream(){

  return (*ov);
}

int Binding::get_arg_stack(){


  int count = arg_Parts.size();
  std::cerr << "\tGetting argstack. Currently: "<< count*4 << std::endl;
  return count*4;
}

void Binding::allocateArgs(std::vector<Part*> args){

  std::cerr << "\t\t\tAllocating function arguments into stack " << std::endl;

  int count = 0;

  for (auto &x : args){

    std::cerr << "Looping through the arg vector" << std::endl;

    Part* part = makeSubPart(std::string("_arg" + count++));
    part->kopia(x);
  }

  std::cerr << "Printing allocateArgs to outputfile" << std::endl;

  stream() <<  "\t" << "lw" << "\t" << "$4, 4($sp)" << "\n"
                << "\t" << "lw" << "\t" << "$5, 8($sp)" << "\n"
                << "\t" << "lw" << "\t" << "$6, 12($sp)" << "\n"
                << "\t" << "lw" << "\t" << "$7, 16($sp)" << "\n"
                << "\t" << "addiu" << "\t" << "$sp, $sp, 4" << "\n";

}

Part* Binding::getPart(std::string id){

  std::cerr << "Getting Part For: " << id << std::endl;

  std::cerr << "Started iterating through sub_Parts with size: " << sub_Parts.size() << std::endl;
  for (int i = 0; i < sub_Parts.size(); i++){
  auto found = sub_Parts[i].find(id);

  if (found != sub_Parts[i].end()){
    std::cerr << "Found in sub_Parts" << std::endl;
    return found->second;
  }
}

  auto found = super_Parts.find(id);

  if (found != super_Parts.end()){
    std::cerr << "Found in super_Parts" << std::endl;
    return found->second;
  }

  found = arg_Parts.find(id);

  if (found != arg_Parts.end()){
    std::cerr << "Found in arg_Parts" << std::endl;
    return found->second;
  }

  else {

    std::cerr << "Could not find part" << std::endl;
    exit(EXIT_FAILURE);
  }

}
Part* Binding::makeSubPart(std::string id){

  std::cerr << "\t\t\t -> making SubPart for **" << id << std::endl;
  std::cerr << "StackSize Currently " << get_stack() << std::endl;

  (*ov) << "\n";
  (*ov) << "\t" << "addiu" << "\t" << "$sp" << ", " << "$sp" << ", " << "-4";

  Part* part = new Sub((*ov), this);
  sub_Parts.back()[id] = part;
  return part;
}
void Binding::reset_binds(){

  std::cerr << "Resetting binds..." << std::endl;
  while (sub_Parts.size() != 0){
    decreaseScope();
  }
  std::unordered_map<std::string, Part*> tmp;
  sub_Parts.push_back(tmp);
  arg_Parts.clear();
}
Part* Binding::makeArgPart(std::string id){

  std::cerr << "\t\tmaking ArgPart" << std::endl;
  Part* subpart = new Sub((*ov), this);
  subpart->access_address() = (-get_arg_stack() - 8);
  arg_Parts[id] = subpart;
  return subpart;
}
Part* Binding::makeSuperPart(std::string id){

  std::cerr << "\tMaking SuperPart" << std::endl;
  Part* part = new Super(id, (*ov), this);
  super_Parts[id] = part;
  return part;
}

void Binding::clear(int input){
  std::cerr << "**Clear bind** " << input << std::endl;
  regs.clear(input);

}
void Binding::clearAll(){
  std::cerr << "**clearAllBinds**" << std::endl;
  regs.clearAll();
}

// void Binding::setArgPart(std::vector<Part*> args){
//
// }
