/**
 * @file bulkccController.h
 * @brief Controller class for managing bulk container stacks
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

#ifndef __bulkccController_h__
#define __bulkccController_h__

#include "./bulkccObjTemplate.h" // BULKCC::ObjTemplate
#include "./bulkccStack.h" // BULKCC::Stack

namespace BULKCC {

#define _VERSION_BULKCC_Controller_ 1.0
// #define _DEBUG_BULKCC_Controller_

/**
 * @class Controller
 * @brief Main controller class for managing bulk container stacks
 *
 * The Controller class provides the primary interface for managing collections
 * of heterogeneous objects in a linked-list stack structure. It supports adding,
 * searching, fetching, and listing objects of various types.
 *
 * @section overview Overview
 *
 * The Controller acts as the main interface for the BULKCC library. It provides
 * template-based operations that allow you to work with any data type while
 * maintaining type safety through the stack mechanism.
 *
 * @section new_api New API (Recommended)
 *
 * The new Stack class provides better performance and thread safety:
 * - push<T>(data) - Add object to stack
 * - pop<T>() - Remove and return object
 * - peek<T>() - View top object
 * - count<T>() - O(1) count (uses internal size tracker)
 * - findAll<T>() - Get all objects of type
 * - empty() - Check if empty
 * - size() - O(1) size
 *
 * @section operations Supported Operations
 *
 * - add(): Add new objects to the stack (DEPRECATED - use push)
 * - search(): Find objects of a specific type (DEPRECATED - use count)
 * - fetch(): Retrieve and remove objects from the stack (DEPRECATED - use pop)
 * - list(): Get all objects of a specific type as an array (DEPRECATED - use findAll)
 * - clean(): Remove all stored objects (not the stack nodes)
 * - erase(): Remove the entire stack including nodes
 *
 * @section example Example Usage
 *
 * @code
 * // NEW API (recommended)
 * BULKCC::Stack stack;
 * stack.push<MyClass*>(new MyClass());
 * stack.push<MyClass*>(new MyClass());
 *
 * size_t count = stack.count<MyClass*>(); // O(1)!
 * MyClass* obj = stack.pop<MyClass*>();
 *
 * // Old API (deprecated)
 * BULKCC::Controller controller;
 * MyClass* obj1 = new MyClass();
 * BULKCC::Obj* stack = controller.add<MyClass*>(obj1);
 *
 * // Add more objects to the stack
 * controller.add<MyClass*>(new MyClass(), stack);
 * controller.add<MyClass*>(new MyClass(), stack);
 *
 * // Search for objects of a specific type
 * int count = controller.search<MyClass*>(stack);
 *
 * // Fetch an object (removes it from stack)
 * MyClass* fetched = controller.fetch<MyClass*>(stack);
 *
 * // Clean up
 * controller.erase(stack); // Delete entire stack
 * @endcode
 *
 * @note The Controller does not take ownership of raw pointers unless explicitly
 *       told to clean or erase. You must manage memory for your objects.
 *
 * @warning Always call erase() or clean() before destroying the Controller to
 *          prevent memory leaks.
 *
 * @see Obj
 * @see ObjTemplate
 * @see Stack
 * @see StackGuard
 * @see Iterator
 */
class Controller {
  public:

    /**
     * @brief Default constructor
     *
     * Initializes a new Controller instance for managing bulk container stacks.
     *
     * @post A new Controller is ready to manage objects
     */
    Controller( void );

    /**
     * @brief Destructor
     *
     * Cleans up the Controller. Note: Does NOT automatically clean or erase
     * any stacks or objects. You must call erase() or clean() on any active
     * stacks before destroying the Controller.
     *
     * @warning Always ensure proper memory management by cleaning up stacks
     */
    virtual ~Controller( void );

