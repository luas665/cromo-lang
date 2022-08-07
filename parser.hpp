#pragma once
#include "token.hpp"
#include <vector>
#include <string>
#include <iostream>

enum BOperator
{
    Add,
    Min,
    Mul,
    Div,
    Pow,
    Root,
    Equal,
};

enum AOperator
{
    AddAssign,
    MinAssign,
    Assign,
};

enum NodeType
{
    ite,
    num,
    id,
    binop,
    assign,
    whileloop,
    err,
};

class Node
{
public:
    Node(NodeType tpe, void* nde):t(tpe),node(nde){}
    NodeType t;
    void* node;
};

class Ite
{
public:
    Ite(Node& condition, Node& ifBranch, Node& elseBranch):condition(condition),ifBranch(ifBranch),elseBranch(elseBranch){}
    Node& condition;
    Node& ifBranch;
    Node& elseBranch;
};


class Number
{
public:
    Number(double number):num(number){}
    double num;
};

class Id
{
public:
    Id(std::string id):id(id){}
    std::string id;
};

class Bop
{
public:
    Bop(BOperator op, Node l, Node r):op(op),left(l),right(r){}
    BOperator op;
    Node left;
    Node right;
    
};

class StatementBlock
{
public:
    std::vector<Node> statments;
};

class Assignment
{
public:
    Assignment(AOperator assignOp, Id lvalue, Node rvalue):assignOp(assignOp),lvalue(lvalue),rvalue(rvalue){}
    AOperator assignOp;
    Id lvalue;
    Node rvalue;
};

class whileLoop
{
public:
    whileLoop(Node condition, StatementBlock Block):condition(condition),Block(Block){}
    Node condition;
    StatementBlock Block;
};

class AST
{
public:
    AST(StatementBlock blck):s(blck){}
    StatementBlock s;
};

class Parser
{
private:
    int pos = -1;
    std::vector<Token> tokens;
    Token lookahead;

public:
    Parser(std::vector<Token> toks);
    Parser(){}
    void eat(TokenType tokTpe);
    void error();
    Token get_nxt_tok();
    Token peek();
    Node factor();
    Node fterm();
    Node term();
    Node expression();
    AST parse();


};

void show_AST(AST a);


// class forLoop
// {
//     Expression condition;
//     Statement Block;
// };


// Node* to_node(NodeType t, void*)
