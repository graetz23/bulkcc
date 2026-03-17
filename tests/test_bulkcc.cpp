#define CATCH_CONFIG_MAIN
#include <catch_amalgamated.hpp>
#include "../source/bulkcc/bulkccController.h"
#include "DummyA.h"
#include "DummyB.h"
#include "DummyC.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

TEST_CASE("Controller instantiation", "[controller]") {
    BULKCC::Controller controller;
    REQUIRE(true);
}

TEST_CASE("Controller destruction", "[controller]") {
    BULKCC::Controller* controller = new BULKCC::Controller();
    delete controller;
    REQUIRE(true);
}

TEST_CASE("Add single DummyA object", "[add]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "testA");
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    REQUIRE(obj != 0);
    REQUIRE(obj->checkObj() == true);
    controller.erase(obj);
}

TEST_CASE("Add single DummyB object", "[add]") {
    BULKCC::Controller controller;
    DummyB* objB = new DummyB(2, "testB");
    BULKCC::Obj* obj = controller.add<DummyB*>(objB);
    REQUIRE(obj != 0);
    REQUIRE(obj->checkObj() == true);
    controller.erase(obj);
}

TEST_CASE("Add single DummyC object", "[add]") {
    BULKCC::Controller controller;
    DummyC* objC = new DummyC(3, "testC");
    BULKCC::Obj* obj = controller.add<DummyC*>(objC);
    REQUIRE(obj != 0);
    REQUIRE(obj->checkObj() == true);
    controller.erase(obj);
}

TEST_CASE("Add mixed objects (all 3 types)", "[add]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "A");
    DummyB* objB = new DummyB(2, "B");
    DummyC* objC = new DummyC(3, "C");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    controller.add<DummyB*>(objB, obj);
    controller.add<DummyC*>(objC, obj);
    
    REQUIRE(obj != 0);
    controller.erase(obj);
}

TEST_CASE("Search DummyA by type", "[search]") {
    BULKCC::Controller controller;
    DummyA* objA1 = new DummyA(1, "A1");
    DummyA* objA2 = new DummyA(2, "A2");
    DummyB* objB = new DummyB(1, "B");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA1);
    controller.add<DummyA*>(objA2, obj);
    controller.add<DummyB*>(objB, obj);
    
    int found = controller.search<DummyA*>(obj);
    REQUIRE(found == 2);
    
    controller.erase(obj);
}

TEST_CASE("Search DummyB by type", "[search]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "A");
    DummyB* objB1 = new DummyB(1, "B1");
    DummyB* objB2 = new DummyB(2, "B2");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    controller.add<DummyB*>(objB1, obj);
    controller.add<DummyB*>(objB2, obj);
    
    int found = controller.search<DummyB*>(obj);
    REQUIRE(found == 2);
    
    controller.erase(obj);
}

TEST_CASE("Search DummyC by type", "[search]") {
    BULKCC::Controller controller;
    DummyC* objC1 = new DummyC(1, "C1");
    DummyC* objC2 = new DummyC(2, "C2");
    DummyC* objC3 = new DummyC(3, "C3");
    
    BULKCC::Obj* obj = controller.add<DummyC*>(objC1);
    controller.add<DummyC*>(objC2, obj);
    controller.add<DummyC*>(objC3, obj);
    
    int found = controller.search<DummyC*>(obj);
    REQUIRE(found == 3);
    
    controller.erase(obj);
}

TEST_CASE("Fetch first matching object", "[fetch]") {
    BULKCC::Controller controller;
    DummyA* objA1 = new DummyA(1, "A1");
    DummyA* objA2 = new DummyA(2, "A2");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA1);
    controller.add<DummyA*>(objA2, obj);
    
    DummyA* fetched = controller.fetch<DummyA*>(obj);
    REQUIRE(fetched != 0);
    REQUIRE(fetched->getId() == 2);
    
    delete fetched;
    controller.erase(obj);
}

