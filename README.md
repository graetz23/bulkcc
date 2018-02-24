## BULKCC is a C++ bulk stack implementation ##

[![Build Status](https://travis-ci.org/cscheiblich/bulkcc.svg?branch=master)](https://travis-ci.org/cscheiblich/bulkcc) on travis-ci.com

BULKCC is an object-oriented C++ template based list for storing any data /
object types in one single list. It is ideal directly after some parsing method,
while the parser generates data / objects of known type but in unknown sequence.
Therefore, the data / objects can be pushed in their sequence to a single BULKCC
list, that allows for searching by data / types or reading the sequence again.

The implementation separates the template based methods from tha data / object
list. The data / object list consists of a native base class where a template
class forms the sub class for. However, a controller class implements the auto-
matic template functionality for storing data / objects to the sub class and
queueing up the base class by an infinite pointered list. Have fun. ~8>

### License ###

**BULKCC is distributed under the MIT License (MIT); this file is part of.**

**Copyright (c) 2008-2018 Christian Scheiblich (cscheiblich@gmail.com)**

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

### Version ###

**BULKCC Version 0.16 20160106**

### Change Log ###

201XXXXX version 0.1X :
- updated readme file

20160106 version 0.16 :
- cleaned code due to old MSVS stuff ..
- updated the years of the Copyright by 2008-2018

20141231 version 0.15 :
- changed to the MIT License (MIT)
- pushed to https://github.com/cscheiblich/blukcc for development

20120430 version 0.14 :
- changed copyright towards 2012 and removed old email address
- reconfigured visual studio project due to executing file for debug
- TODO: deleting seems to run to infinty; fix this!

20100807 version 0.13 :
- added common header file for including STL lib and set common typedefs

20100805 version 0.12 :
- tested for Microsoft Windows 7 using MS Visual Studio 2005
- tested for GNU/Linux debian 5.0 kernel 2.6.26-2-686 using GNU/g++/gcc 4.3.2 
- added readMe.txt
- added Makefile

20100805 version 0.11 :
- renamed all files
- renamed all classes
- added defines

20100805 version 0.10 :
- renamed to Catalogs:: to BULKCC::
- released BULKCC:: under Apache License, Version 2.0
- created Microsoft Visual Studio 2005 Project
- added version and dates
- added package name as Kiera Gothe

20080118 version 0.01 :
- implemented complete project as Catalogs:: and tested it

/******************************************************************************/
