/**
 * @file bulkccStackGuard.h
 * @brief RAII wrapper for automatic stack cleanup
 * @author Christian (graetz23@gmail.com)
 *
 * BULKCC is distributed under the MIT License (MIT); this file is part of.
 *
 * Copyright (c) 2008-2024 Christian (graetz23@gmail.com)
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __bulkccStackGuard_h__
#define __bulkccStackGuard_h__

#include "./bulkccStack.h"

namespace BULKCC {

#define _VERSION_BULKCC_StackGuard_ 1.0

#define _DEBUG_BULKCC_StackGuard_

/**
 * @class StackGuard
 * @brief RAII wrapper for automatic stack cleanup
 *
 * The StackGuard class provides automatic cleanup of a Stack when
 * it goes out of scope. This is useful for ensuring resources
 * are properly released even when exceptions are thrown.
 *
 * @section example Example
 * @code
 * void myFunction() {
 *     BULKCC::Stack stack;
 *     BULKCC::StackGuard guard(stack); // stack will be erased when function ends
 *
 *     stack.push<int>(42);
 *     // stack.erase() called automatically when guard is destroyed
 * }
 * @endcode
 *
 * @see Stack
 */
class StackGuard {
public:

  /**
   * @brief Constructor with stack reference
   *
   * Creates a guard for the given stack.
   *
   * @param stack Reference to the Stack to guard
   * @param autoErase If true, call erase() on destruction (default: true)
   */
  StackGuard(Stack& stack, bool autoErase = true);

  /**
   * @brief Constructor with stack pointer
   *
   * Creates a guard for the given stack.
   *
   * @param stack Pointer to the Stack to guard
   * @param autoErase If true, call erase() on destruction (default: true)
   */
  StackGuard(Stack* stack, bool autoErase = true);

  /**
   * @brief Destructor
   *
   * If autoErase is true, calls erase() on the guarded stack.
   */
  ~StackGuard();

  /**
   * @brief Release the guard
   *
   * Prevents automatic erasure on destruction. After calling
   * release(), the stack will not be erased when the guard
   * is destroyed.
   */
  void release();

private:

  Stack* _stack;
  bool _autoErase;

};

inline StackGuard::StackGuard(Stack& stack, bool autoErase)
    : _stack(&stack), _autoErase(autoErase) {
#ifdef _DEBUG_BULKCC_StackGuard_
  std::cout << "StackGuard::StackGuard(Stack&)" << std::endl << std::flush;
#endif
}

inline StackGuard::StackGuard(Stack* stack, bool autoErase)
    : _stack(stack), _autoErase(autoErase) {
#ifdef _DEBUG_BULKCC_StackGuard_
  std::cout << "StackGuard::StackGuard(Stack*)" << std::endl << std::flush;
#endif
}

inline StackGuard::~StackGuard() {
#ifdef _DEBUG_BULKCC_StackGuard_
  std::cout << "StackGuard::~StackGuard()" << std::endl << std::flush;
#endif
  if (_autoErase && _stack != 0) {
    _stack->erase();
  }
}

inline void StackGuard::release() {
  _stack = 0;
}

}

#endif
