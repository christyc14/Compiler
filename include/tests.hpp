#ifndef TESTS_HPP
#define TESTS_HPP
#include<ostream>
#include<vector>
#include"ast.hpp"

class tests{
public:
  tests();
  int check_tests(std::string input);
  friend bool operator ==(std::vector<std::string> a, std::vector<std::string>b);
  void print_test(std::ostream& o, int input);
private:
  std::vector<std::string> big_vec_tests;
  std::vector<std::vector<std::string> >big_vec_mips;
};
#endif
