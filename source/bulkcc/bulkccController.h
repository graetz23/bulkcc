/** 
 * @file bulkccController.h
 * @brief Controller class for managing the bulk stack
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
 * @class BULKCC::Controller
 * @brief Main controller class for managing the bulk stack.
 *
 * This class provides all the operations needed to work with the bulk stack,
 * including adding objects, searching by type, fetching objects, and converting
 * to arrays. All operations are template-based to support any data type.
 *
 * @note The Controller does not own the objects - it manages the stack.
 *       Callers are responsible for deleting objects returned by fetch() and list().
 *
 * @{
 */

#ifndef __bulkccController_h__
#define __bulkccController_h__

#include "./bulkccObjTemplate.h" // BULKCC::ObjTemplate

namespace BULKCC {

#define _VERSION_BULKCC_Controller_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Controller_

/**
 * @brief Controller for managing the bulk stack
 *
 * This is the main class for interacting with the bulk stack. It provides
 * methods to add objects of any type, search for objects by type, fetch
 * objects from the stack, and convert the stack to arrays.
 *
 * The stack operates as a linked list where objects can be pushed in
 * arbitrary sequence and retrieved based on their type.
 */
class Controller {
  public:

    /** @brief Default constructor */
    Controller( void );

    /** @brief Virtual destructor */
    virtual ~Controller( void );

    /**
     * @brief Erases all objects in the stack
     * @param obj Pointer to the top of the stack
     *
     * This method deletes all Obj objects in the stack, including their
     * internal data. Use clean() first if you want to keep the objects
     * but remove them from the stack.
     */
    void erase( Obj* obj );

    /**
     * @brief Cleans all objects added to Obj containers
     * @param obj Pointer to the top of the stack
     *
     * This method deletes all the user objects stored in the stack
     * containers but keeps the container structure intact.
     */
    void clean( Obj* obj );

    /**
     * @brief Adds the first object to the stack
     * @tparam T The type of object to add
     * @param object The object to add
     * @return Pointer to the new top of the stack
     *
     * Use this method to add the first object to an empty stack.
     * For subsequent additions, use the two-parameter add() method.
     */
    template< class T > Obj* add( T object );

    /**
     * @brief Adds an object to the top of the stack
     * @tparam T The type of object to add
     * @param object The object to add
     * @param obj Reference to the current top of the stack
     *
     * This method adds a new object to the top of the stack and updates
     * the stack pointer to reference the new top.
     */
    template< class T > void add( T object, Obj*& obj );

    /**
     * @brief Identifies if an object is of a specific type
     * @tparam T The type to check for
     * @param obj The object to check
     * @return true if the object is of type T, false otherwise
     *
     * Uses dynamic_cast to check if the object is an ObjTemplate<T>.
     */
    template< class T > bool identify( Obj* obj );

    /**
     * @brief Searches for objects of a specific type
     * @tparam T The type to search for
     * @param obj Reference to the top of the stack
     * @return The number of objects of type T found
     *
     * This method traverses the entire stack and counts all objects
     * of the specified type that have a valid (non-NULL) internal object.
     */
    template< class T > int search( Obj*& obj );

    /**
     * @brief Fetches an object of a specific type
     * @tparam T The type of object to fetch
     * @param obj Reference to the top of the stack
     * @return The first object of type T, or 0 if none found
     *
     * @warning This method has O(n) complexity and traverses from the
     *          top of the stack. For large stacks with many non-matching
     *          types, this can be slow.
     *
     * The fetched object is removed from the stack and returned to the
     * caller, who is responsible for deleting it.
     */
    template< class T > T fetch( Obj*& obj );

    /**
     * @brief Gets a list of all objects of a specific type
     * @tparam T The type of objects to list
     * @param obj Reference to the top of the stack
     * @return Array of pointers to objects of type T
     *
     * @warning This method has O(n) complexity as it traverses the
     *          entire stack and calls fetch() for each matching object.
     *
     * The returned array is dynamically allocated and must be deleted
     * by the caller, along with each individual object.
     */
    template< class T > T* list( Obj*& obj );

  private:

