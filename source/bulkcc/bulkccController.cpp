/** 
 * @file bulkccController.cpp
 * @author Christian
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

#include "./bulkccController.h" // header

namespace BULKCC {

// constructor
Controller::Controller( void ) {
} // Controller

// destructor
Controller::~Controller( void ) {
} // ~Controller

void // erase a Obj object
Controller::erase( Obj* obj ) {
  Obj* lastObj = obj;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false; // break down search
    else {
      Obj* deadObj = lastObj;
      lastObj = lastObj->getNextObj( );
      delete deadObj;
    } // if
  } // while
} // erase

void // erase all object added in Obj object
Controller::clean( Obj* obj ) {
  Obj* lastObj = obj;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false; // break down search
    else {
      lastObj->eraseObj( );
      lastObj = lastObj->getNextObj( );
    } // if
  } // while
} // clean

} // namespace BULKCC
