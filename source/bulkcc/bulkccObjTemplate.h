/** 
 * @file bulkccObjTemplate.h
 * @brief Template class for typed stack objects
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
 * @class BULKCC::ObjTemplate<T>
 * @brief Template class for storing typed objects in the bulk stack.
 *
 * This class extends Obj and provides type-safe storage for any data type T.
 * It is used by the Controller to store objects of various types in the stack.
 *
 * @tparam T The type of object to store (typically a pointer type)
 *
 * @{
 */

#ifndef __bulkccObjTemplate_h__
#define __bulkccObjTemplate_h__

#include "./bulkccObj.h" // BULKCC::Obj

#define _VERSION_BULKCC_ObjTemplate_ 0.16 // 20141231
// #define _DEBUG_BULKCC_ObjTemplate_

namespace BULKCC {

/**
 * @brief Template class for typed stack objects
 *
 * This class provides type-safe storage for objects in the bulk stack.
 * Each ObjTemplate instance stores a single object of type T and maintains
 * a reference to the next object in the stack (inherited from Obj).
 *
 * @tparam T The type of object to store (typically a pointer type)
 */
template<class T>
class ObjTemplate : public Obj {
public:

  /** @brief Default constructor */
  ObjTemplate( void );

  /** @brief Virtual destructor */
  virtual ~ObjTemplate( void );

  /**
   * @brief Returns the type of this object
   * @return Always returns TYPE::Template
   */
  TYPE::ObjType getObjType( void );

  /**
   * @brief Returns the type of this object as a string
   * @return String representation of the object type
   */
  Str getObjTypeAsString( void );

  /**
   * @brief Stores an object in this container
   * @param object The object to store
   */
  void add( T object );

  /**
   * @brief Checks if a valid object is stored
   * @return true if the stored object is not NULL, false otherwise
   */
  bool checkObj( void );

  /**
   * @brief Deletes the stored object and sets internal pointer to NULL
   *
   * This method properly releases memory allocated for the stored object.
   * After calling this method, checkObj() will return false until a new
   * object is added via add().
   */
  void eraseObj( void );

  /**
   * @brief Fetches and removes the stored object
   * @return The stored object, or 0 if none
   *
   * This method returns the stored object and sets the internal pointer
   * to NULL, effectively removing it from this container without freeing
   * the memory. The caller is responsible for managing the returned object.
   */
  T fetch( void );

  /**
   * @brief Gets this template object as a base Obj pointer
   * @return Pointer to this object cast as Obj*
   */
  Obj* getAsBaseObj( void );

private:

  /** @brief The stored object */
  T _obj;

  /** @brief Flag indicating if object has been set */
  bool  _objIsSet;

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
  _obj = 0;
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
