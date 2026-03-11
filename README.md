# BULKCC - C++ Bulk Stack Library

**Version 0.16** | [LICENSE](LICENSE.md) | Author: Christian (graetz23@gmail.com)

---

## Overview

BULKCC is a lightweight, template-based C++ library that provides a **bulk stack** data structure for storing typed objects during parsing and tokenizing workflows. It allows you to push objects of any type onto a stack in arbitrary sequence and later retrieve them by type.

## Main Purpose

BULKCC is designed for scenarios where a parser or tokenizer generates typed data or objects in an unknown sequence. It provides:

- **Temporary storage** for typed objects during parsing/tokenizing
- **Type-based retrieval** - search and fetch objects by their C++ type
- **Stack-based organization** - LIFO (Last In, First Out) behavior
- **Array conversion** - convert stored objects to C-style arrays

## Advantages

| Feature | Description |
|---------|-------------|
| **ANSI C++ Compatible** | Works with older C++ compilers (C++98 and later). No modern C++ features required. |
| **Template-Based Type Safety** | Full compile-time type checking through C++ templates |
| **Zero Dependencies** | No external libraries required - self-contained implementation |
| **Lightweight** | Minimal overhead - simple linked list structure |
| **Open Source** | Released under the MIT License |
| **Well Documented** | Full Doxygen documentation available |

## Architecture

BULKCC consists of three main components:

1. **`Obj`** (`bulkccObj.h`) - Abstract base class for stack objects
2. **`ObjTemplate<T>`** (`bulkccObjTemplate.h`) - Template class for storing typed objects
3. **`Controller`** (`bulkccController.h`) - Main interface for stack operations

```
Stack (linked list):
┌─────┐   ┌─────┐   ┌─────┐   ┌─────┐
│ Obj │ → │ Obj │ → │ Obj │ → │ Obj │ → NULL
│  A  │   │  B  │   │  A  │   │  C  │
└─────┘   └─────┘   └─────┘   └─────┘
```

## Performance

Benchmark results (100,000 objects, mixed types):

| Operation | Time | Rate |
|-----------|------|------|
| **Push** (add to stack) | ~7ms | 0.07 μs/item |
| **Search** (count by type) | ~1.5s | 1.5 ms/search |
| **List** (convert to array) | ~5ms | 0.1 μs/item |
| **Fetch** (retrieve by type) | ~9ms* | 9 μs/item |

*Fetch performance scales with stack depth due to O(n) traversal from top.

### Known Limitations

- **`fetch()` has O(n) complexity** - It traverses from the top of the stack and stops at the first match. For large stacks with many non-matching types at the top, performance degrades.
- **`list()` has O(n) complexity** - It traverses the entire stack and calls `fetch()` for each matching object.

## Quick Start

```cpp
#include "bulkcc/bulkcc.h"

struct MyData { int id; };

int main() {
    BULKCC::Controller controller;
    BULKCC::Obj* stack = 0;

    // Add objects to the stack
    MyData* data1 = new MyData{1};
    MyData* data2 = new MyData{2};

    stack = controller.add<MyData*>(data1);
    controller.add<MyData*>(data2, stack);

    // Search for objects by type
    int count = controller.search<MyData*>(stack);  // Returns 2

    // Fetch objects
    MyData* fetched = controller.fetch<MyData*>(stack);  // Gets first match

    // Clean up
    controller.clean(stack);
    controller.erase(stack);

    return 0;
}
```

## Building

### Prerequisites

- C++98 compatible compiler (GCC, Clang, MSVC)
- CMake 3.14+
- Ninja build system (optional, but recommended)

### Build Commands

```bash
# Configure with CMake
cmake -B build -G Ninja

# Build main library
ninja -C build bulkcc

# Build and run tests
ninja -C build bulkcc_test
./build/bulkcc_test
```

### Generate Documentation

```bash
# Install Doxygen
doxygen Doxyfile

# View documentation
# Open doxygen/html/index.html in a browser
```

## File Structure

```
bulkcc/
├── CMakeLists.txt           # CMake build configuration
├── Doxyfile                 # Doxygen configuration
├── LICENSE.md               # MIT License
├── README.md                # This file
├── source/bulkcc/
│   ├── bulkcc.h             # Main header
│   ├── bulkcc.cpp           # Implementation
│   ├── bulkccController.h   # Controller class
│   ├── bulkccException.h    # Exception class
│   ├── bulkccIncl.h         # Common includes
│   ├── bulkccObj.h          # Base object class
│   ├── bulkccObj.cpp        # Base object implementation
│   ├── bulkccObjTemplate.h  # Template object class
│   └── bulkccTypeObjTypes.h # Type definitions
└── tests/
    ├── test_bulkcc.cpp      # Test suite
    └── src/
        ├── test_types.h     # Test type definitions
        └── test_types.cpp   # Test type implementations
```

## License

BULKCC is distributed under the MIT License. See [LICENSE.md](LICENSE.md) for details.

**Copyright (c) 2016-2026 Christian (graetz23@gmail.com)**
