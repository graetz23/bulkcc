#ifndef __DummyB_h__
#define __DummyB_h__

#include "../source/bulkcc/bulkccObj.h"
#include <string>

class DummyB : public BULKCC::Obj {
public:
    DummyB(int id = 0, const std::string& data = "") : _id(id), _data(data), _objIsSet(true) {}
    virtual ~DummyB() {}

    BULKCC::TYPE::ObjType getObjType() { return BULKCC::TYPE::Template; }
    BULKCC::Str getObjTypeAsString() { return "DummyB"; }
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
