#ifndef _sql_firebird_hpp__
#define _sql_firebird_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql.hpp>

namespace sql { namespace firebird {

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
        string myUser;
        string myPassword;

        /* construction. */
    public:
        ConnectionString (
            const string& database, const string& user, const string& password
            )
            : myDatabase(database), myUser(user), myPassword(password)
        {}

        /* methods. */
    public:
        const string& database () const {
            return (myDatabase);
        }

        void database ( const string& value ) {
            myDatabase = value;
        }

        const string& user () const {
            return (myUser);
        }

        void user ( const string& value ) {
            myUser = value;
        }

        const string& password () const {
            return (myPassword);
        }

        void password ( const string& value ) {
            myPassword = value;
        }

        /* overrides. */
    protected:
        virtual std::ostream& put ( std::ostream& out ) const;
    };

} }

#endif /* _sql_firebird_hpp__ */
