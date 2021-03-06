// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <sql.hpp>
#include <odbc.hpp>

#include <iostream>

int main (int argc, char ** argv)
try
{
    // Select the data source category.
    sql::odbc::DataSources::Type type = sql::odbc::DataSources::all();
    if ((argc > 1) && std::strcmp(argv[1],"--user")==0) {
        type = sql::odbc::DataSources::user();
    }
    if ((argc > 1) && std::strcmp(argv[1],"--system")==0) {
        type = sql::odbc::DataSources::system();
    }

    // List all known connections in that category.
    sql::Environment environment;
    sql::odbc::DataSources data_sources(environment, type);
    while (data_sources.next()) {
        std::cout
            << data_sources.name() << ": "
            << data_sources.info() << "."
            << std::endl;
    }
}
catch ( const sql::Environment::Failure& ) {
    std::cerr << "Failed to initialize SQL/ODBC environment!" << std::endl;
    return (EXIT_FAILURE);
}
catch ( const std::exception& error ) {
    std::cerr << error.what() << std::endl;
    return (EXIT_FAILURE);
}
catch ( ... ) {
    std::cerr << "Unknown error!" << std::endl;
    return (EXIT_FAILURE);
}
