#include "test_types.h"
#include <cstring>
#include <cstdio>

TestTypeA* createTypeA(int id) {
    TestTypeA* obj = new TestTypeA();
    obj->id = id;
    return obj;
}

TestTypeB* createTypeB(double value) {
    TestTypeB* obj = new TestTypeB();
    obj->value = value;
    return obj;
}

TestTypeC* createTypeC(const char* data) {
    TestTypeC* obj = new TestTypeC();
    if (data) {
        strncpy(obj->data, data, 31);
        obj->data[31] = '\0';
    } else {
        obj->data[0] = '\0';
    }
    return obj;
}

void deleteTypeA(TestTypeA* obj) {
    delete obj;
}

void deleteTypeB(TestTypeB* obj) {
    delete obj;
}

void deleteTypeC(TestTypeC* obj) {
    delete obj;
}
