#ifndef _sql_Results_hpp__
#define _sql_Results_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include "types.hpp"
#include "NotCopyable.hpp"
#include "Statement.hpp"
#include "string.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "Timestamp.hpp"
#include "Guid.hpp"
#include "Numeric.hpp"

namespace sql {

    class Row {}; static const Row row;

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
