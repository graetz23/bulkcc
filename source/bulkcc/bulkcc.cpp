/** 
 * @file bulkcc.cpp
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

#include "./bulkcc.h" // header

namespace BULKCC {

void // test function
testBULKCC( void ) {

  try {

    // The controller keeps the the templated based functions for the data
    // object template list. The template list does implement any functionality
    // and has a native base class, while only the first sub class implements
    // a template class.
    //
    Controller controller; // use template methods for bulk stack template

    // some complex objects for testing Obj objects
    //
    std::string* string1 = new std::string( "first" );
    std::string* string2 = new std::string( "second" );
    std::string* string3 = new std::string( "third" );
    std::exception* exception1 = new std::exception( );
    std::exception* exception2 = new std::exception( );
    std::exception* exception3 = new std::exception( );

    Obj* obj = controller.add<std::exception*>( exception1 );
    controller.add<std::string*>( string1, obj );
    controller.add<std::string*>( string2, obj );
    controller.add<std::exception*>( exception2, obj );
    controller.add<std::string*>( string3, obj );
    controller.add<std::exception*>( exception3, obj );

    int found = -1;
    found = controller.search<std::exception*>( obj );
    std::cout << "std::exception* -> found: " << found << std::endl
              << std::flush;

    found = -1;
    found = controller.search<std::string*>( obj );
    std::cout << "std::string* -> found: " << found << std::endl << std::flush;

    std::exception* fetchedException = controller.fetch<std::exception*>( obj );
    delete fetchedException;
    fetchedException = controller.fetch<std::exception*>( obj );
    delete fetchedException;
    fetchedException = controller.fetch<std::exception*>( obj );
    delete fetchedException;

    // delete fetched;
    //
    std::string* fetchedString = controller.fetch<std::string*>( obj );
    delete fetchedString;
    fetchedString = controller.fetch<std::string*>( obj );
    delete fetchedString;
    fetchedString = controller.fetch<std::string*>( obj );
    delete fetchedString;

    // some tries even if there are no objects left, no errors, no exceptions
    //
    fetchedException = controller.fetch<std::exception*>( obj );
    delete fetchedException;
    fetchedString = controller.fetch<std::string*>( obj );
    delete fetchedString;

    found = -1;
    found = controller.search<std::exception*>( obj );
    std::cout << "std::exception* -> found: " << found << std::endl
              << std::flush;

    found = -1;
    found = controller.search<std::string*>( obj );
    std::cout << "std::string* -> found: " << found << std::endl << std::flush;

    // delete the pointer list
    //
    controller.erase( obj );


    // automatic test
    //
    int end = 500000; // will be one million and one
    std::string* str1 = new std::string( );
    Obj* cObj = controller.add<std::string*>( str1 );
   
    // create list
    //
    std::cout << std::endl << std::flush;
    std::cout << "long long list with: " << (end*2)+1 << " elements"
              << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    for( int i = 0; i < end; i++ ) {

      std::string* str = new std::string( );

      std::exception* exc = new std::exception( );

      controller.add<std::string*>( str, cObj );

      controller.add<std::exception*>( exc, cObj );

    } // i till end
    
    std::cout << std::endl << std::flush;
    
    // convert half of complex objects to pointer list of complex objects
    //
    std::cout << std::endl << std::flush;
    std::cout << "convert added objects of std::string* to list std::string**"
              << std::endl << std::flush;

    int noOfStringObjs = controller.search<std::string*>( cObj ); // kill all added objects
    std::string** stringObjList = controller.list<std::string*>( cObj ); // kill all added objects

    std::cout << std::endl << std::flush;

    // delete the pointer list in well-known style
    //
    std::cout << std::endl << std::flush;
    std::cout << "delete converted objects of std::string* in list std::string**" << std::endl << std::flush;
    
    for( int i = 0; i < noOfStringObjs; i++ ) {
      std::string* stringObjFromList = stringObjList[ i ];
      delete stringObjFromList;
    } // i
    delete [ ] stringObjList;

    std::cout << std::endl << std::flush;

    // delete the rest of the added objects, other half
    //
    std::cout << std::endl << std::flush;
    std::cout << "deleting added objects" << std::endl << std::flush;
    
    controller.clean( cObj ); /// kill all added objects

    std::cout << std::endl << std::flush;

    // delete the bulkccObj* objects themselves
    //
    std::cout << "deleting list" << std::endl << std::flush;
    controller.erase( cObj );

    std::cout << std::endl << std::flush;
    std::cout << "done" << std::endl << std::flush;

  } catch( Exception& exception ) {
    std::cout << std::endl << std::flush;
    std::cout << exception.what( ) << std::endl << std::flush;
  } catch( std::exception& exception ) {
    std::cout << std::endl << std::flush;
    std::cout << "std::exception caught: " << exception.what( ) << std::flush;
  } catch( ... ) {
    std::cout << std::endl << std::flush;
    std::cout << "strange exception caught" << std::endl << std::flush;
  } // try

}; // testObj

} // namespace BULKCC
