/**
 * @file bulkccException.h
 * @brief Exception class for BULKCC library errors
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

#ifndef __bulkccException_h__
#define __bulkccException_h__

#include "./bulkccIncl.h" /// common includes and typedefs

namespace BULKCC {

#define _VERSION_BULKCC_Exception_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Exception_

/**
 * @class Exception
 * @brief Exception class for BULKCC library errors
 *
 * The Exception class provides a simple mechanism for reporting errors
 * within the BULKCC library. It stores an error message that can be
 * retrieved using the what() method.
 *
 * @section usage Usage
 *
 * @code
 * try {
 *     // Code that might throw an exception
 *     throw BULKCC::Exception("Something went wrong");
 * } catch (BULKCC::Exception& e) {
 *     std::cout << "Error: " << e.what() << std::endl;
 * }
 * @endcode
 */
class Exception {
 public:

  /**
   * @brief Constructor with message
   *
   * Creates an exception with the specified error message.
   *
   * @param msg The error message to store
   */
  Exception( Str msg );

  /**
   * @brief Destructor
   */
  ~Exception( void );

  /**
   * @brief Get error message
   *
   * Returns a C-string describing the error.
   *
   * @return const char* Error message
   */
  const char* what( void ) const;

 protected:
  
  Str _msg; ///< Stored exception message

}; // class Exception 

} // namespace BULKCC

#endif // __bulkccException_h__