    /**
     * @brief Erase all stack nodes
     *
     * Deletes all stack nodes in the linked list, including the internal
     * storage for each node. This completely removes the stack structure.
     *
     * @param obj Pointer to the head of the stack (Obj*)
     *
     * @post The stack and all its nodes are deleted
     * @post The obj pointer is now invalid (dangling)
     *
     * @note This does NOT delete the objects stored in the stack. Use clean()
     *       first if you want to delete the stored objects as well.
     *
     * @code
     * controller.clean(stack);  // Delete stored objects first
     * controller.erase(stack);  // Then delete stack nodes
     * @endcode
     */
    void erase( Obj* obj );

    /**
     * @brief Clean all stored objects from the stack
     *
     * Deletes all objects stored in the stack nodes but keeps the stack
     * structure intact. After cleaning, the stack nodes remain but contain
     * no objects.
     *
     * @param obj Pointer to the head of the stack (Obj*)
     *
     * @post All stored objects are deleted
     * @post Stack nodes still exist but are empty
     *
     * @note This only deletes the stored objects, not the stack nodes.
     *       Use erase() to remove the stack structure itself.
     *
     * @code
     * controller.clean(stack);  // Delete stored objects
     * controller.erase(stack);  // Delete stack nodes
     * @endcode
     */
    void clean( Obj* obj );

    /**
     * @brief Add first object to create a new stack
     *
     * Creates a new stack by adding the first object. This is used to start
     * a new stack with a single element.
     *
     * @tparam T The type of object to store
     * @param object The object to store in the stack
     *
     * @return Pointer to the new stack (Obj*)
     *
     * @post A new stack is created with one node containing the object
     *
     * @code
     * BULKCC::Controller controller;
     * MyClass* obj = new MyClass();
     * BULKCC::Obj* stack = controller.add<MyClass*>(obj);
     * @endcode
     *
     * @see add(T object, Obj*& obj)
     */
    template< class T > Obj* add( T object );

    /**
     * @brief Add another object to an existing stack
     *
     * Adds a new object to the beginning of an existing stack, pushing
     * the existing nodes down.
     *
     * @tparam T The type of object to store
     * @param object The object to add to the stack
     * @param obj Reference to the stack head pointer
     *
     * @post The new object is added at the top of the stack
     *
     * @code
     * BULKCC::Controller controller;
     * MyClass* obj1 = new MyClass();
     * BULKCC::Obj* stack = controller.add<MyClass*>(obj1);
     * controller.add<MyClass*>(new MyClass(), stack);  // Added to top
     * @endcode
     *
     * @see add(T object)
     */
    template< class T > void add( T object, Obj*& obj );

    /**
     * @brief Identify if a stack node contains a specific type
     *
     * Uses dynamic casting to check if the stack node contains an object
     * of the specified type T.
     *
     * @tparam T The type to check for
     * @param obj Pointer to the stack node to check
     *
     * @return true if the node contains type T, false otherwise
     */
    template< class T > bool identify( Obj* obj );

    /**
     * @brief Search for objects of a specific type
     *
     * Traverses the stack and counts all objects of type T that are
     * currently stored (not NULL).
     *
     * @tparam T The type of object to search for
     * @param obj Reference to the stack head pointer
     *
     * @return Number of objects of type T found in the stack
     *
     * @code
     * int count = controller.search<MyClass*>(stack);
     * std::cout << "Found " << count << " objects" << std::endl;
     * @endcode
     */
    template< class T > int search( Obj*& obj );

    /**
     * @brief Fetch and remove first object of a specific type
     *
     * Searches the stack for the first object of type T, retrieves it,
     * and removes it from the stack. The object is returned and no longer
     * managed by the stack.
     *
     * @tparam T The type of object to fetch
     * @param obj Reference to the stack head pointer
     *
     * @return The fetched object of type T, or 0 if not found
     *
     * @post The first matching object is removed from the stack
     *
     * @code
     * MyClass* fetched = controller.fetch<MyClass*>(stack);
     * if (fetched) {
     *     // Use fetched object
     *     delete fetched;
     * }
     * @endcode
     */
    template< class T > T fetch( Obj*& obj );

