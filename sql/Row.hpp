#ifndef _sql_Row_hpp__
#define _sql_Row_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <sql/string.hpp>
#include <sql/Date.hpp>
#include <sql/Guid.hpp>
#include <sql/NotCopyable.hpp>
#include <sql/Numeric.hpp>
#include <sql/Time.hpp>
#include <sql/Timestamp.hpp>

namespace sql {

#if 0

    class Row;

        /*!
         * @brief Utility to read individual results among isolated rows in a
         *   results set.
         *
         * This is a proxy object used to make the code easy to write. It is
         * extremely lightweight and convenient.
         */
    class Row :
        private NotCopyable
    {
        /* nested types. */
    public:
            /*!
             * @brief Function that modifies the result set input.
             *
             * Manipulators may be inserted into the stream among other read
             * operations, just like manipulators for standard i/o streams.
             */
        typedef Row&(*Manipulator)(Row&);

        /* data. */
    private:
        ResultSet * myResultSet;
        ::SQLUSMALLINT myColumn;

        /* construction. */
    public:
        Row ()
            : myResultSet(0), myColumn(0)
        {}

        /* methods. */
    public:
            /*!
             * @brief Skips the following column.
             *
             * Use this when a query returns some data you do not want to use.
             * This may be necessary if you receive data but cannot change the
             * query that requests the returned data.
             */
        void skip () {
            ++myColumn;
        }

        /* operators. */
    public:
            /*!
             * @brief Tests the row for being ok to read.
             *
             * This function acts as a boolean test, so the return value has
             * no meaning whatsoever and should not be manipulated in any way,
             * except for the intended boolean test. In fact, applications
             * should not rely on this being a pointer at all.
             */
        operator const void* () const {
            return (myResultSet);
        }

            /*!
             * @brief Applies a manipulator to the row.
             */
        Row& operator>> ( Manipulator manipulator ) {
            return ((*manipulator)(*this));
        }

            /*!
             * @brief Reads the next column as a signed 8-bit integer field.
             */
        Row& operator>> ( int8& value );

            /*!
             * @brief Reads the next column as an unsigned 8-bit integer field.
             */
        Row& operator>> ( uint8& value );

            /*!
             * @brief Reads the next column as a signed 16-bit integer field.
             */
        Row& operator>> ( int16& value );

            /*!
             * @brief Reads the next column as an unsigned 16-bit integer field.
             */
        Row& operator>> ( uint16& value );

            /*!
             * @brief Reads the next column as a signed 32-bit integer field.
             */
        Row& operator>> ( int32& value );

            /*!
             * @brief Reads the next column as an unsigned 32-bit integer field.
             */
        Row& operator>> ( uint32& value );

            /*!
             * @brief Reads the next column as a signed 64-bit integer field.
             */
        Row& operator>> ( int64& value );

            /*!
             * @brief Reads the next column as an unsigned 64-bit integer field.
             */
        Row& operator>> ( uint64& value );

            /*!
             * @brief Reads the next column as a 32-bit floating point field.
             */
        Row& operator>> ( float& value );

            /*!
             * @brief Reads the next column as a 64-bit floating point field.
             */
        Row& operator>> ( double& value );

            /*!
             * @brief Reads the next column as a string field.
             *
             * The result depends on what the database field's type actually
             * is. For instance, reading a fixed lenght string field will yield
             * a string with exactly that length.
             */
        Row& operator>> ( string& value );

            /*!
             * @brief Reads the next column as a wide string field.
             *
             * The result depends on what the database field's type actually
             * is. For instance, reading a fixed lenght string field will yield
             * a string with exactly that length.
             */
        Row& operator>> ( wstring& value );

            /*!
             * @brief Reads the next column as a date field.
             */
        Row& operator>> ( Date& value );

            /*!
             * @brief Reads the next column as a unique identifier field.
             */
        Row& operator>> ( Guid& value );

            /*!
             * @brief Reads the next column as a numeric field.
             */
        Row& operator>> ( Numeric& value );

            /*!
             * @brief Reads the next column as a time field.
             */
        Row& operator>> ( Time& value );

            /*!
             * @brief Reads the next column as a timestamp field.
             */
        Row& operator>> ( Timestamp& value );
    };

        /*!
         * @brief Skips a field in the row.
         *
         * The effect of this manipulator is exactly the same as using the
         * \c Row::skip() function, but is more convenient when used among other
         * reading operations.
         */
    Row& skip ( Row& row );

#endif

}

#endif /* _sql_Row_hpp__ */
