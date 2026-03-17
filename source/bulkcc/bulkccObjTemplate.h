/**
 * @file bulkccObjTemplate.h
 * @brief Template class for type-specific stack nodes
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

#ifndef __bulkccObjTemplate_h__
#define __bulkccObjTemplate_h__

#include "./bulkccObj.h" // BULKCC::Obj

#define _VERSION_BULKCC_ObjTemplate_ 0.16 // 20141231
// #define _DEBUG_BULKCC_ObjTemplate_

namespace BULKCC {

/**
 * @class ObjTemplate
 * @brief Template class for type-specific stack nodes
 *
 * The ObjTemplate class is a concrete implementation of the Obj base class
 * that can store objects of a specific type T. It provides type-safe storage
 * and retrieval of objects within the stack structure.
 *
 * @tparam T The type of object to store in this node
 *
 * @section overview Overview
 *
 * Each ObjTemplate node can hold one object of type T. The object is stored
 * as a member variable and can be added, fetched, or erased through the
 * provided methods.
 *
 * @section usage Usage
 *
 * This class is typically not used directly. Use the Controller class
 * to create and manage stacks:
 *
 * @code
 * BULKCC::Controller controller;
 * MyClass* obj = new MyClass();
 * BULKCC::Obj* stack = controller.add<MyClass*>(obj);
 * @endcode
 *
 * @see Controller
 * @see Obj
 */
template<class T>
class ObjTemplate : public Obj {
public:

  /**
   * @brief Default constructor
   *
   * Initializes the template node with no object (null) and marks
   * the object as not set.
   */
  ObjTemplate( void );

  /**
   * @brief Virtual destructor
   *
   * Cleans up the template node. If an object is stored, it should
   * be erased before destroying the node to avoid memory leaks.
   */
  virtual ~ObjTemplate( void );

  /**
   * @brief Get the object type
   *
   * Returns the type identifier for this template node.
   *
   * @return TYPE::ObjType Always returns TYPE::Template
   */
  TYPE::ObjType getObjType( void );

  /**
   * @brief Get the object type as string
   *
   * Returns a string representation of the template type.
   *
   * @return Str The type as a string (uses typeid)
   */
  Str getObjTypeAsString( void );

  /**
   * @brief Store an object in this node
   *
   * Stores the given object in this template node. Any previously
   * stored object is overwritten.
   *
   * @param object The object to store
   */
  void add( T object );

  /**
   * @brief Check if this node contains an object
   *
   * Determines whether this template node currently holds a non-null object.
   *
   * @return true if a valid object is stored, false otherwise
   */
  bool checkObj( void );

  /**
   * @brief Delete the stored object
   *
   * Deletes the object stored in this node and sets the internal
   * pointer to null. Does not delete the node itself.
   */
  void eraseObj( void );

  /**
   * @brief Fetch and remove the stored object
   *
   * Returns the stored object and sets the internal pointer to null.
   * The caller takes ownership of the returned object.
   *
   * @return The stored object, or 0 if none
   *
   * @post The internal object pointer is set to null
   */
  T fetch( void );

  /**
   * @brief Get this template as base Obj pointer
   *
   * Returns a pointer to this object cast to the base Obj type.
   *
   * @return Obj* Pointer to this as base class
   */
  Obj* getAsBaseObj( void );

private:

  T _obj;       ///< The stored object
  bool _objIsSet; ///< Flag indicating if an object is stored

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
