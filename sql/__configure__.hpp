#ifndef _sql_configure_hpp__
#define _sql_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // On Microsoft Windows, <Windows.h> is required to be included *before*
    // standard headers. On other platforms, no headers are prerequesites.
#if (defined(_WIN32))
#   include <Windows.h>
#endif

    // Standard SQL headers.
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#endif /* _sql_configure_hpp__ */
