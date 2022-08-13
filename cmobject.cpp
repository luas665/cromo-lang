#include "cmobject.hpp"

double toNumber(CmObject *object)
{
    if (object->getType() == "int")
    {
        return *(int*)object->getData().data;
    } else if (object->getType() == "float")
    {
        return *(double*)object->getData().data;
    } else if (object->getType() == "bool")
    {
        return *(bool*)object->getData().data;
    }
}

CmObject* defaultFunc(CmObject* self, CmObject* args)
{
    return new CmObject();
}

CmObject* notEqual(CmObject* self, CmObject* args)
{
    CmObject* equal = self->getAttr("equal")->call(args);
    bool result = *(bool*)equal->getData().data;
    return new CmObject(!result);
}

CmObject* lessThan(CmObject* self, CmObject* args)
{
    bool equal = *(bool*)(self->getAttr("equal")->call(args)->getData().data);
    bool greaterThan = *(bool*)(self->getAttr("greaterThan")->call(args)->getData().data);

    return new CmObject(!(greaterThan || equal));
}

CmObject* greaterThanOrEqual(CmObject* self, CmObject* args)
{
    bool equal = *(bool*)(self->getAttr("equal")->call(args)->getData().data);
    bool greaterThan = *(bool*)(self->getAttr("greaterThan")->call(args)->getData().data);
    return new CmObject(equal || greaterThan);
}

CmObject* lessThanOrEqual(CmObject* self, CmObject* args)
{
    bool equal = *(bool*)(self->getAttr("equal")->call(args)->getData().data);
    bool lessThan = *(bool*)(self->getAttr("lessThan")->call(args)->getData().data);
    return new CmObject(equal || lessThan);
}


CmObject::CmObject() : data(Data()), type("null")
{
    this->setAttr("add", new CmObject(defaultFunc));
    this->setAttr("min", new CmObject(defaultFunc));
    this->setAttr("mul", new CmObject(defaultFunc));
    this->setAttr("div", new CmObject(defaultFunc));
    this->setAttr("pot", new CmObject(defaultFunc));
    this->setAttr("root", new CmObject(defaultFunc));
    this->setAttr("equal", new CmObject(defaultFunc));
    this->setAttr("greaterThan", new CmObject(defaultFunc));
    this->setAttr("lessThan", new CmObject(defaultFunc));
    this->setAttr("greaterThanOrEqual", new CmObject(greaterThanOrEqual));
    this->setAttr("lessThanOrEqual", new CmObject(lessThanOrEqual));
    this->setAttr("notEqual", new CmObject(notEqual));

}

CmObject* intAdd(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    int r = toNumber(args->getAttr("0"));
    return new CmObject(l+r);
}

CmObject* intMin(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    int r = toNumber(args->getAttr("0"));
    return new CmObject(l-r);
}

CmObject* intMul(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    int r = toNumber(args->getAttr("0"));
    return new CmObject(l*r);
}

CmObject* intDiv(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    int r = toNumber(args->getAttr("0"));
    return new CmObject(l/r);
}

CmObject* intPot(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    int r = toNumber(args->getAttr("0"));
    return new CmObject(std::pow(l, r));
}

CmObject* intRoot(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    int r = toNumber(args->getAttr("0"));
    return new CmObject(std::pow(l, 1.0/r));
}


CmObject* intEqual(CmObject* self, CmObject* args)
{
    int l = toNumber(self);
    CmObject* r = args->getAttr("0");
    if (r->getType() == "int")
    {
        return new CmObject(l == toNumber(r));
    }
    return new CmObject(false);
}

CmObject::CmObject(int num) : data(Data(new int(num))), type("int") 
{
    this->setAttr("add", new CmObject(intAdd));
    this->setAttr("min", new CmObject(intMin));
    this->setAttr("mul", new CmObject(intMul));
    this->setAttr("div", new CmObject(intDiv));
    this->setAttr("pot", new CmObject(intPot));
    this->setAttr("root", new CmObject(intRoot));
    this->setAttr("equal", new CmObject(defaultFunc));
    this->setAttr("greaterThan", new CmObject(defaultFunc));
    this->setAttr("lessThan", new CmObject(defaultFunc));
    this->setAttr("greaterThanOrEqual", new CmObject(greaterThanOrEqual));
    this->setAttr("lessThanOrEqual", new CmObject(lessThanOrEqual));
    this->setAttr("notEqual", new CmObject(notEqual));
}
CmObject::CmObject(double num) : data(Data(new double(num))), type("float") {}
CmObject::CmObject(bool value) : data(Data(new bool(value))), type("bool") {}
CmObject::CmObject(std::string value) : data(Data(new std::string(value))), type("string") {}
CmObject::CmObject(cfunction* cfunc) : data(Data(cfunc)), type("function") {}
