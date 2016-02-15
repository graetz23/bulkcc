/** 
 * @file bulkccController.h
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

#ifndef __bulkccController_h__
#define __bulkccController_h__

#include "./bulkccObjTemplate.h" // BULKCC::ObjTemplate

namespace BULKCC {

#define _VERSION_BULKCC_Controller_ 0.16 // 20141231
// #define _DEBUG_BULKCC_Controller_

class Controller {
  public:

    Controller( void ); /// constructor
    virtual ~Controller( void ); /// destructor

    void erase( Obj* obj ); /// erase all Obj objects
    void clean( Obj* obj ); /// erase all object added in Obj objects

    template< class T > Obj* add( T object ); /// add first object
    template< class T > void add( T object, Obj*& obj ); /// add following objects
    template< class T > bool identify( Obj* obj ); /// create an Obj object
    template< class T > int search( Obj*& obj ); /// search object of data type T
    template< class T > T fetch( Obj*& obj ); /// add an object
    template< class T > T* list( Obj*& obj ); /// get list of objects

  private:

    template< class T > Obj* create( TYPE::ObjType objType ); /// create an Obj object

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
