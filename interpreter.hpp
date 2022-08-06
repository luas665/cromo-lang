#pragma once
#include "lexer.hpp"
#include "parser.hpp"
#include "var.hpp"


class Interpreter
{
private:
    AST astTree;
    Escope esc;
public:
    Interpreter(AST a):astTree(a){}
    void run();
    Var visit(Node n);
    Var visitBinOp(Bop b);
    Var visitNum(Number n);
};