    /**
     * @brief Get all objects of a specific type as an array
     *
     * Searches the stack for all objects of type T and returns them
     * as a newly allocated array. Each matching object is removed from
     * the stack during retrieval.
     *
     * @tparam T The type of objects to list
     * @param obj Reference to the stack head pointer
     *
     * @return Array of objects of type T (must be deleted by caller)
     * @return 0 if no objects found
     *
     * @post All matching objects are removed from the stack
     *
     * @code
     * int count = controller.search<MyClass*>(stack);
     * MyClass** list = controller.list<MyClass*>(stack);
     * for (int i = 0; i < count; i++) {
     *     delete list[i];
     * }
     * delete[] list;
     * @endcode
     */
    template< class T > T* list( Obj*& obj );

  private:

    /**
     * @brief Internal method to create stack nodes
     *
     * Factory method to create the appropriate type of stack node
     * based on the requested object type.
     *
     * @tparam T The type of object the node will store
     * @param objType The type of node to create
     *
     * @return Pointer to newly created stack node
     *
     * @throws Exception if unknown object type is requested
     */
    template< class T > Obj* create( TYPE::ObjType objType );

    Stack _stack;

};
// class Controller

// /// //// PUBLIC //// /// //
template< class T > Obj* // add first object
Controller::add( T object ) {
  Obj* nextObj = create< T >( TYPE::Template );
  ObjTemplate< T >* nextObjTemplateObj = (ObjTemplate< T >*)nextObj;
  nextObjTemplateObj->add( object );
  return nextObjTemplateObj->getAsBaseObj( );
} // add

template< class T > void // add following objects
Controller::add( T object, Obj*& obj ) {
  Obj* newObj = add< T >( object );
  newObj->setNextObj( obj );
  obj = newObj;
} // add

template< class T > bool // create a Obj object
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
  } // if
  return result;
} // create<T>

template< class T > int // search object of data type T
Controller::search( Obj*& obj ) {
  int noOfFound = 0;
  Obj* lastObj = obj;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false; // break down search
    else {
      bool found = identify< T >( lastObj );
      if( found ) {
        bool isSet = lastObj->checkObj( );
        if( isSet )
          noOfFound++;
      } // if
      lastObj = lastObj->getNextObj( );
    } // if
  } // while
  return noOfFound;
} // search<T>

template< class T > T Controller::fetch( Obj*& obj ) { /// fetch an object
  T object = 0;
  Obj* lastObj = obj;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false; // break down search
    else {
      bool found = identify< T >( lastObj );
      if( found ) {
        ObjTemplate< T >* objTemplate = (ObjTemplate< T >*)( lastObj );
        object = objTemplate->fetch( );
        if( object != 0 )
          search = false; // break down search
      } // if
      lastObj = lastObj->getNextObj( );
    } // if
  } // while
  return object;
} // fetch

template< class T > T* // get list of objects
Controller::list( Obj*& obj ) {
  int noOfObjs = search< T >( obj );
  T* objectList = new T[ noOfObjs ];
  T object = 0;
  Obj* lastObj = obj;
  int positionInList = 0;
  bool search = true;
  while( search ) {
    if( lastObj == 0 )
      search = false; // break down search
    else {
      bool found = identify< T >( lastObj );
      if( found ) {
        ObjTemplate< T >* objTemplate = (ObjTemplate< T >*)( lastObj );
        object = objTemplate->fetch( );
        objectList[ positionInList++ ] = object;
      } // if
      lastObj = lastObj->getNextObj( );
    } // if
  } // while
  return objectList;
} // list
// /// //// PUBLIC //// /// //

// /// //// PRIVATE //// /// //
template< class T > Obj* // create a Obj object
Controller::create( TYPE::ObjType objType ) {
  Obj* obj;
  switch( objType ) {
    case TYPE::Template:
      obj = new ObjTemplate< T >( ); // head object
      break;
    default:
      throw Exception(
        "Controller::create - unknown type of Obj object requested" );
      break;
  }; // switch
  return obj;
} // create<T>
// /// //// PRIVATE //// /// //

} // namespace BULKCC

#endif // __bulkccController_h__
