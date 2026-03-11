#define ACUTEST_LIBRARY
#include "acutest.h"

#include "../source/bulkcc/bulkcc.h"
#include "src/test_types.h"

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define PERFORMANCE_COUNT 100000
#define PERF_RESULTS_FILE "perf_results.txt"

double get_time_seconds() {
    return static_cast<double>(clock()) / CLOCKS_PER_SEC;
}

void save_perf_result(const char* test_name, double time_seconds, int count) {
    FILE* f = fopen(PERF_RESULTS_FILE, "a");
    if (f) {
        fprintf(f, "%s: %.6f seconds (%d items, %.6f us/item)\n", 
                test_name, time_seconds, count, 
                (time_seconds * 1000000.0) / count);
        fclose(f);
    }
}

void compare_with_baseline(const char* test_name, double time_seconds) {
    FILE* f = fopen(PERF_RESULTS_FILE, "r");
    if (!f) {
        printf("    No baseline found - first run\n");
        return;
    }

    char line[256];
    double baseline = -1.0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, test_name) == line) {
            char* colon = strchr(line, ':');
            if (colon) {
                sscanf(colon + 1, "%lf", &baseline);
            }
            break;
        }
    }
    fclose(f);

    if (baseline > 0) {
        double diff = ((time_seconds - baseline) / baseline) * 100.0;
        if (diff > 0) {
            printf("    Baseline: %.6fs (+%.2f%% vs baseline)\n", baseline, diff);
        } else {
            printf("    Baseline: %.6fs (%.2f%% vs baseline)\n", baseline, diff);
        }
    } else {
        printf("    No baseline found for this test\n");
    }
}

void print_perf_result(const char* test_name, double time_seconds, int count) {
    printf("    Time: %.6f seconds\n", time_seconds);
    printf("    Rate: %.2f us/item\n", (time_seconds * 1000000.0) / count);
    save_perf_result(test_name, time_seconds, count);
    compare_with_baseline(test_name, time_seconds);
}

void test_add_single(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    TEST_CHECK(stack != 0);
    int found = controller.search<TestTypeA*>(stack);
    TEST_CHECK(found == 1);
    controller.clean(stack);
    controller.erase(stack);
}

void test_add_multiple_mixed(void) {
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;

    for (int i = 0; i < 10; i++) {
        switch (i % 3) {
            case 0: {
                TestTypeA* a = createTypeA(i);
                if (i == 0) {
                    stack = controller.add<TestTypeA*>(a);
                } else {
                    controller.add<TestTypeA*>(a, stack);
                }
                break;
            }
            case 1: {
                TestTypeB* b = createTypeB(i * 1.5);
                controller.add<TestTypeB*>(b, stack);
                break;
            }
            case 2: {
                TestTypeC* c = createTypeC("test");
                controller.add<TestTypeC*>(c, stack);
                break;
            }
        }
    }

    int foundA = controller.search<TestTypeA*>(stack);
    int foundB = controller.search<TestTypeB*>(stack);
    int foundC = controller.search<TestTypeC*>(stack);

    TEST_CHECK(foundA == 4);
    TEST_CHECK(foundB == 3);
    TEST_CHECK(foundC == 3);

    controller.clean(stack);
    controller.erase(stack);
}

void test_identify_positive(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    bool identified = controller.identify<TestTypeA*>(stack);
    TEST_CHECK(identified == true);
    controller.clean(stack);
    controller.erase(stack);
}

void test_identify_negative(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    bool identified = controller.identify<TestTypeB*>(stack);
    TEST_CHECK(identified == false);
    controller.clean(stack);
    controller.erase(stack);
}

void test_search_found(void) {
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;
    for (int i = 0; i < 5; i++) {
        TestTypeA* a = createTypeA(i);
        TestTypeB* b = createTypeB(i);
        if (i == 0) {
            stack = controller.add<TestTypeA*>(a);
        } else {
            controller.add<TestTypeA*>(a, stack);
        }
        controller.add<TestTypeB*>(b, stack);
    }
    int found = controller.search<TestTypeA*>(stack);
    TEST_CHECK(found == 5);
    controller.clean(stack);
    controller.erase(stack);
}

void test_search_not_found(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    int found = controller.search<TestTypeB*>(stack);
    TEST_CHECK(found == 0);
    controller.clean(stack);
    controller.erase(stack);
}

