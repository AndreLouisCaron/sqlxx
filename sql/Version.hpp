#ifndef _sql_Version_hpp__
#define _sql_Version_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace sql {

        /*!
         * @brief Enumeration of ODBC Versions.
         */
    class Version
    {
        /* nested types. */
    public:
            /*!
             * @brief Native representation of version values.
             */
        typedef ::SQLPOINTER Value;

        /* class data. */
    public:
            /*!
             * @brief Version 2.x style calls.
             */
        static const Version odbc2;

            /*!
             * @brief Version 3.x style calls.
             */
        static const Version odbc3;

        /* members. */
    private:
        Value myValue;

        /* construction. */
    private:
        explicit Version ( Value value ) throw();

        /* methods. */
    public:
            /*!
             * @brief Obtains the version's value, in it's native API
             *    representation.
             * @return The version's native value.
             */
        Value value () const throw();
    };

}

#endif /* _sql_Version_hpp__ */
