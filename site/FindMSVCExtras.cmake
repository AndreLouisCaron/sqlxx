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

# List CMake variables containing build flags.
set(CMAKE_COMPILER_FLAGS_VARIABLES
  CMAKE_C_FLAGS_DEBUG
  CMAKE_C_FLAGS_MINSIZEREL
  CMAKE_C_FLAGS_RELEASE
  CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_DEBUG
  CMAKE_CXX_FLAGS_MINSIZEREL
  CMAKE_CXX_FLAGS_RELEASE
  CMAKE_CXX_FLAGS_RELWITHDEBINFO
)

# Select static or dynamic MSVC runtime based on 'MSVC_RUNTIME' variable.
# This variable can be set through the command-line like so:
#
#   cmake -G "..." -DMSVC_RUNTIME=static
#
# Acceptable values are "static" (default) and "dynamic".
macro(msvc_configure_runtime)
  if(MSVC)
    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()
    # Set compiler options.
    if(${MSVC_RUNTIME} STREQUAL "static")
      message(STATUS
        "MSVC -> forcing use of statically-linked runtime."
      )
      foreach(variable ${CMAKE_COMPILER_FLAGS_VARIABLES})
        if(${variable} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
      endforeach()
    else()
      message(STATUS
        "MSVC -> forcing use of dynamically-linked runtime."
      )
      foreach(variable ${CMAKE_COMPILER_FLAGS_VARIABLES})
        if(${variable} MATCHES "/MT")
          string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        endif()
      endforeach()
    endif()
  endif()
endmacro()

# Enable Microsoft's structured exception handling.
macro(msvc_enable_se_handling)
  if(MSVC)
    message(STATUS
      "MSVC -> enabling structured exception hanlding."
    )
    if(CMAKE_CXX_FLAGS MATCHES "/EH")
      string(REGEX REPLACE
        "/EH[acs]+" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}"
      )
    else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
    endif()
  endif()
endmacro()

# Compile message file to resource file.
macro(compile_message_file resource messages)
  # compute the resource file name.
  get_filename_component(
    ${resource} ${messages} NAME_WE
  )
  set(${resource} "${CMAKE_CURRENT_BINARY_DIR}/${${resource}}.rc")
  # compile the message file.
  add_custom_command(
    OUTPUT
      ${${resource}}
    COMMAND
      mc ${messages}
    MAIN_DEPENDENCY
      ${messages}
    DEPENDS
      ${messages}
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT
      "Compiling message file '${messages}'."
    VERBATIM
  )
  set_source_files_properties(${${resource}} PROPERTIES GENERATED True)
endmacro()

# Compile resource-only DLL.
function(add_resource_only_library target sources)
  add_library(${target} SHARED ${sources})
  if(MSVC)
    # Make sure the DLL links with nothing and doesn't have an entry point.
    set_target_properties(${target}
      PROPERTIES LINK_FLAGS "/MANIFEST:NO /NODEFAULTLIB /NOENTRY"
    )
    # CMake can't guess what language this is since only resources
    # are being compiled.  Tell it it's C++ so it gets off our back.
    set_target_properties(${target}
      PROPERTIES LINKER_LANGUAGE "CXX"
    )
  endif()
endfunction()
