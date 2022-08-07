#include "lexer.hpp"

Lexer::Lexer(std::string input):input(input)
{
}
std::vector<Token> Lexer::lex()
{
    std::vector<Token> tokens;
    
    int currentPos = 0;
    while (currentPos < input.length())
    {
        int tokenStartPos = currentPos;
        char lookahead = input[currentPos];
        if (lookahead == ' ')
        {
            currentPos++;
        } else if (lookahead == '+')
        {
            currentPos++;
            tokens.push_back(Token(Plus, std::string(1, lookahead)));
        } else if (lookahead == '-')
        {
            currentPos++;
            tokens.push_back(Token(Minus, std::string(1, lookahead)));
        } else if (lookahead == '*')
        {
            currentPos++;
            TokenType type = Times;
            if (input[currentPos] == '*')
            {
                currentPos++;
                type = Potentiation;
            }
            tokens.push_back(Token(type, std::string(1, lookahead)));
        } else if (lookahead == '/')
        {
            currentPos++;
            TokenType type = Division;
            if (input[currentPos] == '/')
            {
                currentPos++;
                type = Rooting;
            }
            tokens.push_back(Token(type, std::string(1, lookahead)));
        } else if (lookahead == '{')
        {
            currentPos++;
            tokens.push_back(Token(LBrace, std::string(1, lookahead)));
        } else if (lookahead == '}')
        {
            currentPos++;
            tokens.push_back(Token(RBrace, std::string(1, lookahead)));
        } else if (lookahead == '(')
        {
            currentPos++;
            tokens.push_back(Token(LParen, std::string(1, lookahead)));
        } else if (lookahead == ')')
        {
            currentPos++;
            tokens.push_back(Token(RParen, std::string(1, lookahead)));
        } else if (lookahead == '=')
        {
            currentPos++;
            if (input[currentPos] == '=')
            {
                tokens.push_back(Token(Eq, "=="));
                currentPos++;
            } else
            {
            tokens.push_back(Token(Assgn, std::string(1, lookahead)));
            }
        } else if (std::isdigit(lookahead))
        {
            std::string text = "";
            while (std::isdigit(lookahead))
            {
                text += lookahead;
                lookahead = input[++currentPos];

            }
            
            tokens.push_back(Token(Num, text));
        } else if (std::isalpha(lookahead))
        {
            std::string text = "";
            while (currentPos < input.length() && (std::isalnum(lookahead) || lookahead == '_'))
            {
                text += lookahead;
                lookahead = input[++currentPos];
            }

            TokenType tpe;

            if(text == "true")
            {
                tpe = True;
            } else if (text == "false")
            {
                tpe = False;
            } else
            {
                tpe = Identifier;
            }

            tokens.push_back(Token(tpe, text));
        } else
        {
            tokens.push_back(Token(Error, "Error: Unknown character '" + std::string(1, lookahead) + "' at position " + std::to_string(currentPos)));
            currentPos++;
        }
    }

    return tokens;
    
}

void show_toks(std::vector<Token> toks)
{
    for (Token tok : toks)
    {
        std::cout << tok.to_string() << std::endl;
    }
}
