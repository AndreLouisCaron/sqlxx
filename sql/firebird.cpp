// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/firebird.hpp>

namespace sql { namespace firebird {

    std::ostream& ConnectionString::put ( std::ostream& out ) const
    {
        std::ostream::sentry ok(out);
        if ( ok )
        {
            out << "DRIVER={Firebird/Interbase(r) Driver (*.fdb)};"
                << "DATABASE=" << database() << ';'
                << "USER=" << user() << ';'
                << "PASSWORD=" << password() << ';'
                << "CHARSET=WIN1250;";
        }
        return (out);
    }

} }
