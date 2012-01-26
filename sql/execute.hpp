#ifndef _sql_execute_hpp__
#define _sql_execute_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "string.hpp"

namespace sql {

    class Connection;

    void execute ( Connection& connection, const string& update );

}

#endif /* _sql_execute_hpp__ */
