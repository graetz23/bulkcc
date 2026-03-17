/**
 * @file bulkccObj.h
 * @brief Base class for stack nodes in the bulk container
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

#ifndef __bulkccObj_h__
#define __bulkccObj_h__

#include "./bulkccException.h" // BULKCC::Exception
#include "./bulkccTypeObjTypes.h" // BULKCC::TYPE::ObjTypes

namespace BULKCC {

#define _VERSION_BULKCC_Obj_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Obj_

/**
 * @class Obj
 * @brief Abstract base class for stack nodes
 *
 * The Obj class is the abstract base class for all stack nodes in the
 * BULKCC library. It provides the fundamental linked-list structure
 * for storing objects in a stack.
 *
 * @section design Design
 *
 * Each stack node contains:
 * - A pointer to the next node in the stack (_nextObj)
 * - Virtual methods for type identification and object management
 *
 * This class cannot be instantiated directly. Use ObjTemplate<T> to
 * create concrete stack nodes that can store objects of a specific type.
 *
 * @section usage Usage
 *
 * This class is typically not used directly. Instead, use the Controller
 * class to manage stacks:
 *
 * @code
 * BULKCC::Controller controller;
 * BULKCC::Obj* stack = controller.add<MyType*>(myObject);
 * @endcode
 *
 * @see Controller
 * @see ObjTemplate
 */
class Obj {
public:

  /**
   * @brief Default constructor
   *
   * Initializes the stack node with no next node (null pointer).
   */
  Obj( void );

  /**
   * @brief Virtual destructor
   *
   * Ensures proper cleanup of derived classes.
   */
  virtual ~Obj( void );

  /**
   * @brief Get the object type
   *
   * Returns the type identifier for this stack node.
   *
   * @return TYPE::ObjType The type of this object
   */
  virtual TYPE::ObjType getObjType( void ) = 0;

  /**
   * @brief Get the object type as string
   *
   * Returns a string representation of the object type.
   *
   * @return Str The type as a string
   */
  virtual Str getObjTypeAsString( void ) = 0;

  /**
   * @brief Get this node as base Obj pointer
   *
   * Returns a pointer to this object cast to the base Obj type.
   *
   * @return Obj* Pointer to this as base class
   */
  virtual Obj* getAsBaseObj( void ) = 0;

  /**
   * @brief Check if this node contains an object
   *
   * Determines whether this stack node currently holds a non-null object.
   *
   * @return true if a valid object is stored, false otherwise
   */
  virtual bool checkObj( void ) = 0;

  /**
   * @brief Delete the stored object
   *
   * Deletes the object stored in this node and sets the internal
   * pointer to null. Does not delete the node itself.
   */
  virtual void eraseObj( void ) = 0;

  /**
   * @brief Set the next node in the stack
   *
   * Links this node to another node, creating a chain in the stack.
   *
   * @param obj Reference to the next node pointer
   */
  void setNextObj( Obj*& obj );

  /**
   * @brief Get the next node in the stack
   *
   * Returns a pointer to the next node in the stack.
   *
   * @return Obj* Pointer to next node, or 0 if none
   */
  Obj* getNextObj( void );

private:

  Obj* _nextObj; /// Pointer to next node in the stack

}; // class Obj

} // namespace BULKCC

#endif // __bulkccObj_h__
