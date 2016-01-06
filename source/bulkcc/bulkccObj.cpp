/** 
 * @file bulkccObj.cpp
 * @author Christian Scheiblich
 *
 * BULKCC is distributed under the MIT License (MIT); this file is part of.
 *
 * Copyright (c) 2008-2016 Christian Scheiblich (cscheiblich@gmail.com)
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

#include "./bulkccObj.h" // header

namespace BULKCC {

// /// //// PUBLIC //// /// //
// constructor
Obj::Obj( void ) {
  _nextObj = 0;
} // Obj

// destructor
Obj::~Obj( void ) {
} // ~Obj

void // glue an Obj object to this object
Obj::setNextObj( Obj*& obj ) {
  this->_nextObj = obj;
} // glueObj

Obj* // return member of type Obj*
Obj::getNextObj( void ) {
  return _nextObj;
}
// /// //// PUBLIC //// /// //


// /// //// PRIVATE //// /// //
// /// //// PRIVATE //// /// //

// /// //// PROTECTED //// /// //
// /// //// PROTECTED //// /// //

} // namespace BULKCC
