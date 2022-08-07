#include "interpreter.hpp"

void Interpreter::run()
{
    for (Node node : astTree.s.statments)
    {
        std::cout << visit(node).get_num() << std::endl;
    }
}
Var Interpreter::visit(Node n)
{
    if(n.t == binop)
    {
        Bop b = *((Bop*)(n.node));
        return visitBinOp(b);
    } else if(n.t == num)
    {
        Number num = *((Number*)(n.node));
        return visitNum(num);
    }
    
    return Var();
}
Var Interpreter::visitBinOp(Bop b)
{
    Var r = visit(b.right);
    Var l = visit(b.left);
    Var result;
    switch (b.op)
    {
    case Add:
        result = l.add(r);
        break;
    case Min:
        result = l.min(r);
        break;
    case Mul:
        result = l.mul(r);
        break;
    case Div:
        result = l.div(r);
        break;
    case Pow:
        result = l.pow(r);
        break;
    case Root:
        result = l.root(r);
        break;
    default:
        result = Var();
        break;
    }
    return result;
}
Var Interpreter::visitNum(Number n)
{
    return Var(n.num);
}