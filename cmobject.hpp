#include <map>
#include <string>
#include <cmath>


class CmObject 
{
private:
    Data data;
    std::map<std::string, CmObject*> attr;
    std::string type;
    CmObject* parent;

public:
    CmObject();
    CmObject(int num);
    CmObject(double num);
    CmObject(bool value);
    CmObject(std::string value);
    CmObject(cfunction cfunc);

    CmObject* getAttr(std::string name);
    void setAttr(std::string name, CmObject* obj);

    Data getData();
    std::string getType();
    CmObject* call(CmObject* args);


};





typedef CmObject* cfunction(CmObject* self, CmObject* args);

class Data
{
public:
    void* data;
    cfunction* cfunc;
    
    Data(void* data, cfunction* cfunc) : data(data), cfunc(cfunc) {}
    Data(void* data) : data(data), cfunc(nullptr) {}
    Data(cfunction* cfunc) : data(nullptr), cfunc(cfunc) {}
    Data() : data(nullptr), cfunc(nullptr) {}

};


