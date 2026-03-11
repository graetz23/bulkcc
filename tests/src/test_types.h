#ifndef test_types_h
#define test_types_h

struct TestTypeA {
    int id;
};

struct TestTypeB {
    double value;
};

struct TestTypeC {
    char data[32];
};

TestTypeA* createTypeA(int id);
TestTypeB* createTypeB(double value);
TestTypeC* createTypeC(const char* data);

void deleteTypeA(TestTypeA* obj);
void deleteTypeB(TestTypeB* obj);
void deleteTypeC(TestTypeC* obj);

#endif
