/** 
 * @file bulkccException.h
 * @brief Exception class for BULKCC errors
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
 * @class BULKCC::Exception
 * @brief Exception class for reporting BULKCC errors.
 *
 * @{
 */

#ifndef __bulkccException_h__
#define __bulkccException_h__

#include "./bulkccIncl.h" /// common includes and typedefs

namespace BULKCC {

#define _VERSION_BULKCC_Exception_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Exception_

/**
 * @brief Exception class for BULKCC errors
 *
 * This class is thrown when an error occurs in the BULKCC library,
 * such as requesting an unknown object type.
 */
class Exception {
  public:

    /**
     * @brief Constructs an exception with a message
     * @param msg The error message
     */
    Exception( Str msg );

    /** @brief Destructor */
    ~Exception( void );

    /**
     * @brief Gets the error message
     * @return C-string containing the error message
     */
    const char* what( void ) const;

  protected:
  
    /** @brief Stored exception message */
    Str _msg;

}; // class Exception 

} // namespace BULKCC

/** @} */

#endif // __bulkccException_h__
