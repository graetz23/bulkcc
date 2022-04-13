## BULKCC is a C++ bulk stack implementation ##

[![Build Status](https://travis-ci.org/graetz23/bulkcc.svg?branch=master)](https://travis-ci.org/graetz23/bulkcc) on travis-ci.com

BULKCC is an object-oriented C++ template based _stack_ for storing any _type_ of
data. 

Directly after some parsing method, while the parser or a tokenizer generates
_typed_ data or objects in unknown sequence, BULKCC can be used to store those.
Thereby, the typed data / objects are pushed in (unkown) sequence into BULKCC.

BULKCC allows for searching by data / objects by its type or reading the
- yet known - sequence, poping them of the stack, as pushed in; _first in, first out_.

BLUKCC's implementation separates the template based methods for handling the stack
from storing the _typed_ data or object. Therefore the stack consists of a
non-template base class, where a template class derives. However, a controller
class implements the necessary template functionality for handling the stack.
The stack itself is an infinite pointer refrenced list.

Have fun. ~8>

### License ###

**BULKCC is distributed under the MIT License (MIT); this file is part of.**

**Copyright (c) 2008-2020 Christian (graetz23@gmail.com)**

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

2020030 version 0.16 :
- updated contact information

20160106 version 0.16 :
- cleaned code due to old MSVS stuff ..
- updated the years of the Copyright by 2008-2018

20141231 version 0.15 :
- changed to the MIT License (MIT)
- pushed to https://github.com/graetz23/blukcc for development

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
