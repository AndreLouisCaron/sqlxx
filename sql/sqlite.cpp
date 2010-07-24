// Copyright (c) 2009, Andre Caron
//
// This package is free software; you can redistribute it and/or modify it
// under the terms of a Berkely Software Distribution (BSD) license.
//
// This package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the accompanying "license.txt" file
// for more details.
//

/*!
 * @file sqlite.cpp
 * @author Andre Caron
 */

#include <sql/sqlite.hpp>

namespace sql { namespace sqlite {

    std::ostream& ConnectionString::put ( std::ostream& out ) const
    {
        std::ostream::sentry ok(out);
        if ( ok )
        {
            out << "Driver={SQLite ODBC Driver};"
                << "Database=" << database() << ';';
        }
        return (out);
    }

} }