void test_fetch_single(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(42);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    TestTypeA* fetched = controller.fetch<TestTypeA*>(stack);
    TEST_CHECK(fetched != 0);
    TEST_CHECK(fetched->id == 42);
    deleteTypeA(fetched);
    controller.erase(stack);
}

void test_fetch_all(void) {
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;
    for (int i = 0; i < 5; i++) {
        TestTypeA* a = createTypeA(i);
        TestTypeB* b = createTypeB(i * 1.0);
        if (i == 0) {
            stack = controller.add<TestTypeA*>(a);
        } else {
            controller.add<TestTypeA*>(a, stack);
        }
        controller.add<TestTypeB*>(b, stack);
    }
    for (int i = 0; i < 5; i++) {
        TestTypeA* fetched = controller.fetch<TestTypeA*>(stack);
        TEST_CHECK(fetched != 0);
        deleteTypeA(fetched);
    }
    int found = controller.search<TestTypeA*>(stack);
    TEST_CHECK(found == 0);
    controller.clean(stack);
    controller.erase(stack);
}

void test_fetch_empty(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    TestTypeA* fetched = controller.fetch<TestTypeA*>(stack);
    TEST_CHECK(fetched != 0);
    deleteTypeA(fetched);
    fetched = controller.fetch<TestTypeA*>(stack);
    TEST_CHECK(fetched == 0);
    controller.erase(stack);
}

void test_list_conversion(void) {
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;
    for (int i = 0; i < 5; i++) {
        TestTypeA* a = createTypeA(i);
        TestTypeB* b = createTypeB(i);
        if (i == 0) {
            stack = controller.add<TestTypeA*>(a);
        } else {
            controller.add<TestTypeA*>(a, stack);
        }
        controller.add<TestTypeB*>(b, stack);
    }
    int count = controller.search<TestTypeA*>(stack);
    TEST_CHECK(count == 5);
    TestTypeA** list = controller.list<TestTypeA*>(stack);
    TEST_CHECK(list != 0);
    for (int i = 0; i < count; i++) {
        deleteTypeA(list[i]);
    }
    delete[] list;
    controller.clean(stack);
    controller.erase(stack);
}

void test_erase_stack(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    controller.erase(stack);
}

void test_clean_objects(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    controller.clean(stack);
    int found = controller.search<TestTypeA*>(stack);
    TEST_CHECK(found == 0);
    controller.erase(stack);
}

void test_empty_stack(void) {
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;
    int found = controller.search<TestTypeA*>(stack);
    TEST_CHECK(found == 0);
    TestTypeA* fetched = controller.fetch<TestTypeA*>(stack);
    TEST_CHECK(fetched == 0);
}

void test_single_element(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(99);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    int found = controller.search<TestTypeA*>(stack);
    TEST_CHECK(found == 1);
    TestTypeA* fetched = controller.fetch<TestTypeA*>(stack);
    TEST_CHECK(fetched->id == 99);
    deleteTypeA(fetched);
    controller.erase(stack);
}

void perf_push_100k(void) {
    printf("    Pushing %d objects with random type order...\n", PERFORMANCE_COUNT);
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;

    double start = get_time_seconds();
    for (int i = 0; i < PERFORMANCE_COUNT; i++) {
        switch (i % 3) {
            case 0: {
                TestTypeA* a = createTypeA(i);
                if (i == 0) {
                    stack = controller.add<TestTypeA*>(a);
                } else {
                    controller.add<TestTypeA*>(a, stack);
                }
                break;
            }
            case 1: {
                TestTypeB* b = createTypeB(i * 1.0);
                controller.add<TestTypeB*>(b, stack);
                break;
            }
            case 2: {
                TestTypeC* c = createTypeC("perf");
                controller.add<TestTypeC*>(c, stack);
                break;
            }
        }
    }
    double elapsed = get_time_seconds() - start;

    print_perf_result("perf_push_100k", elapsed, PERFORMANCE_COUNT);

    controller.clean(stack);
    controller.erase(stack);
}

