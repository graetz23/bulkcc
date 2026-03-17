/**
 * @file bulkcc.h
 * @brief Main include file for BULKCC - A Generic Bulk Container Library
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
 *
 * @defgroup BULKCC BULKCC Library
 * @brief A generic bulk container library for managing heterogeneous object stacks
 *
 * BULKCC (Bulk Container) is a C++98-compatible template library that provides
 * a flexible mechanism for managing collections of objects of different types
 * in a linked-list style stack structure.
 *
 * @section features Key Features
 * - Type-safe generic container for any object type
 * - Linked-list based stack implementation
 * - Search, fetch, and list operations
 * - Automatic memory management
 * - C++98 compatible (no modern C++ features required)
 *
 * @section usage Basic Usage
 * @code
 * #include "bulkcc.h"
 *
 * BULKCC::Controller controller;
 * MyClass* obj = new MyClass();
 * BULKCC::Obj* stack = controller.add<MyClass*>(obj);
 * controller.add<MyClass*>(new MyClass(), stack);
 * @endcode
 */

#ifndef __bulkcc_h__
#define __bulkcc_h__

#include "./bulkccController.h" // BULKCC::Controller

namespace BULKCC {

/// use and share by the MIT License (MIT)
#define _BULKCC_LICENSE_ "MIT"

/// http://www.namegenerator.biz/female-name-generator.php
#define _BULKCC_PACKAGE_ "Kiera Gothe" // since 20100805

/// first load test are done for prototype of binary hash function and tree
#define _BULKCC_VERSION_ "0.16"
#define _BULKCC_DATE_ 20160106

void testBULKCC( void ); // test function

} // namespace BULKCC

#endif // __bulkcc_h__
