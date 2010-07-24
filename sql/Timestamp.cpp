// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Timestamp.hpp>
#include <iomanip>
#include <ostream>

namespace sql {

    std::ostream& operator<< ( std::ostream& out, const Timestamp& value )
    {
        out << value.date() << " " << value.time() << "."
            << std::setfill('0') << std::setw(4) << value.fraction();
        return (out);
    }

}
