# AGENTS.md - BULKCC Development Guide

Guidelines for agentic coding agents operating in the BULKCC repository.

## Project Overview

- **Name**: BULKCC - C++ Bulk Stack Library
- **Language**: C++98 (ANSI C++ compatible)
- **License**: MIT
- **Version**: 0.16
- **Author**: Christian (graetz23@gmail.com)
- **Copyright**: 2016-2026

BULKCC is a template-based bulk stack for storing typed objects during parsing/tokenizing.

---

## Build Commands

```bash
# Configure with CMake and Ninja
cmake -B build -G Ninja

# Build main library
ninja -C build bulkcc

# Build tests
ninja -C build bulkcc_test

# Run all tests
./build/bulkcc_test

# Run single test
./build/bulkcc_test test_add_single

# Run tests matching pattern
./build/bulkcc_test test_add
./build/bulkcc_test perf_

# Generate Doxygen docs
doxygen Doxyfile
# View: doxygen/html/index.html
```

---

## Code Style Guidelines

### Language Standard

- **STRICTLY C++98** - No modern C++ features (no auto, no range-for, no nullptr, no smart pointers)
- Use `0` instead of `nullptr` for null pointers
- Use `static_cast<T>()` for explicit type conversions

### Copyright Header

Every source file must include this MIT License header:

```cpp
/** 
 * @file <filename>
 * @brief <brief description>
 * @author Christian
 *
 * BULKCC is distributed under the MIT License (MIT); this file is part of.
 *
 * Copyright (c) 2016-2026 Christian (graetz23@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 */
```

### Doxygen Documentation

Use Doxygen-style comments: `@brief`, `@details`, `@class`, `@param`, `@return`, `@note`, `@warning`

### Naming Conventions

| Type | Convention | Example |
|------|------------|---------|
| Classes | PascalCase | `Controller`, `ObjTemplate` |
| Methods | camelCase | `add()`, `fetch()` |
| Private Members | `_camelCase` | `_obj`, `_nextObj` |
| Constants | UPPER_CASE | `PERFORMANCE_COUNT` |
| Defines | UPPER_CASE | `_VERSION_BULKCC_Controller_` |

### Import Guidelines

- Use relative paths with descriptive comments
- Example: `#include "./bulkccController.h" // BULKCC::Controller`

### Formatting

- Use tabs for indentation
- Opening brace on same line: `void method() {`
- Closing brace on own line: `} // method`

### Error Handling

- Use `BULKCC::Exception` for library errors
- Throw with descriptive message: `throw Exception("Controller::create - unknown type requested")`

### Memory Management

- **Manual management only** (pre-smart pointer era)
- Always pair `new` with `delete` and `new[]` with `delete[]`
- Call `clean()` before `erase()` to release user objects
- **CRITICAL**: Set pointers to 0 after delete:
  ```cpp
  delete _obj;
  _obj = 0;  // Always do this!
  ```

---

## Test Guidelines

### Test Framework

- **acutest** (auto-downloaded via CMake FetchContent)
- Include: `#define ACUTEST_LIBRARY` then `#include "acutest.h"`

### Test Functions

```cpp
void test_function_name(void) {
    BULKCC::Controller controller;
    TestTypeA* obj = createTypeA(1);
    BULKCC::Obj* stack = controller.add<TestTypeA*>(obj);
    TEST_CHECK(stack != 0);
    controller.clean(stack);
    controller.erase(stack);
}
```

### Test Registration

```cpp
TEST_LIST = {
    { "test_name", test_name },
    { 0 }  // Must end with null
};
```

---

## Important Notes

### Known Limitations

1. **O(n) complexity in fetch()**: Traverses from top of stack
2. **O(n) complexity in list()**: Traverses entire stack and calls fetch()
3. **No smart pointers**: Manual memory management required
4. **No thread safety**: Not thread-safe

### Memory Safety

- Always call `controller.clean(stack)` before `controller.erase(stack)`
- Set `_obj = 0` after `delete _obj` to avoid dangling pointers
- Test for memory leaks using valgrind if needed

### Build Flags

- CMake uses C++98 standard
- Warning flag: `-Wall`
- No optimizations by default (add `-DCMAKE_BUILD_TYPE=Release`)
