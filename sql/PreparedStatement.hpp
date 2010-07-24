#ifndef _sql_PreparedStatement_hpp__
#define _sql_PreparedStatement_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/string.hpp>
#include <sql/Statement.hpp>

namespace sql {

        /*!
         * @brief Pre-compiled statement in which parameters are substituted at
         *    execution time.
         *
         * Prepared statements are more convenient, more secure and also usually
         * much faster than there manual counterparts. The framework handles all
         * parameter formatting which avoids you the trouble of escaping quotes,
         * for instance; this also has the benefit of increasing security when
         * parameters are fetched from fields in a form, etc. A nice bonus is
         * that the statements are probably pre-parsed by the driver and are
         * therefore more efficient.
         */
    class PreparedStatement :
        public Statement
    {
        /* data. */
    private:
        string myQuery;

        /* construction. */
    public:
            /*!
             * @brief Creates a statement for use over a given connection.
             *
             * @param connection Connection to use the statement with.
             * @param query Query to pre-parse. Format for queries is defined by
             *    ODBC, you can easily find this somewhere on the internet.
             */
        PreparedStatement ( Connection& connection, const string& query );

        /* overrides. */
    public:
        virtual void execute ();
    };

}

#endif /* _sql_PreparedStatement_hpp__ */
