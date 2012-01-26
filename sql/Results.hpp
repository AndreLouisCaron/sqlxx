#ifndef _sql_Results_hpp__
#define _sql_Results_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <sql/NotCopyable.hpp>
#include <sql/Statement.hpp>
#include <sql/string.hpp>
#include <sql/Date.hpp>
#include <sql/Time.hpp>
#include <sql/Timestamp.hpp>
#include <sql/Guid.hpp>
#include <sql/Numeric.hpp>

namespace sql {

    class Row {};

    extern const Row row;

    class Null {};

    extern const Null null;

    class Results;

        /*!
         * @brief Convenient utility for reading the results returned by an SQL
         *    query.
         *
         * This allows reading of individual rows. This object is also called
         * a result set in other libraries. Note that in this case, results on
         * a given row a read by \c Row objects.
         */
    class Results :
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
        typedef Results&(*Manipulator)(Results&);

        class State
        {
            /* class data. */
        public:
            static const State good;
            static const State null;
            static const State fail;

            /* data. */
        private:
            unsigned int myBits;

            /* construction. */
        private:
            State ( unsigned int bits );

        public:
            State ();

            /* methods. */
        public:
            void set ( const State& bits );
            void clear ( const State& bits );
            bool get ( const State& bits );

            /* operators. */
        public:
            operator bool () const;

            State& operator&= ( const State& other );
            State& operator|= ( const State& other );

            State operator& ( const State& other ) const;
            State operator| ( const State& other ) const;
        };

        /* data. */
    private:
        Statement& myStatement;
        State myState;
        ::SQLUSMALLINT myColumn;

        /* construction. */
    public:
        Results ( Statement& statement )
            : myStatement(statement), myState(), myColumn(0)
        {}

        /* methods. */
    public:
        Statement& statement () {
            return (myStatement);
        }

        const State& state () const {
            return (myState);
        }

        operator bool () const {
            return ((bool)myState);
        }

        const Handle& handle () const throw() {
            return (myStatement.handle());
        }

            /*!
             * @brief Obtains the number of rows returned by the last query.
             *
             * Note that this is not necessary (the abstraction allows you not
             * to worry about indices), but is convenient if you want to reserve
             * memory for an array of objects, or take particular action based
             * on the number of results, etc.
             */
        size_t rows () const;

        /* operators. */
    public:
            /*!
             * @brief Applies a manipulator to the row.
             */
        Results& operator>> ( Manipulator manipulator ) {
            return ((*manipulator)(*this));
        }

            /*!
             * @brief Fetches the next row in the results.
             */
        Results& operator>> ( const Row& );

            /*!
             * @brief Reads the next value if it's null.
             */
        Results& operator>> ( const Null& );

            /*!
             * @brief Reads the next column as a signed 8-bit integer field.
             */
        Results& operator>> ( int8& value );

            /*!
             * @brief Reads the next column as an unsigned 8-bit integer field.
             */
        Results& operator>> ( uint8& value );

            /*!
             * @brief Reads the next column as a signed 16-bit integer field.
             */
        Results& operator>> ( int16& value );

            /*!
             * @brief Reads the next column as an unsigned 16-bit integer field.
             */
        Results& operator>> ( uint16& value );

            /*!
             * @brief Reads the next column as a signed 32-bit integer field.
             */
        Results& operator>> ( int32& value );

            /*!
             * @brief Reads the next column as an unsigned 32-bit integer field.
             */
        Results& operator>> ( uint32& value );

            /*!
             * @brief Reads the next column as a signed 64-bit integer field.
             */
        Results& operator>> ( int64& value );

            /*!
             * @brief Reads the next column as an unsigned 64-bit integer field.
             */
        Results& operator>> ( uint64& value );

            /*!
             * @brief Reads the next column as a 32-bit floating point field.
             */
        Results& operator>> ( float& value );

            /*!
             * @brief Reads the next column as a 64-bit floating point field.
             */
        Results& operator>> ( double& value );

            /*!
             * @brief Reads the next column as a string field.
             *
             * The result depends on what the database field's type actually
             * is. For instance, reading a fixed lenght string field will yield
             * a string with exactly that length.
             */
        Results& operator>> ( string& value );

            /*!
             * @brief Reads the next column as a wide string field.
             *
             * The result depends on what the database field's type actually
             * is. For instance, reading a fixed lenght string field will yield
             * a string with exactly that length.
             */
        Results& operator>> ( wstring& value );

            /*!
             * @brief Reads the next column as a date field.
             */
        Results& operator>> ( Date& value );

            /*!
             * @brief Reads the next column as a unique identifier field.
             */
        Results& operator>> ( Guid& value );

            /*!
             * @brief Reads the next column as a numeric field.
             */
        Results& operator>> ( Numeric& value );

            /*!
             * @brief Reads the next column as a time field.
             */
        Results& operator>> ( Time& value );

            /*!
             * @brief Reads the next column as a timestamp field.
             */
        Results& operator>> ( Timestamp& value );
    };

}

#endif /* _sql_Results_hpp__ */
