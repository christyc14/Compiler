#ifndef binding_hpp
#define binding_hpp

#include <map>
#include <iostream>
#include <ostream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>


class Binding;


class Register {

private:

  int val;
  std::string name;
  bool allocated = false;

public:

  Register(int in_val, std::string in_name, bool in_allocated);
  int& access_val();
  std::string access_name();
  bool& access_allocated();

  void clear();


};

class Registers { //viva la naming convention

private:

  std::vector<Register> registers;

public:

  Registers();
  Register getRegister(int input);
  void printRegs();
  int findRegister(std::string input); //for finding reg of var.
  void allocate(int in_register, int val, std::string name);
  void clear(int input);
  void clearAll();
  int findTempReg();
  int findPersistReg();

};

class Stack {

private:

  std::map<std::string, int> storage;
  int stack_pointer;


public:

  int getStack();
  Stack();
  void pushToStack(std::string input);
  int locatedAt(std::string input);
  void increaseStack();
  void decreaseStack();


};

class Scope {

private:

  int count;

public:

  Scope();
  void increaseScope();
  void decreaseScope();
  bool isGlobal();


};

class Part {


public:

  Part();
  virtual ~Part();


  virtual void kopia(Part *part) = 0;
  virtual int& access_address() = 0;
  virtual int& access_reg() = 0;
  virtual void clear()  = 0;
  virtual void save() = 0;
  virtual int load() = 0;

};


class Sub : public Part {

private:

  int address;
  Binding *current_binding;
  std::ostream *ov;
  int *reg = NULL;

public:

  Sub(std::ostream &o, Binding *binds);
  void kopia(Part *part);
  int& access_address();
  int& access_reg();
  void clear();
  void save();
  int load();

};

class Super : public Part {

private:

  int tmp = -1;
  Binding *current_binding;
  std::ostream *ov;
  std::string id;
  int *reg = NULL;

public:

  Super(std::string id_in, std::ostream &o, Binding *binds);
  int& access_reg();
  int& access_address();
  void clear();
  void save();
  void kopia(Part *part);
  int load();

};


class Binding {


public:
  //public properties

  std::unordered_map<std::string, int> variables;
  Registers regs;
  std::ostream *ov;
  Stack the_stack;
  int memory_addr = 0;
  Scope scope;

  std::unordered_map<std::string, Part*> super_Parts;
  std::vector< std::unordered_map<std::string, Part*> > sub_Parts;
  std::unordered_map<std::string, Part*> arg_Parts;


  //public methods

  Binding(std::ostream &o);

  int get_stack();
  int get_arg_stack();
  void increaseScope();
  std::ostream& stream();
  void decreaseScope();
  void allocateArgs(std::vector<Part*> args);
  int getScope();
  void addVariable(std::string name);
  int findVariable(std::string name);
  Part* getPart(std::string id);
  Part* makeSubPart(std::string id);
  Part* makeSuperPart(std::string id);
  Part* makeArgPart(std::string id);
  void reset_binds();
  int getStackDepth(int index); //for when removing scope to throw away the items in stack.

  //void setArgPart(std::vector<Part*> args);

  void clear(int input);
  void clearAll();

  int findTempReg();
  int findPersistReg();
  void save(std::ostream& o, int input);
  int load(std::ostream& o, int input);

};

#endif
