#ifndef _sql_sqlite_hpp__
#define _sql_sqlite_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql.hpp>

namespace sql { namespace sqlite {

        /*!
         * @brief Groups fields used in the connection string passed to the ODBC
         *   driver to open the connection.
         */
    class ConnectionString :
        public sql::ConnectionString
    {
        /* data. */
    private:
        string myDatabase;

        /* construction. */
    public:
        ConnectionString ( const string& database )
            : myDatabase(database)
        {}

        /* methods. */
    public:
        const string& database () const {
            return (myDatabase);
        }

        void database ( const string& value ) {
            myDatabase = value;
        }

        /* overrides. */
    protected:
        virtual std::ostream& put ( std::ostream& out ) const;
    };

} }

#endif /* _sql_sqlite_hpp__ */
