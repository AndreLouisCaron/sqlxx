#ifndef _sql_ConnectionString_hpp__
#define _sql_ConnectionString_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <iosfwd>
#include <string>

namespace sql {

    class ConnectionString;

    std::ostream& operator<< (
        std::ostream& out, const ConnectionString& string
        );

        /*!
         * @brief Encapsulates parameters required to open the connection to
         *    a database using an ODBC database driver.
         *
         * As parameters vary from driver to driver and between different
         * connection modes for a given driver, this class must be implemented
         * for each type of database.
         */
    class ConnectionString
    {
        /* construction. */
    public:
        virtual ~ConnectionString () {
        }

        /* methods. */
    protected:
            /*!
             * @brief Does the actual output and depends on the parameters
             *    passed to the driver.
             */
        virtual std::ostream& put ( std::ostream& out ) const = 0;

        /* operators. */
    public:
        operator std::string () const;

            // Puts the parameters (properly formatter) to a stream.
        friend std::ostream& operator<< (
            std::ostream& out, const ConnectionString& string
            );
    };

}

#endif /* _sql_ConnectionString_hpp__ */
