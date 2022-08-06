#include "parser.hpp"

Parser::Parser(std::vector<Token> toks)
{
    tokens = toks;
    lookahead = get_nxt_tok();
}
void Parser::error()
{
    std::cerr << "Error: SyntaxError" << std::endl;
    exit(1);
}
Token Parser::peek()
{
    if(pos + 1 < tokens.size())
    {
        return tokens[pos + 1];
    }
    return Token(EoF, "");
}
Token Parser::get_nxt_tok()
{
    if(++pos < tokens.size())
    {
        return tokens[pos];
    }
    return Token(EoF, "");
}
void Parser::eat(TokenType tokTpe)
{
    if (lookahead.tpe == tokTpe)
    {
        lookahead = get_nxt_tok();
    } else
    {
        error();
    }
}
Node Parser::factor()
{
    Token tok = lookahead;
    if(tok.tpe == Num)
    {
        eat(Num);
        Number* number = new Number(std::stod(tok.text));
        Node node(num, number);
        return node;
    } else if (tok.tpe == LParen)
    {
        eat(LParen);
        Node node = expression();
        eat(RParen);
        return node;
    } else
    {
        error();
        std::string* s = new std::string("Error");
        return Node(err, s);
    }
    
}
Node Parser::term()
{
    Node node = factor();
    while (lookahead.tpe == Times || lookahead.tpe == Division)
    {
        Token tok = lookahead;
        BOperator op;
        if(tok.tpe == Times)
        {   
            op = Mul;
            eat(Times);
        } else
        {
            op = Div;
            eat(Division);
        }
        Bop* b = new Bop(op, node, factor());
        node = Node(binop, b);
    }

    return node;
    
}
Node Parser::expression()
{
    Node node = term();
    while (lookahead.tpe == Plus || lookahead.tpe == Minus)
    {
        Token tok = lookahead;
        BOperator op;
        if(tok.tpe == Plus)
        {   
            op = Add;
            eat(Plus);
        } else
        {
            op = Min;
            eat(Minus);
        }
        Bop* b = new Bop(op, node, term());
        node = Node(binop, b);
    }

    return node;
}
AST Parser::parse()
{
    StatementBlock s = StatementBlock();
    if (lookahead.tpe == Num || lookahead.tpe == Minus || lookahead.tpe == Plus)
    {
        s.statments.push_back(expression());
    } else if (lookahead.tpe == Identifier)
    {
        Token id = lookahead;
        if (peek().tpe == Assgn)
        {
            eat(Identifier);
            eat(Assgn);
            Assignment* a = new Assignment(Assign, Id(id.text), expression());
            s.statments.push_back(Node(assign, a));
        } else if (id.text == "while")
        {
            eat(Identifier);
            Node condition = expression();
            eat(LBrace);
            std::vector<Token> whlTok;
            Token ct = get_nxt_tok();
            while (ct.tpe != RBrace)
            {
                whlTok.push_back(ct);
                ct = get_nxt_tok();
            }
            eat(RBrace);

            StatementBlock s = Parser(whlTok).parse().s;
            whileLoop* w = new whileLoop(condition, s);
            s.statments.push_back(Node(whileloop, w));

        } else if (id.text == "if")
        {
            
        } else
        {
            s.statments.push_back(expression());
        }
        
    }

    return AST(s);
    
}

std::string BOperator_to_string(BOperator bop)
{
    std::string op = "NULLL";
    switch (bop)
    {
    case Add:
        op = "+";
        break;
    case Min:
        op = "-";
        break;
    case Mul:
        op = "*";
        break;
    case Div:
        op = "/";
        break;
    case Equal:
        op = "==";
        break;
    }
    return op;
}   

void show_node(Node node)
{
    if (node.t == binop)
    {
        Bop* b = (Bop*)(node.node);
        std::cout << "BinOp( left = ";
        show_node((*b).left);
        BOperator op = (*b).op;
        
        std::cout << ", Operation = " << BOperator_to_string(op) << ", right = ";
        show_node((*b).right);
        std::cout << ")";
    } else if(node.t == num)
    {
        Number* n = (Number*)(node.node);
        std::cout << "Number( " << (*n).num << " )";
    }
}


void show_AST(AST a)
{
    for (Node node : a.s.statments)
    {
        show_node(node);
        std::cout << std::endl;
    }
}
