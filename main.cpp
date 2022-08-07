#include "interpreter.hpp"
#include <iostream>

using namespace std;

int idle()
{
    std::string txt;
    while (true)
    {
        cout << ">> ";
        getline(cin, txt);
        if (txt != ""){
            vector<Token> toks = Lexer(txt).lex();
            AST a = Parser(toks).parse();
            Interpreter(a).run();
        }
    }

    return 0;
    
}

int main(int argc, char const *argv[])
{
    return idle();	
}
