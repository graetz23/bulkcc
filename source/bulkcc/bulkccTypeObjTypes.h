/**
 * @file bulkccTypeObjTypes.h
 * @brief Type definitions for object types in BULKCC
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

#ifndef __bulkccObjTypes_h__
#define __bulkccObjTypes_h__

namespace BULKCC {

#define _VERSION_BULKCC_TYPE_ObjTypes_ 0.16 // 20141231
// #define _DEBUG_BULKCC_TYPE_ObjTypes_

namespace TYPE {

/**
 * @namespace BULKCC::TYPE
 * @brief Type namespace containing object type enumerations
 *
 * This namespace contains type definitions used throughout the BULKCC library.
 */

/**
 * @enum ObjType
 * @brief Enumeration of object types in BULKCC
 *
 * Defines the different types of objects that can be stored in the stack.
 */
enum ObjType {
  Template = 0  ///< Template-based object type
}; // enum ObjType

} // namespace TYPE

} // namespace BULKCC

#endif // __bulkccObjTypes_h__