void perf_fetch_100k(void) {
    const int FETCH_COUNT = 1000;
    printf("    Creating and fetching %d objects...\n", FETCH_COUNT);
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;

    for (int i = 0; i < FETCH_COUNT; i++) {
        switch (i % 3) {
            case 0: {
                TestTypeA* a = createTypeA(i);
                if (i == 0) {
                    stack = controller.add<TestTypeA*>(a);
                } else {
                    controller.add<TestTypeA*>(a, stack);
                }
                break;
            }
            case 1: {
                TestTypeB* b = createTypeB(i * 1.0);
                controller.add<TestTypeB*>(b, stack);
                break;
            }
            case 2: {
                TestTypeC* c = createTypeC("perf");
                controller.add<TestTypeC*>(c, stack);
                break;
            }
        }
    }

    double start = get_time_seconds();
    int fetched = 0;
    while (true) {
        TestTypeA* a = controller.fetch<TestTypeA*>(stack);
        if (!a) break;
        deleteTypeA(a);
        fetched++;
    }
    while (true) {
        TestTypeB* b = controller.fetch<TestTypeB*>(stack);
        if (!b) break;
        deleteTypeB(b);
        fetched++;
    }
    while (true) {
        TestTypeC* c = controller.fetch<TestTypeC*>(stack);
        if (!c) break;
        deleteTypeC(c);
        fetched++;
    }
    double elapsed = get_time_seconds() - start;

    printf("    Fetched %d items\n", fetched);
    print_perf_result("perf_fetch_100k", elapsed, fetched);

    controller.erase(stack);
}

void perf_search_100k(void) {
    printf("    Searching in stack with %d objects...\n", PERFORMANCE_COUNT);
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;

    for (int i = 0; i < PERFORMANCE_COUNT; i++) {
        switch (i % 3) {
            case 0: {
                TestTypeA* a = createTypeA(i);
                if (i == 0) {
                    stack = controller.add<TestTypeA*>(a);
                } else {
                    controller.add<TestTypeA*>(a, stack);
                }
                break;
            }
            case 1: {
                TestTypeB* b = createTypeB(i * 1.0);
                controller.add<TestTypeB*>(b, stack);
                break;
            }
            case 2: {
                TestTypeC* c = createTypeC("perf");
                controller.add<TestTypeC*>(c, stack);
                break;
            }
        }
    }

    double start = get_time_seconds();
    int found = 0;
    for (int i = 0; i < 1000; i++) {
        found = controller.search<TestTypeA*>(stack);
    }
    double elapsed = get_time_seconds() - start;

    printf("    Found %d items per search, ran 1000 searches\n", found);
    print_perf_result("perf_search_100k", elapsed, 1000);

    controller.clean(stack);
    controller.erase(stack);
}

void perf_list_100k(void) {
    printf("    Converting stack with %d objects to array...\n", PERFORMANCE_COUNT);
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;

    for (int i = 0; i < PERFORMANCE_COUNT; i++) {
        switch (i % 3) {
            case 0: {
                TestTypeA* a = createTypeA(i);
                if (i == 0) {
                    stack = controller.add<TestTypeA*>(a);
                } else {
                    controller.add<TestTypeA*>(a, stack);
                }
                break;
            }
            case 1: {
                TestTypeB* b = createTypeB(i * 1.0);
                controller.add<TestTypeB*>(b, stack);
                break;
            }
            case 2: {
                TestTypeC* c = createTypeC("perf");
                controller.add<TestTypeC*>(c, stack);
                break;
            }
        }
    }

    double start = get_time_seconds();
    int count = controller.search<TestTypeA*>(stack);
    TestTypeA** list = controller.list<TestTypeA*>(stack);
    double elapsed = get_time_seconds() - start;

    printf("    Converted %d items to array\n", count);
    print_perf_result("perf_list_100k", elapsed, count);

    for (int i = 0; i < count; i++) {
        deleteTypeA(list[i]);
    }
    delete[] list;
    controller.clean(stack);
    controller.erase(stack);
}

TEST_LIST = {
    { "test_add_single", test_add_single },
    { "test_add_multiple_mixed", test_add_multiple_mixed },
    { "test_identify_positive", test_identify_positive },
    { "test_identify_negative", test_identify_negative },
    { "test_search_found", test_search_found },
    { "test_search_not_found", test_search_not_found },
    { "test_fetch_single", test_fetch_single },
    { "test_fetch_all", test_fetch_all },
    { "test_fetch_empty", test_fetch_empty },
    { "test_list_conversion", test_list_conversion },
    { "test_erase_stack", test_erase_stack },
    { "test_clean_objects", test_clean_objects },
    { "test_empty_stack", test_empty_stack },
    { "test_single_element", test_single_element },
    { "perf_push_100k", perf_push_100k },
    { "perf_fetch_100k", perf_fetch_100k },
    { "perf_search_100k", perf_search_100k },
    { "perf_list_100k", perf_list_100k },
    { 0 }
};
