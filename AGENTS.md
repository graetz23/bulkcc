# BULKCC Developer Guide

Guidelines for agents operating in this repository.

---

## Build Commands

### Prerequisites
- CMake 3.14+, Ninja build tool, C++ compiler (GCC/Clang)

### Build
```bash
# Configure and build (Debug)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja -C build

# Build specific target
ninja -C build bulkcc
ninja -C build bulkcc_tests

# Clean build
rm -rf build && cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

### Run Application
```bash
./build/bulkcc
```

---

## Testing

### Run All Tests
```bash
ctest --test-dir build --output-on-failure
```

### Run Single Test (Catch2)
```bash
# List all test cases
./build/bulkcc_tests --list-tests

# Run specific test (exact name)
./build/bulkcc_tests "Controller instantiation"

# Run by tag
./build/bulkcc_tests "[controller]"
./build/bulkcc_tests "[add]"
./build/bulkcc_tests "[search]"
./build/bulkcc_tests "[fetch]"
./build/bulkcc_tests "[perf]"

# With verbose output
./build/bulkcc_tests -s
./build/bulkcc_tests "Test Name" -s
```

### Test Tags
`[controller]`, `[add]`, `[search]`, `[fetch]`, `[list]`, `[clean]`, `[erase]`, `[traverse]`, `[edge]`, `[identify]`, `[perf]`

---

## Documentation

### Generate Doxygen Docs
```bash
doxygen Doxyfile
```
Output: `doc/html/index.html` (49 HTML files with class hierarchy)

---

## Code Style

### File Organization
```
source/bulkcc/
  bulkcc.h              # Main include
  bulkcc.cpp            # Test/main
  bulkccController.h    # Controller + templates
  bulkccController.cpp  # Controller methods
  bulkccObj.h           # Base class
  bulkccObj.cpp         # Implementation
  bulkccObjTemplate.h   # Template class
  bulkccException.h/.cpp
  bulkccIncl.h          # Common includes
  bulkccTypeObjTypes.h  # Types
tests/
  test_bulkcc.cpp
  DummyA.h, DummyB.h, DummyC.h
```

### Header Guards
```cpp
#ifndef __bulkccController_h__
#define __bulkccController_h__
#endif
```

### License Headers
All source files must include MIT License header:
```cpp
/** 
 * @file bulkccController.h
 * @brief Brief description
 * @author Christian (graetz23@gmail.com)
 *
 * BULKCC is distributed under the MIT License (MIT)
 * Copyright (c) 2008-2024 Christian (graetz23@gmail.com)
 * ... (full MIT license text)
 */
```

### Include Order
1. Associated header, 2. System/library, 3. Project, 4. Test headers (tests only)

### Naming Conventions
- Classes: PascalCase (`Controller`, `ObjTemplate`)
- Abstract classes: suffix with base name (`Obj`)
- Methods: PascalCase (`add()`, `search()`, `fetch()`)
- Member variables: underscore prefix (`_obj`, `_objIsSet`)
- Constants/Macros: UPPER_CASE (`TYPE::ObjType`, `_VERSION_BULKCC_Controller_`)
- Namespaces: All caps (`BULKCC`, `TYPE`)

### Formatting Rules
- Braces: opening on same line, closing on own line
- Indentation: 2 spaces, no tabs
- Line length: under 100 characters
- Spacing: `if (`, `while (`, no space before parentheses
- Operators: `a = b`, `a + b`, no excessive spaces

### Template Usage
Template implementations in headers:
```cpp
template< class T > Obj* Controller::add( T object ) {
  // implementation
}
```

### Memory Management
**CRITICAL: Always nullify after delete:**
```cpp
delete _obj;
_obj = 0;
```

### Error Handling
Use `BULKCC::Exception` with descriptive messages:
```cpp
throw Exception( "Controller::create - unknown type requested" );
```

### Debug Macros
```cpp
#ifdef _DEBUG_Controller_
  std::cout << "message" << std::endl << std::flush;
#endif
```
Enable by uncommenting in header: `#define _DEBUG_BULKCC_Controller_`

---

## Common Tasks

### Add Test Class
1. Create `tests/DummyX.h` implementing `BULKCC::Obj`
2. Add to `tests/test_bulkcc.cpp`

### Add Test Case
```cpp
TEST_CASE("Test description", "[tag]") {
    BULKCC::Controller controller;
    // Arrange, Act, Assert
    REQUIRE(condition);
}
```

### Modify Core Library
1. Edit relevant source file in `source/bulkcc/`
2. Rebuild: `ninja -C build`
3. Run tests: `ctest --test-dir build --output-on-failure`

---

## Important Notes

- **C++98** in core library (no C++11+ features)
- **C++14** in tests (Catch2 requirement)
- **Always clean memory** - use `erase()` or delete objects
- **Library provides stack structure** - caller manages stored object memory
- **Catch2** is automatically fetched via FetchContent in CMake
