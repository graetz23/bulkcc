/** 
 * @file bulkccObjTemplate.h
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

#ifndef __bulkccObjTemplate_h__
#define __bulkccObjTemplate_h__

#include "./bulkccObj.h" // BULKCC::Obj

#define _VERSION_BULKCC_ObjTemplate_ 0.15 // 20141231
// #define _DEBUG_BULKCC_ObjTemplate_

namespace BULKCC {

template<class T>
class ObjTemplate : public Obj { // fancy in C++ but never Java!
public:

  ObjTemplate( void ); /// constructor
  virtual ~ObjTemplate( void ); /// destructor

  TYPE::ObjType getObjType( void ); /// return type of object
  Str getObjTypeAsString( void ); /// return type of object as std::string
  void add( T object ); /// add an object
  bool checkObj( void ); /// return true if not NULL
  void eraseObj( void ); /// use delete operator for object
  T fetch( void ); /// fetch an object

  Obj* getAsBaseObj( void ); /// get this template object as base object

private:

  T _obj; // member
  bool  _objIsSet; // member

}; // class ObjTemplate

// constructor
template<class T>
ObjTemplate<T>::ObjTemplate( void ) {
    _obj = 0;
    _objIsSet = false;
} // ObjTemplate

// destructor
template<class T>
ObjTemplate<T>::~ObjTemplate( void ) {
  #ifdef _DEBUG_ObjTemplate_
  std::cout << getObjTypeAsString( ) << std::flush;
  std::cout << std::endl << std::flush;
  #endif // _DEBUG_ObjTemplate_
} // ~ObjTemplate

template<class T> TYPE::ObjType // return type of object
ObjTemplate<T>::getObjType( void ) { 
  return TYPE::Template;
} // getObjType

template<class T> Str // return type of object
ObjTemplate<T>::getObjTypeAsString( void ) { 
  return (Str)(typeid(this).name( ));
} // getObjType

template<class T> void // add an object
ObjTemplate<T>::add( T object ) {
  _obj = object;
} // add


template<class T> bool // return true if not NULL
ObjTemplate<T>::checkObj( void ) {
  T object = _obj;
  if( object == 0 )
    return false;
  else
    return true;
} // checkObj

template<class T> void  // use delete operator for object
ObjTemplate<T>::eraseObj( void ) {
  delete _obj;
} // eraseObj

template<class T> T // fetch an object
ObjTemplate<T>::fetch( void ) {
  T object = _obj;
  _obj = 0;
  return object;
} // store

template<class T> Obj* // get this template object as base object
ObjTemplate<T>::getAsBaseObj( void ) {
  return (Obj*)(this);
} // getAsBaseObj

} // namespace BULKCC

#endif // __bulkccObjTemplate_h__
