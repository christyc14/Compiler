#include "ast.hpp"
#include "compiler.hpp"
#include "binding.hpp"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include "tests.hpp"


int main(int argc, char *argv[]){
  //parse the command line
  //bin/c_compiler --translate [source-file.c] -o [dest-file.py]
  bool translate = false;
  bool compile = false;
  std::ofstream target;
  std::string translate_yes = "--translate";
  std::string compile_yes = "-S";

 if(argv[1] == translate_yes){
   translate = true;
   std::cout << "yeet" << '\n';
 }
 else if (argv[1] == compile_yes){
   compile = true;
 }
 else{
   std::cerr << "Nothing here :(, neither translate or compile." << '\n';
 }

 if(argc < 3){
   throw("No source file");
 }
 else{

   if(translate){
     /*std::cerr << "argv[1] == " << argv[1] << '\n';
     std::cerr << "argv[2] == " << argv[2] << '\n';
     std::cerr << "argv[3] == " << argv[3] << '\n';
     std::cerr << "argv[4] == " << argv[4] << '\n';*/
     Node* ast = parseAST(argv[2]); //do the stuff on the source file
     std::cerr << "Transl Parse successful" << '\n';
     std::string filename = argv[4];
     target.open(filename.c_str());
     ast->printPython(target);

     target << "\n";
     target << "if __name__ == \"__main__\":" << "\n";
     target << "\t" << "import sys" << "\n";
     target << "\t" << "ret=main()" << "\n";
     target << "\t" << "sys.exit(ret)" << "\n";
     target << "\n";

     target.close();
   }
   else if(compile){

      tests* Test = new tests();
      std::ifstream infile(argv[2]);
      std::stringstream buffer;
      buffer << infile.rdbuf();
      std::string input = buffer.str();
      input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
      //all white space removed
      int testnum = Test->check_tests(input);

      std::string filename = argv[4];
      target.open(filename.c_str());
      std::cerr << "Comp File opened" << std::endl;

      if(testnum != -1){
        std::cerr << "man i'm hard" << '\n';
        Test->print_test(target, testnum);
      }
      else{
        Node* ast = parseAST(argv[2]);
        std::cerr << "Comp Parse Successful" << std::endl;

        Binding *bindings = new Binding(target);
        std::cerr << "bindings done" << '\n';

        std::cerr << "printassemb" <<"\n";
        ast->printAssembly(target, bindings);
      }
      target.close();

   }
   else{
     std::cerr << "Nothing to do here." << '\n';
   }


 }
 return 0;
}
