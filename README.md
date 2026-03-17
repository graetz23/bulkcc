# BULKCC - Bulk Container Library

```
       BULKCC - Bulk Container Library
       ================================

                    +---------------+
                    |   STACK       |
                    |   (Top)       |
           +--------|    [Obj3]     |--------+
           |        +---------------+        |
           |                |                |
           v                v                v
    +------------+   +------------+   +------------+
    |   [Obj2]   |   |   [Obj1]   |   |   [Obj0]   |
    +------------+   +------------+   +------------+
          |                |                |
          v                v                v
    +------------+   +------------+   +------------+
    |  <T>* obj  |   |  <T>* obj  |   |  <T>* obj  |
    +------------+   +------------+   +------------+


       How the stack grows when you add items:

       Initial:                    After add(item1):
       +--------+                   +--------+
       | nullptr|                   | item1  | <- top
       +--------+                   +--------+

       After add(item2):             After add(item3):
       +--------+                   +--------+
       | item2  | <- top             | item3  | <- top
       +--------+                   +--------+
       | item1  |                   | item2  |
       +--------+                   +--------+
                                   | item1  |
                                   +--------+
```

## Overview

BULKCC (Bulk Container) is a C++98-compatible generic container library that provides flexible management of heterogeneous object stacks. It allows you to store and manage collections of different object types in a linked-list based stack structure.

## Author

**Christian** (graetz23@gmail.com)

## Version

0.16 (2016-01-06)

## Key Advantages

- **C++98 Compatible**: Works with legacy C++ codebases - no modern C++ features required
- **Type-Safe**: Template-based design ensures type safety at compile time
- **Heterogeneous Storage**: Store objects of different types in the same stack
- **Flexible Operations**: Search, fetch, and list objects by type
- **Linked-List Design**: Efficient insertion at the top of the stack (O(1))
- **Memory Management**: Clean and erase methods for proper cleanup
- **Lightweight**: Minimal dependencies, no external libraries required
- **Exception Handling**: Custom exception class for error reporting

## Architecture

The library consists of four main components:

| Class | Purpose |
|-------|---------|
| `Controller` | Main interface for managing stacks |
| `Obj` | Abstract base class for stack nodes |
| `ObjTemplate<T>` | Template class for type-specific nodes |
| `Exception` | Error reporting |

## Simple Application Example

```cpp
#include "bulkcc.h"
#include <iostream>
#include <string>

int main() {
    // Create a controller to manage your stack
    BULKCC::Controller controller;

    // Add some objects to the stack
    std::string* str1 = new std::string("Hello");
    std::string* str2 = new std::string("World");
    std::exception* exc1 = new std::exception();

    // Create the stack with first object
    BULKCC::Obj* stack = controller.add<std::string*>(str1);

    // Add more objects to the stack
    controller.add<std::string*>(str2, stack);
    controller.add<std::exception*>(exc1, stack);

    // Search for objects of a specific type
    int stringCount = controller.search<std::string*>(stack);
    int excCount = controller.search<std::exception*>(stack);

    std::cout << "Found " << stringCount << " strings" << std::endl;
    std::cout << "Found " << excCount << " exceptions" << std::endl;

    // Fetch an object (removes it from stack)
    std::string* fetched = controller.fetch<std::string*>(stack);
    if (fetched) {
        std::cout << "Fetched: " << *fetched << std::endl;
        delete fetched;
    }

    // Get all remaining strings as an array
    int remaining = controller.search<std::string*>(stack);
    std::string** list = controller.list<std::string*>(stack);

    // Clean up the list
    for (int i = 0; i < remaining; i++) {
        delete list[i];
    }
    delete[] list;

    // Clean all stored objects (but keep stack structure)
    controller.clean(stack);

    // Erase the entire stack (delete all nodes)
    controller.erase(stack);

    std::cout << "Done!" << std::endl;
    return 0;
}
```

## Building

### Prerequisites

- CMake 3.14+
- Ninja build tool
- C++ compiler (GCC/Clang)

### Build Commands

```bash
# Configure and build (Debug)
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# Build all targets
ninja -C build
```

### Running Tests

```bash
# Run all tests
ctest --test-dir build --output-on-failure

# Run with verbose output
./build/bulkcc_tests -s
```

## Documentation

HTML documentation is available in the `doc/html/` directory. Open `index.html` in a web browser to view.

## License

BULKCC is distributed under the **MIT License (MIT)**.

See [LICENSE.md](LICENSE.md) for full license text.

## GitHub Repository

For the latest version, bug reports, and feature requests, visit:
https://github.com/anomalyco/bulkcc