TEST_CASE("List all objects of specific type", "[list]") {
    BULKCC::Controller controller;
    DummyA* objA1 = new DummyA(1, "A1");
    DummyA* objA2 = new DummyA(2, "A2");
    DummyB* objB = new DummyB(1, "B");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA1);
    controller.add<DummyB*>(objB, obj);
    controller.add<DummyA*>(objA2, obj);
    
    int count = controller.search<DummyA*>(obj);
    REQUIRE(count == 2);
    
    DummyA** list = controller.list<DummyA*>(obj);
    REQUIRE(list != 0);
    REQUIRE(list[0]->getId() == 2);
    REQUIRE(list[1]->getId() == 1);
    
    delete[] list;
    controller.erase(obj);
}

TEST_CASE("Clean stored objects", "[clean]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "A");
    DummyB* objB = new DummyB(2, "B");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    controller.add<DummyB*>(objB, obj);
    
    controller.clean(obj);
    REQUIRE(obj->getNextObj() != 0);
    
    controller.erase(obj);
}

TEST_CASE("Erase entire stack", "[erase]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "A");
    DummyB* objB = new DummyB(2, "B");
    DummyC* objC = new DummyC(3, "C");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    controller.add<DummyB*>(objB, obj);
    controller.add<DummyC*>(objC, obj);
    
    controller.erase(obj);
}

TEST_CASE("Linked list traversal", "[traverse]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "A");
    DummyB* objB = new DummyB(2, "B");
    DummyC* objC = new DummyC(3, "C");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    controller.add<DummyB*>(objB, obj);
    controller.add<DummyC*>(objC, obj);
    
    int count = 0;
    BULKCC::Obj* current = obj;
    while (current != 0) {
        count++;
        current = current->getNextObj();
    }
    REQUIRE(count == 3);
    
    controller.erase(obj);
}

TEST_CASE("Empty/null edge cases", "[edge]") {
    BULKCC::Controller controller;
    BULKCC::Obj* obj = 0;
    
    int found = controller.search<DummyA*>(obj);
    REQUIRE(found == 0);
    
    DummyA* fetched = controller.fetch<DummyA*>(obj);
    REQUIRE(fetched == 0);
}

TEST_CASE("Identify type correctly", "[identify]") {
    BULKCC::Controller controller;
    DummyA* objA = new DummyA(1, "A");
    DummyB* objB = new DummyB(2, "B");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA);
    controller.add<DummyB*>(objB, obj);
    
    bool isB = controller.identify<DummyB*>(obj);
    bool isA = controller.identify<DummyA*>(obj);
    
    REQUIRE(isB == true);
    REQUIRE(isA == false);
    
    controller.erase(obj);
}

TEST_CASE("Fetch removes from stack", "[fetch]") {
    BULKCC::Controller controller;
    DummyA* objA1 = new DummyA(1, "A1");
    DummyA* objA2 = new DummyA(2, "A2");
    
    BULKCC::Obj* obj = controller.add<DummyA*>(objA1);
    controller.add<DummyA*>(objA2, obj);
    
    int before = controller.search<DummyA*>(obj);
    REQUIRE(before == 2);
    
    DummyA* fetched = controller.fetch<DummyA*>(obj);
    delete fetched;
    
    int after = controller.search<DummyA*>(obj);
    REQUIRE(after == 1);
    
    controller.erase(obj);
}

static std::vector<int> generateRandomSequence(int count) {
    std::vector<int> seq;
    for (int i = 0; i < count; i++) {
        seq.push_back(rand() % 3);
    }
    return seq;
}

