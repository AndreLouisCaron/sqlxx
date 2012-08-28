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

set(headers
  Connection.hpp
  Date.hpp
  Diagnostic.hpp
  Driver.hpp
  Environment.hpp
  execute.hpp
  Guid.hpp
  Handle.hpp
  NotCopyable.hpp
  Numeric.hpp
  PreparedStatement.hpp
  Results.hpp
  Row.hpp
  Statement.hpp
  Status.hpp
  Time.hpp
  Timestamp.hpp
  Transaction.hpp
  Version.hpp
  firebird.hpp
  mysql.hpp
  sql.hpp
  sqlite.hpp
  string.hpp
  types.hpp
)
set(sources
  Connection.cpp
  Date.cpp
  Diagnostic.cpp
  Driver.cpp
  Environment.cpp
  execute.cpp
  Guid.cpp
  Handle.cpp
  PreparedStatement.cpp
  Results.cpp
  Row.cpp
  Statement.cpp
  Status.cpp
  Time.cpp
  Timestamp.cpp
  Transaction.cpp
  Version.cpp
  firebird.cpp
  mysql.cpp
  sqlite.cpp
)
add_library(sql
  STATIC
  ${sources}
  ${headers}
)
