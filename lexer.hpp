#pragma once
#include "token.hpp"
#include <vector>
#include <iostream>

class Lexer
{
private:
    std::string input;
public:
    Lexer(std::string input);
    std::vector<Token> lex();
};

void show_toks(std::vector<Token> toks);