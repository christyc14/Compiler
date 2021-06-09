#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include "ast_node.hpp"


class Integer : public Node {

private:

  int value;
  int bytesize = 4;
  std::string type = "Integer";

protected:


public:

  Integer(int input);

  int& access();
  int get_size();
  std::string getType();
  void printPython(std::ostream &o);
  void printAssembly(std::ostream&o, Binding *binds);
  void printAssembly(Part* sub, std::ostream &o, Binding *binds);
  void storevector(std::vector<std::string>& v);
};

class Floating : public Node {

private:

  double value;
  int bytesize = 4;

protected:

public:
  Floating(double in): value(in){};
  double& access();
  void printPython(std::ostream &o);
  void storevector(std::vector<std::string>& v);
//  Binding printAssembly(std::ostream &o, Binding binds){};

};
class Character : public Node {

private:

  char value;
  int bytesize = 1;

protected:

public:


  //char& access();
  void printPython(std::ostream &o);
  void storevector(std::vector<std::string>& v);
//  Binding printAssembly(std::ostream &o, Binding binds){};

};

class String : public Node {

private:

  std::string value;

protected:

public:

  String(std::string *input){delete input;};
//  std::string& access();
  void printPython(std::ostream &o){ o << value;};
  void storevector(std::vector<std::string>& v);
//  Binding printAssembly(std::ostream &o, Binding binds){};
  // void printAssembly(std::ostream &o);
};

#endif