    /**
     * @brief Creates a new stack object
     * @tparam T The type of object to create
     * @param objType The type of stack object to create
     * @return Pointer to the newly created Obj object
     *
     * Internal method used to instantiate the appropriate object type.
     */
    template< class T > Obj* create( TYPE::ObjType objType );

};
// class Controller

// /// //// PUBLIC //// /// //
/**
 * @brief Adds the first object to the stack
 * @tparam T The type of object to add
 * @param object The object to add
 * @return Pointer to the new top of the stack
 */
template< class T > Obj*
Controller::add( T object ) {
  Obj* nextObj = create< T >( TYPE::Template );
  ObjTemplate< T >* nextObjTemplateObj = (ObjTemplate< T >*)nextObj;
  nextObjTemplateObj->add( object );
  return nextObjTemplateObj->getAsBaseObj( );
}

/**
 * @brief Adds an object to the top of the stack
 * @tparam T The type of object to add
 * @param object The object to add
 * @param obj Reference to the current top of the stack
 */
template< class T > void
Controller::add( T object, Obj*& obj ) {
  Obj* newObj = add< T >( object );
  newObj->setNextObj( obj );
  obj = newObj;
}

/**
 * @brief Identifies if an object is of a specific type
 * @tparam T The type to check for
 * @param obj The object to check
 * @return true if the object is of type T, false otherwise
 */
template< class T > bool
Controller::identify( Obj* obj ) {
  bool result = false;
  ObjTemplate< T >* objTemplate = dynamic_cast< ObjTemplate< T >* >( obj );
  if( objTemplate == 0 ) {
#ifdef _DEBUG_Controller_
    std::cout << "castObj is NOT " << obj->getObjTypeAsString( ) << std::endl << std::flush;
#endif // _DEBUG_Controller_
    result = false;
  } else {
#ifdef _DEBUG_Controller_
    std::cout << "castObj is " << obj->getObjTypeAsString( ) << std::endl << std::flush;
#endif // _DEBUG_Controller_
    result = true;
  }
  return result;
}

/**
 * @brief Searches for objects of a specific type
 * @tparam T The type to search for
 * @param obj Reference to the top of the stack
 * @return The number of objects of type T found
 */
template< class T > int
Controller::search( Obj*& obj ) {
  int noOfFound = 0;
  Obj* lastObj = obj;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false;
    else {
      bool found = identify< T >( lastObj );
      if( found ) {
        bool isSet = lastObj->checkObj( );
        if( isSet )
          noOfFound++;
      }
      lastObj = lastObj->getNextObj( );
    }
  }
  return noOfFound;
}

/**
 * @brief Fetches an object of a specific type
 * @tparam T The type of object to fetch
 * @param obj Reference to the top of the stack
 * @return The first object of type T, or 0 if none found
 */
template< class T > T
Controller::fetch( Obj*& obj ) {
  T object = 0;
  Obj* lastObj = obj;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false;
    else {
      bool found = identify< T >( lastObj );
      if( found ) {
        ObjTemplate< T >* objTemplate = (ObjTemplate< T >*)( lastObj );
        object = objTemplate->fetch( );
        if( object != 0 )
          search = false;
      }
      lastObj = lastObj->getNextObj( );
    }
  }
  return object;
}

/**
 * @brief Gets a list of all objects of a specific type
 * @tparam T The type of objects to list
 * @param obj Reference to the top of the stack
 * @return Array of pointers to objects of type T
 */
template< class T > T*
Controller::list( Obj*& obj ) {
  int noOfObjs = search< T >( obj );
  T* objectList = new T[ noOfObjs ];
  T object = 0;
  Obj* lastObj = obj;
  int positionInList = 0;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false;
    else {
      bool found = identify< T >( lastObj );
      if( found ) {
        ObjTemplate< T >* objTemplate = (ObjTemplate< T >*)( lastObj );
        object = objTemplate->fetch( );
        objectList[ positionInList++ ] = object;
      }
      lastObj = lastObj->getNextObj( );
    }
  }
  return objectList;
}
// /// //// PUBLIC //// /// //

// /// //// PRIVATE //// /// //
/**
 * @brief Creates a new stack object
 * @tparam T The type of object to create
 * @param objType The type of stack object to create
 * @return Pointer to the newly created Obj object
 */
template< class T > Obj*
Controller::create( TYPE::ObjType objType ) {
  Obj* obj;
  switch( objType ) {
    case TYPE::Template:
      obj = new ObjTemplate< T >( );
      break;
    default:
      throw Exception(
        "Controller::create - unknown type of Obj object requested" );
      break;
  };
  return obj;
}
// /// //// PRIVATE //// /// //

} // namespace BULKCC

/** @} */

#endif // __bulkccController_h__
