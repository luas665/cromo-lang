#pragma once 
#include <map>
#include <iostream>
#include <cmath>

enum varType
{
    number,
    string,
    boolean,
    none,

};

class Var
{
private:
    varType tpe;
    void* var;
public:
    Var();
    Var(double d);
    Var(varType type, void* variable):tpe(type),var(variable){}
    Var add(Var v);
    Var min(Var v);
    Var mul(Var v);
    Var div(Var v);
    Var pow(Var v);
    Var root(Var v);
    double get_num();

};

class Escope
{
private:
    std::map<std::string, Var> vars;

public:
    void add(std::string, Var);
    void del(std::string);
    Var get(std::string);
};
