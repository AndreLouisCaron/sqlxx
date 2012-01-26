// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // Include this so that we only get a link error if not compiled properly.
#include "unit-test.hpp"

// Include this at the end of a source file implementing a unit test.
//
// This file is not meant to compile as a standalone application. It will not
// compile and link as an executable program unless "#include"d from inside a
// unit test source file which defines all symbols prototyped in
// "unit-test.hpp".

#include "firebird.hpp"
#include "mysql.hpp"
#include "sqlite.hpp"
#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>
#include <utility>

namespace {

    int firebird ( int argc, char ** argv )
    {
        if ( argc != 3 )
        {
            std::cerr
                << "firebird: Expecting database path, user name and password."
                << std::endl;
            return (EXIT_FAILURE);
        }

            // Allocate the environment.
        sql::Environment environment;

            // Group information required for the connection.
        sql::string path(argv[0]);
        sql::string user(argv[1]);
        sql::string password(argv[2]);

            // Connect to the database.
        sql::firebird::Connection connection
            (environment, path, user, password);

            // Run the unit test.
        run(connection);

        return (EXIT_SUCCESS);
    }

    int sqlite ( int argc, char ** argv )
    {
        if ( argc != 1 )
        {
            std::cerr
                << "sqlite: Expecting database path."
                << std::endl;
            return (EXIT_FAILURE);
        }

            // Allocate the environment.
        sql::Environment environment;

            // Group information required for the connection.
        sql::string path(argv[0]);

            // Connect to the database.
        sql::sqlite::Connection connection(environment, path);

            // Run the unit test.
        run(connection);

        return (EXIT_SUCCESS);
    }

    int mysql ( int argc, char ** argv )
    {
        if ( argc != 3 )
        {
            std::cerr
                << "mysql: Expecting database name, user name and password."
                << std::endl;
            return (EXIT_FAILURE);
        }

            // Allocate the environment.
        sql::Environment environment;

            // Group information required for the connection.
        sql::string database(argv[0]);
        sql::string user(argv[1]);
        sql::string password(argv[2]);

            // Connect to the database.
        sql::mysql::Connection connection
            (environment, database, user, password);

            // Run the unit test.
        run(connection);

        return (EXIT_SUCCESS);
    }

    typedef std::pair< const char*, int(*)(int,char**) > Provider;
    const Provider providers[] = {
        Provider("firebird",&firebird),
        Provider("sqlite",&sqlite),
        Provider("mysql",&mysql),
    };

    const std::size_t providercount = sizeof(providers)/sizeof(Provider);

    class ProviderNameIs {
        const char * myReference;
    public:
        explicit ProviderNameIs ( const char * reference )
            : myReference(reference)
        {}
        bool operator() ( const Provider& candidate ) const {
            return (std::strcmp(candidate.first,myReference) == 0);
        }
    };

}

int main ( int argc, char ** argv )
{
    try
    {
        if ( argc < 2 )
        {
            std::cerr
                << "Expecting argument(s), use '--help' option for usage."
                << std::endl;
            return (EXIT_FAILURE);
        }

            // Dispatch based on connection method.
        if ( std::strcmp(argv[1],"--provider") == 0 )
        {
            if ( argc < 3 ) {
                std::cerr << "Expecting provider name." << std::endl;
                return (EXIT_FAILURE);
            }

                // Find the requested provider.
            const Provider * provider = std::find_if(
                providers, providers+providercount, ::ProviderNameIs(argv[2])
                );
            if ( provider == (providers+providercount) )
            {
                std::cerr
                    << "No such provider: '" << argv[2] << "'." << std::endl;
                return (EXIT_FAILURE);
            }

                // Use the requested provider.
            (*provider->second)(argc-3,argv+3);
        }
        else {
            std::cerr
                << "Invalid argument: '" << argv[1] << "'." << std::endl;
            return (EXIT_FAILURE);
         }
    }
    catch ( const sql::Diagnostic& diagnostic ) {
        std::cerr << diagnostic << std::endl;
        return (EXIT_FAILURE);
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

    return (EXIT_SUCCESS);
}
