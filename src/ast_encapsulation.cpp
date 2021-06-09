#include "ast/ast_encapsulation.hpp"
#include "ast/ast_variable.hpp"


void Encapsulate::printPython(std::ostream &o) {
 increase_scope();
//  indent(o);
  //This printPython will print the part of python that is responsible for scope. i.e. It will indent once to the right (tab), newline. and then
  //it will call printpython on statementlist. Then it will new line and de-indent once to the right (tab).
  if(declarlist){
    declarlist->printPython(o);
    o << "\n";
  }
  if(statementList){
    statementList->printPython(o);
  }
  decrease_scope();
}

Encapsulate::Encapsulate(NodePtr lone, NodePtr ltwo): declarlist(lone), statementList(ltwo){};

void Encapsulate::printAssembly(std::ostream &o, Binding *binds){

std::cerr << "\t\t Encapsulate printAssembly" << std::endl;
    bool f_scope = function_scope;
    function_scope = false;
//  o<< "encapsulate\n";


  int current_scope = binds->getScope();
  binds->increaseScope();


  if(declarlist){
    declarlist->allocateVars(o,binds);
    std::cerr << "encapsulate print asem" << '\n';
    //o << "\n";
  }
  if(statementList){
    statementList->printAssembly(o,binds);
    std::cerr << "encapsulate statementlist print asem" << '\n';
  }


  if (f_scope){
    std::cerr << "f_scope set true" << std::endl;
    o << "\n";
    o << return_label << ":";

    while(binds->getScope() != current_scope){
      binds->decreaseScope();
      std::cerr << "Decreasig scope in loop" << std::endl;
    }
  }
  else
  {
      std::cerr << "Decreasing scope once" << std::endl;
      binds->decreaseScope();
  }

}

/*void Encapsulate::count_variables(int32_t&var){
  std::cerr << "encapsulate count variables" << '\n';
  statementList->count_variables(var);
}*/

void Encapsulate::storevector(std::vector<std::string>& v){
//  v.push_back("(");
  if(declarlist){
    declarlist->storevector(v);
  }
//  v.push_back(")");
  //v.push_back("{");
  if(statementList){
    statementList->storevector(v);
  }
//  v.push_back("}");
}
//////////////////////////////////////////////////////////////////////// YEEEEEEEET

StatementList::StatementList(){std::cerr << "made statementlist" << '\n';}

void StatementList::printPython(std::ostream &o){

  //please implement this. aka print in order. remember to indent and shit.
 //Printpython here will iterate through the list of nodepointers which will be "statements" as we defined the token in parser.y
 std::cerr << "StatementList printing python" << std::endl;

 for (int i = 0; i < list.size(); i++){
/*
   indent(o);
   list[i]->printPython(o);
   o << "\n";
*/
   if(list[i]){
     if (type == "INIT"){
       std::cerr << "if type = init" << '\n';
      //  indent(o);
         list[i]->printPython(o);
       if(list.size() != 0 && i < list.size()){
         o << "\n";
      //   break;
       }
     }
     else if(type == "ARG_EXP") {
       std::cerr << "Yee HAw" << std::endl;
      /* indent(o);*/
       list[i]->printPython(o);
       if(list.size() != 0 && i < list.size()-1){
         o << ", ";
        // break;
       }
     }
     else if(type == "PAR"){
       std::cerr << "entered PAR" << '\n';
       list[i]->printPython(o);
       if(list.size() != 0 && i < list.size()-1){
         o << ", ";
        // break;
       }
     }
     else{
       indent(o);
       list[i]->printPython(o);
       if(list.size() != 0 && i < list.size()){
         o << "\n";
      //  break;
       }
     }
   }
 }
}


void StatementList::settype(std::string t){
  type = t;
}

void StatementList::insert(NodePtr node_in) { list.push_back(node_in); }

void StatementList::getglobal(std::vector<std::string> &vec){
  for(int i = 0; i < list.size(); i++){
    if(list[i]){
      list[i]->getglobal(vec);
    }
  }
}

void StatementList::printAssembly(std::ostream &o, Binding *binds){
/* o << "statementlist here"; */
std::cerr << "statementlist print assembly" << '\n';
  for(int i = 0; i < list.size(); i++){
    if(list[i])
    {
    list[i]->printAssembly(o,binds);
    }
  //  std::cerr << "loop?" << '\n';
    o<<"\n";
  }

}

void StatementList::storevector(std::vector<std::string>& v){
  for (int i = 0; i < list.size(); i++) {
    if(list[i]){
      list[i]->storevector(v);
    }
  }
}
/*
void StatementList::variableregisters(std::ostream& o, Binding binds){
  for(int i = 0; i < list.size(); i++){
    if(list[i]!=NULL){
      if(type == "INIT"){
        list[i]->singlereg(o,binds);
      }
      else if(type == "declare"){
        list[i]->variableregisters(o,binds);
      }
      else if(type == "PAR"){
        list[i]->singlereg(o,binds);
      }
    }
  }
}*/

void StatementList::transferArgs(std::vector<Part*> &v, Binding *binds){

  if(type == "ARG_EXP"){
    for(int i = 0; i < list.size(); i++){
      Part* arg = binds->makeSubPart(makeLabel(std::string("_ARGOS_")));

      list[i]->printAssembly(arg);

      v.push_back(arg);
    }
  }
}


void StatementList::allocateVars(std::ostream &o, Binding *binds){

  std::cerr << "\t\t StatementList AllocateVars" << std::endl;

  for (auto &x : list){

    if (x)
    {
      if (type == "INIT")
      {
        std::cerr << "Allocating Variable for INIT" << std::endl;
        x->allocateVar(o, binds);
      }
      else if (type == "DEC")
      {
        std::cerr << "Allocating Variables for DEC" << std::endl;
        x->allocateVars(o, binds);
      }
      else if (type == "PAR")
      {
        std::cerr << "Allocating Variable for PAR" << std::endl;
        x->allocateVar(o, binds);
      }
    }

  }
}


///////////////////////////////////////////////////////////////////////
IdList::IdList(){};
void IdList::insert(std::string *in){
  ids.push_back(*in);
  delete in;
}
void IdList::printPython(std::ostream& o){
  for(int i = 0; i < ids.size(); i++){
    o << ids[i] << std::endl;
  }
}

void IdList::storevector(std::vector<std::string>& v){
  for (int i = 0; i < ids.size(); i++) {
    v.push_back(ids[i]);
  }
}
///////////////////////////////////////////////////////////////////////

ExpressionList::ExpressionList(){

}

void ExpressionList::printPython(std::ostream &o){

  for (int i = 0; i < list.size(); i++){

    std::cerr << "Printing the Expression List" << std::endl;
    list[i]->printPython(o);
  //  o << " ";
  }

}

void ExpressionList::insert(NodePtr node_in){

  list.push_back(node_in);
}

void ExpressionList::storevector(std::vector<std::string>& v){
  for (int i = 0; i < list.size(); i++) {
    list[i]->storevector(v);
  }
}
