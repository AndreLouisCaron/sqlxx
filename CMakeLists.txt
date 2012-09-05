# Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#
# SQL (ODBC) wrappers for C++.
#

cmake_minimum_required(VERSION 2.6)

project(sqlxx)

# Resolve custom CMake packages.
set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/site
)

# Set compiler options.
find_package(MSVCExtras)
msvc_configure_runtime()
msvc_enable_se_handling()

if(MSVC)
  add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SCL_SECURE_NO_WARNINGS
  )
endif()

# Put all libraries and executables in the build folder root.
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(code)

# Optional targets (skip when building as a dependency).
if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})

  # Build API documentation.
  find_package(Doxygen QUIET)
  find_package(DoxygenExtras)
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_PUBLIC_RELEASE YES)
    set(CMAKE_INTERNAL_BUILD NO)
  else()
    set(CMAKE_PUBLIC_RELEASE NO)
    set(CMAKE_INTERNAL_BUILD YES)
  endif()
  configure_file(
    ${CMAKE_SOURCE_DIR}/help/Doxyfile
    ${CMAKE_BINARY_DIR}/Doxyfile @ONLY
  )
  add_api_documentation(help)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/code)
  #add_subdirectory(demo)

  # Build tools.
  add_subdirectory(tool)

  # Build test suite.
  enable_testing()
  add_subdirectory(test)

endif()
