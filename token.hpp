#pragma once
#include <string>

enum TokenType{
    Num,
    Assgn,

    Eq,
    Plus,
    Minus,
    Times,
    Division,

    Identifier,
    LParen,
    RParen,
    LBrace,
    RBrace,

    True,
    False,
    Error,
    EoF,
};

class Token
{
public:
    TokenType tpe;
    std::string text;
    int startPos;
    Token(TokenType type, std::string txt);
    Token(){}
    std::string to_string();
};






