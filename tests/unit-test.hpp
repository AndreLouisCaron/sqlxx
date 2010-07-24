#ifndef _sql_tests_unittest_hpp__
#define _sql_tests_unittest_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql.hpp>
#include <iostream>

namespace {

    class TestFailed {};

    void fail () {
        throw (TestFailed());
    }

    void assert ( bool satisfied )
    {
        if ( !satisfied ) {
            fail();
        }
    }

        /*!
         * @brief Function to implement when writing a unit test.
         *
         * This function will be called with an open connection to a database.
         */
    void run ( sql::Connection& connection );

}

#endif /* _sql_tests_unittest_hpp__ */
