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

    // Include this so that we only get a link error if not compiled properly.
#include "tool-program.hpp"

// Include this at the end of a source file implementing an sqlxx-based tool.
//
// This file is not meant to compile as a standalone application. It will not
// compile and link as an executable program unless "#include"d from inside a
// unit test source file which defines all symbols prototyped in
// "tool-program.hpp".

#include "firebird.hpp"
#include "mysql.hpp"
#include "sqlite.hpp"
#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>
#include <utility>

namespace {

    int firebird (int argc, char ** argv)
    {
        if (argc < 3) {
            std::cerr
                << "firebird: expecting filepath, username and password."
                << std::endl;
            return (EXIT_FAILURE);
        }

        // Connect to the database.
        sql::Environment environment;
        sql::firebird::Connection connection
            (environment, argv[0], argv[1], argv[2]);

        return (run(connection, argc-3, argv+3));
    }

    int sqlite (int argc, char ** argv)
    {
        if (argc < 1) {
            std::cerr
                << "sqlite: expecting filepath."
                << std::endl;
            return (EXIT_FAILURE);
        }

        // Connect to the database.
        sql::Environment environment;
        sql::sqlite::Connection connection(environment, argv[0]);

        return (run(connection, argc-1, argv+1));
    }

    int mysql (int argc, char ** argv)
    {
        if (argc < 3) {
            std::cerr
                << "mysql: expecting database, username and password."
                << std::endl;
            return (EXIT_FAILURE);
        }

        // Connect to the database.
        sql::Environment environment;
        sql::mysql::Connection connection
            (environment, argv[0], argv[1], argv[2]);

        return (run(connection, argc-3, argv+3));
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

    std::ostream& usage (std::ostream& stream)
    {
        stream
            << "provider connection-parameters ..."      << std::endl
            << std::endl
            << "  provider:"    << std::endl
            << "    > firebird" << std::endl
            << "    > mysql"    << std::endl
            << "    > sqlite"   << std::endl
            << std::endl
            << "  connection-parameters:"      << std::endl
            << "    > firebird: [filepath username password]" << std::endl
            << "    > mysql:    [database username password]" << std::endl
            << "    > sqlite    [filepath]"                   << std::endl;
        return (stream);
    }

}

int main ( int argc, char ** argv )
try
{
    // Make sure we have something to handle.
    if (argc < 2)
    {
        std::cerr
            << "Expecting argument(s), use '--help' option for usage."
            << std::endl;
        return (EXIT_FAILURE);
    }

    // Provide help if requested.
    if (std::strcmp(argv[1],"--help") == 0)
    {
        std::cerr
            << "Usage: " << argv[0] << " " << usage
            << std::endl;
        return (EXIT_FAILURE);
    }

    // Find the requested provider.
    const Provider * provider = std::find_if(
        providers, providers+providercount, ::ProviderNameIs(argv[1])
        );
    if (provider == (providers+providercount))
    {
        std::cerr
            << "No such provider: '" << argv[1] << "'." << std::endl;
        return (EXIT_FAILURE);
    }

    // Use the requested provider.
    return ((*provider->second)(argc-2, argv+2));
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
