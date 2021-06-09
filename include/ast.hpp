#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_node.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_variable.hpp"
#include "ast/ast_encapsulation.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_bitwise.hpp"
#include "ast/ast_controlflow.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_root.hpp"

extern Node* parseAST(std::string name);

#endif
