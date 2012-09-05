.. Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
.. All rights reserved.
..
.. Redistribution and use in source and binary forms, with or without
.. modification, are permitted provided that the following conditions are
.. met:
..
..  * Redistributions of source code must retain the above copyright
..    notice, this list of conditions and the following disclaimer.
..
..  * Redistributions in binary form must reproduce the above copyright
..    notice, this list of conditions and the following disclaimer in the
..    documentation and/or other materials provided with the distribution.
..
.. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
.. "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
.. LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
.. A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
.. HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
.. SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
.. LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
.. DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
.. THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
.. (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
.. OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

####################################################
  ``sqlxx``: type-safe C++ wrappers for ODBC C API.
####################################################

:author: André Caron (andre.l.caron@gmail.com)

Introduction
============

The ``sqlxx`` project is a C++ software library that wraps the cumbersome ODBC
C API in the hope of providing a high-quality SQL experience in small C++
applications.

The primary goal is to provide a light-weight database interface that supports:

#. prepared statements; and
#. transactions.

The project should be freely available and compile from source using CMake_ and
be usable as a Git_ submodule.

.. _CMake: http://www.cmake.org/
.. _Git: http://git-scm.com/

Project state
-------------

This project should still be considered experimental.  The author uses it in
one small production application but not all features are guaranteed to be
production-ready.

The API documentation will be made available online shortly.


Getting started
===============

Compiling
---------

0. Get the source code.

   ::

      git clone git://github.com/AndreLouisCaron/sqlxx.git
      cd sqlxx

1. Read the licence.

   It's BSD, but you're still required to read and understand the license terms
   before starting to use the code.

2. Generate build scripts.

   ::

      mkdir work
      cd work
      cmake -G "NMake Makefiles" .. -DCMAKE_BUILD_TYPE=Release

   If you prefer to use Visual Studio, generate a solution using one of the
   Visual Studio solution generators built-in to CMake.  Type ``cmake`` on
   the command line for a list of supported Visual Studio versions.

3. Compile the libraries and demo projects.

   ::

      nmake

   If you generated Visual Studio solution instead of the Makefiles, start
   Visual Studio, open the solution and build the project (``Ctrl+Shift+B``
   hotkey).

4. Build the API documentation.

   ::

      nmake help

5. Run the test suite.

   ::

      nmake /a test

Embedding
---------

The ``sqlixx`` library is designed for embedding in other CMake-based (and
Git-based) projects.  When built as a dependency, the test suite, tools and
documentation are not automatically compiled, thus accelerating the build.

0. Prepare your project for Git submodules.

   ::

      cd my-project
      git submodule init

1. Embed ``sqlxx`` as a Git submodule.

   ::

      mkdir libs
      git submodule add git://github.com/AndreLouisCaron/sqlxx.git libs/sqlxx

2. Refer to the ``sqlxx`` library in your root ``CMakeLists.txt``.

   ::

      set(sqlxx_DIR
        ${CMAKE_SOURCE_DIR}/libs/sqlxx
      )
      find_package(sqlxx
        REQUIRED
      )
      include_directories(${sqlxx_include_dirs})

      # Use "sqlxx" target for resolving dependencies and "${sqlxx_libraries}"
      # to link against "sqlxx" and its dependencies (native ODBC C library).

Contributing
------------

If you wish to hack on ``sqlxx``, you may want to build in debug mode and
compile the full API documentation:

::

   git clone git://github.com/AndreLouisCaron/sqlxx.git
   cd sqlxx

   mkdir work
   cd work
   cmake -G "NMake Makefiles" .. -DCMAKE_BUILD_TYPE=Debug

   nmake
   nmake help


Tutorial
========

Coming soon!


License
=======

You are free to use this library in commercial and open source applications
under the terms of a 2-clause BSD license.  Consult the ``license.txt`` file
for details.
