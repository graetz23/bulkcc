/** 
 * @file bulkcc.h
 * @brief Main header file for BULKCC library
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @defgroup BULKCC BULKCC Library
 * @brief A C++ template-based bulk stack for storing typed data during parsing and tokenizing.
 *
 * BULKCC is an object-oriented C++ template-based stack for storing any type of data.
 * It is designed for scenarios where a parser or tokenizer generates typed data or objects
 * in unknown sequence, and BULKCC can be used to store them temporarily.
 *
 * Main features:
 * - Template-based type safety
 * - ANSI C++ compatible (no modern C++ features)
 * - Simple linked list implementation
 * - No external dependencies
 *
 * @{
 */

#ifndef __bulkcc_h__
#define __bulkcc_h__

#include "./bulkccController.h" // BULKCC::Controller

namespace BULKCC {

/** @brief License identifier */
#define _BULKCC_LICENSE_ "MIT"

/** @brief Package name */
#define _BULKCC_PACKAGE_ "Kiera Gothe" // since 20100805

/** @brief Library version */
#define _BULKCC_VERSION_ "0.16"

/** @brief Release date */
#define _BULKCC_DATE_ 20160106

/** 
 * @brief Test function for the BULKCC library
 * @details Runs basic validation tests on the bulk stack implementation.
 * This function is provided for manual testing and debugging.
 */
void testBULKCC( void );

} // namespace BULKCC

/** @} */

#endif // __bulkcc_h__