TEST_CASE("Performance: push 10K random objects", "[.][perf]") {
    srand(42);
    std::vector<int> seq = generateRandomSequence(10000);
    
    BULKCC::Controller controller;
    BULKCC::Obj* obj = 0;
    
    BENCHMARK("push 10K random objects") {
        controller.erase(obj);
        obj = 0;
        
        for (int i = 0; i < 10000; i++) {
            int type = seq[i];
            if (type == 0) {
                DummyA* a = new DummyA(i, "A");
                if (obj == 0) obj = controller.add<DummyA*>(a);
                else controller.add<DummyA*>(a, obj);
            } else if (type == 1) {
                DummyB* b = new DummyB(i, "B");
                if (obj == 0) obj = controller.add<DummyB*>(b);
                else controller.add<DummyB*>(b, obj);
            } else {
                DummyC* c = new DummyC(i, "C");
                if (obj == 0) obj = controller.add<DummyC*>(c);
                else controller.add<DummyC*>(c, obj);
            }
        }
        return obj;
    };
    
    controller.erase(obj);
}

TEST_CASE("Performance: search by type (10K random)", "[.][perf]") {
    srand(42);
    std::vector<int> seq = generateRandomSequence(10000);
    
    BULKCC::Controller controller;
    BULKCC::Obj* obj = 0;
    
    for (int i = 0; i < 10000; i++) {
        int type = seq[i];
        if (type == 0) {
            DummyA* a = new DummyA(i, "A");
            if (obj == 0) obj = controller.add<DummyA*>(a);
            else controller.add<DummyA*>(a, obj);
        } else if (type == 1) {
            DummyB* b = new DummyB(i, "B");
            if (obj == 0) obj = controller.add<DummyB*>(b);
            else controller.add<DummyB*>(b, obj);
        } else {
            DummyC* c = new DummyC(i, "C");
            if (obj == 0) obj = controller.add<DummyC*>(c);
            else controller.add<DummyC*>(c, obj);
        }
    }
    
    int result = 0;
    BENCHMARK("search DummyA in 10K random") {
        result = controller.search<DummyA*>(obj);
    };
    
    controller.erase(obj);
    REQUIRE(result > 0);
}

TEST_CASE("Performance: fetch from 10K stack", "[.][perf]") {
    srand(42);
    std::vector<int> seq = generateRandomSequence(10000);
    
    BULKCC::Controller controller;
    BULKCC::Obj* obj = 0;
    
    for (int i = 0; i < 10000; i++) {
        int type = seq[i];
        if (type == 0) {
            DummyA* a = new DummyA(i, "A");
            if (obj == 0) obj = controller.add<DummyA*>(a);
            else controller.add<DummyA*>(a, obj);
        } else if (type == 1) {
            DummyB* b = new DummyB(i, "B");
            if (obj == 0) obj = controller.add<DummyB*>(b);
            else controller.add<DummyB*>(b, obj);
        } else {
            DummyC* c = new DummyC(i, "C");
            if (obj == 0) obj = controller.add<DummyC*>(c);
            else controller.add<DummyC*>(c, obj);
        }
    }
    
    DummyA* fetched = 0;
    BENCHMARK("fetch DummyA from 10K random") {
        fetched = controller.fetch<DummyA*>(obj);
    };
    
    if (fetched) delete fetched;
    controller.erase(obj);
}

TEST_CASE("Performance: list all of one type (10K)", "[.][perf]") {
    srand(42);
    std::vector<int> seq = generateRandomSequence(10000);
    
    BULKCC::Controller controller;
    BULKCC::Obj* obj = 0;
    
    for (int i = 0; i < 10000; i++) {
        int type = seq[i];
        if (type == 0) {
            DummyA* a = new DummyA(i, "A");
            if (obj == 0) obj = controller.add<DummyA*>(a);
            else controller.add<DummyA*>(a, obj);
        } else if (type == 1) {
            DummyB* b = new DummyB(i, "B");
            if (obj == 0) obj = controller.add<DummyB*>(b);
            else controller.add<DummyB*>(b, obj);
        } else {
            DummyC* c = new DummyC(i, "C");
            if (obj == 0) obj = controller.add<DummyC*>(c);
            else controller.add<DummyC*>(c, obj);
        }
    }
    
    DummyA** list = 0;
    BENCHMARK("list all DummyA from 10K random") {
        list = controller.list<DummyA*>(obj);
    };
    
    if (list) delete[] list;
    controller.erase(obj);
}
