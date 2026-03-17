#ifndef __DummyA_h__
#define __DummyA_h__

#include "../source/bulkcc/bulkccObj.h"
#include <string>

class DummyA : public BULKCC::Obj {
public:
    DummyA(int id = 0, const std::string& data = "") : _id(id), _data(data), _objIsSet(true) {}
    virtual ~DummyA() {}

    BULKCC::TYPE::ObjType getObjType() { return BULKCC::TYPE::Template; }
    BULKCC::Str getObjTypeAsString() { return "DummyA"; }
    BULKCC::Obj* getAsBaseObj() { return this; }
    bool checkObj() { return _objIsSet; }
    void eraseObj() { _objIsSet = false; }

    int getId() const { return _id; }
    std::string getData() const { return _data; }

private:
    int _id;
    std::string _data;
    bool _objIsSet;
};

#endif
