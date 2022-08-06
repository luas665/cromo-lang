#include "interpreter.hpp"
#include <iostream>

using namespace std;

void interpret(std::string txt)
{
    vector<Token> toks = Lexer(txt).lex();
    AST a = Parser(toks).parse();
    Interpreter(a).run();
}

int main(int argc, char const *argv[])
{
    std::string txt;
    while (true)
    {
        cout << ">> ";
        getline(cin, txt);
        if (txt != ""){
            interpret(txt);
        }
    }
    

    return 0;
}
