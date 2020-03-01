/** 
 * @file bulkccObj.h
 * @author Christian
 *
 * BULKCC is distributed under the MIT License (MIT); this file is part of.
 *
 * Copyright (c) 2008-2020 Christian (graetz23@gmail.com)
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

#ifndef __bulkccObj_h__
#define __bulkccObj_h__

#include "./bulkccException.h" // BULKCC::Exception
#include "./bulkccTypeObjTypes.h" // BULKCC::TYPE::ObjTypes

namespace BULKCC {

#define _VERSION_BULKCC_Obj_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Obj_

class Obj {
public:

  Obj( void ); /// constructor
  virtual ~Obj( void ); /// destructor

  virtual TYPE::ObjType getObjType( void ) = 0; /// return type of object
  virtual Str getObjTypeAsString( void ) = 0; /// return type of object as string
  virtual Obj* getAsBaseObj( void ) = 0; /// get it as base object
  virtual bool checkObj( void ) = 0; /// return true if not NULL
  virtual void eraseObj( void ) = 0; /// use delete operator for object

  void setNextObj( Obj*& obj ); /// set a Obj* object to this object
  Obj* getNextObj( void ); /// return member of type Obj*

private:

  Obj* _nextObj; /// pointer to next one

}; // class Obj

} // namespace BULKCC

#endif // __bulkccObj_h__
