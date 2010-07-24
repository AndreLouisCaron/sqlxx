#ifndef _sql_DirectStatement_hpp__
#define _sql_DirectStatement_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/string.hpp>
#include <sql/Statement.hpp>
#include <string>

namespace sql {

        /*!
         * @brief Statement with manual formatting of the query.
         */
    class DirectStatement :
        public Statement
    {
        /* data. */
    private:
        string myQuery;

        /* construction. */
    public:
        DirectStatement ( Connection& connection, const string& query );
        DirectStatement ( Connection& connection, const std::string& query );

        /* overrides. */
    public:
        virtual void execute ();
    };

}

#endif /* _sql_DirectStatement_hpp__ */
