#include "token.hpp"

Token::Token(TokenType type, std::string txt):tpe(type),text(txt){}

std::string Token::to_string()
{
    std::string type = "";
    switch (tpe)
    {
    case Num:
        type = "Num";
        break;
    case Plus:
        type = "Plus";
        break;
    case Minus:
        type = "Minus";
        break;
    case Times:
        type = "Times";
        break;
    case Division:
        type = "Division";
        break;
    case Identifier:
        type = "Identifier";
        break;
    case LParen:
        type = "LParen";
        break;
    case RParen:
        type = "RParen";
        break;
    case True:
        type = "True";
        break;
    case False:
        type = "False";
        break;
    case Error:
        type = "Error";
        break;
    case EoF:
        type = "EoF";
        break;
    default:
        break;
    }

    return "Token( type = " + type + ", text = \"" + text + "\")";
}
