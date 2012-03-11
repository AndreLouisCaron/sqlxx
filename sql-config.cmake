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

# Library configuration file used by dependent projects
# via find_package() built-in directive in "config" mode.

if(NOT DEFINED sql_FOUND)

  # Locate library headers.
  find_path(sql_include_dirs
    NAMES sql.hpp
    PATHS ${sql_DIR}/code
  )

  # Common name for exported library targets.
  set(sql_libraries
    sql
    CACHE INTERNAL "sql library" FORCE
  )

  # Usual "required" et. al. directive logic.
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    sql DEFAULT_MSG
    sql_include_dirs
    sql_libraries
  )

  # Add targets to dependent project.
  add_subdirectory(
    ${sql_DIR}
    ${CMAKE_BINARY_DIR}/sql
  )
endif()
