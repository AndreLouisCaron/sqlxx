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

#include "../unit-test.hpp"
#include <sstream>

namespace {

    void create ( sql::Connection& connection )
    {
        std::ostringstream update;
        update << "create table entries ( entry " << DataType << " )";
        std::cerr << "Creating table: '" << update.str() << "'." << std::endl;
        sql::execute(connection, update.str());
    }

    void insert ( sql::Connection& connection )
    {
        std::cerr << "Inserting values." << std::endl;
        static const std::size_t count = sizeof(values)/sizeof(values[0]);
        const sql::string update("insert into entries ( entry ) values (?)");
        sql::PreparedStatement statement(connection, update);
        for ( std::size_t i = 0; (i < count); ++i )
        {
            statement << values[i];
            statement.execute();
        }
    }

    void select ( sql::Connection& connection )
    {
        std::cerr << "Querying stuff." << std::endl;
        const sql::string query("select entry from entries");
        sql::PreparedStatement statement(connection, query);
        statement.execute();

        sql::Results results(statement); Value value;
        for ( std::size_t i = 0; (results >> sql::row); ++i ) {
            assert((results >> value) && (value == values[i]));
        }
    }

    void drop ( sql::Connection& connection )
    {
        std::cerr << "Removing traces." << std::endl;
        const sql::string update("drop table entries");
        sql::PreparedStatement statement(connection, update);
        statement.execute();
    }

    void run ( sql::Connection& connection )
    {
        try {
            create(connection);
            insert(connection);
            select(connection);
        }
        catch ( ... ) {
            std::cerr << "Something failed." << std::endl;
            drop(connection);
            throw;
        }
        drop(connection);
        std::cerr << std::endl;
    }

}

#include "../unit-test.cpp"
