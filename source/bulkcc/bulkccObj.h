/** 
 * @file bulkccObj.h
 * @brief Abstract base class for stack objects
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
 * @class BULKCC::Obj
 * @brief Abstract base class for all stack objects.
 *
 * This class defines the interface that all stack objects must implement.
 * It provides the basic operations for a linked list of objects including
 * type identification, object checking, and memory management.
 *
 * @note This is an abstract class - you cannot instantiate it directly.
 *       Use ObjTemplate<T> for concrete implementations.
 *
 * @{
 */

#ifndef __bulkccObj_h__
#define __bulkccObj_h__

#include "./bulkccException.h" // BULKCC::Exception
#include "./bulkccTypeObjTypes.h" // BULKCC::TYPE::ObjTypes

namespace BULKCC {

#define _VERSION_BULKCC_Obj_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Obj_

/**
 * @brief Abstract base class for stack objects
 *
 * This class serves as the base for all objects stored in the bulk stack.
 * It provides virtual methods for type identification, object validation,
 * and memory management through a linked list structure.
 */
class Obj {
public:

  /** @brief Default constructor */
  Obj( void );

  /** @brief Virtual destructor */
  virtual ~Obj( void );

  /**
   * @brief Returns the type of this object
   * @return The object type as defined in TYPE::ObjType
   */
  virtual TYPE::ObjType getObjType( void ) = 0;

  /**
   * @brief Returns the type of this object as a string
   * @return String representation of the object type
   */
  virtual Str getObjTypeAsString( void ) = 0;

  /**
   * @brief Gets this object as a base Obj pointer
   * @return Pointer to this object cast as Obj*
   */
  virtual Obj* getAsBaseObj( void ) = 0;

  /**
   * @brief Checks if the contained object is valid
   * @return true if the object is not NULL, false otherwise
   */
  virtual bool checkObj( void ) = 0;

  /**
   * @brief Deletes the contained object
   *
   * Releases memory used by the contained object.
   * After calling this method, checkObj() will return false.
   */
  virtual void eraseObj( void ) = 0;

  /**
   * @brief Sets the next object in the stack
   * @param obj Pointer to the next Obj object
   */
  void setNextObj( Obj*& obj );

  /**
   * @brief Gets the next object in the stack
   * @return Pointer to the next Obj object, or 0 if none
   */
  Obj* getNextObj( void );

private:

  /** @brief Pointer to the next object in the stack */
  Obj* _nextObj;

}; // class Obj

} // namespace BULKCC

/** @} */

#endif // __bulkccObj_h__
