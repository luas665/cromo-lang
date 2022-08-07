#include "var.hpp"


Var::Var()
{
    this->tpe = none;
}

Var::Var(double d)
{
    this->tpe = number;
    this->var = new double(d);
}
Var Var::add(Var v)
{
    if(tpe == number && v.tpe == number)
    {
        double r = *((double *)var);
        double l = *((double *)(v.var));
        return Var(r+l);
    }

    return Var();
}
Var Var::min(Var v)
{
    if(tpe == number && v.tpe == number)
    {
        double r = *((double *)var);
        double l = *((double *)(v.var));
        std::cout << r << " " << l << std::endl;
        return Var(r-l);
    }

    return Var();
}
Var Var::mul(Var v)
{
    if(tpe == number && v.tpe == number)
    {
        double r = *((double *)var);
        double l = *((double *)(v.var));
        return Var(r*l);
    }

    return Var();
}
Var Var::div(Var v)
{
    if(tpe == number && v.tpe == number)
    {
        double r = *((double *)var);
        double l = *((double *)(v.var));
        return Var(r/l);
    }

    return Var();
}

Var Var::pow(Var v)
{
    double r = get_num();
    double l = v.get_num();
    double result = std::pow(r, l);
    return result;
}

Var Var::root(Var v)
{
    double r = get_num();
    double l = v.get_num();
    double result = std::pow(r, 1.0/l);
    return result;
}

double Var::get_num()
{
    double n = *((double *)var);
    return n;
}


void Escope::add(std::string s, Var r)
{
    vars.insert(std::pair<std::string, Var>(s, r));
}
void Escope::del(std::string s)
{
    std::map<std::string, Var>::iterator it;
    it = vars.find(s);
    if (it != vars.end())
    {
        vars.erase (it);
    }
}
Var Escope::get(std::string s)
{
    std::map<std::string, Var>::iterator it;
    it = vars.find(s);
    if (it != vars.end())
    {
        return it->second;
    } 

    std::cerr << "Error: NameError coud not find var \"" << s << "\"" << std::endl;

    return  Var();
}

