// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
