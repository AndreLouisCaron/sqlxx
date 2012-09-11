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

    /*!
     * @internal
     * @brief Placeholder type for implementing @c null.
     */
    class Row {};

    /*!
     * @brief Placeholder for a row's results.
     */
    static const Row row;

    class Results;

    /*!
     * @brief Skip the next result in the current row.
     * @param results Result set in which to skip a result.
     * @return @a results, for method chaining.
     *
     * This is a @c Results::Manipulator.
     *
     * @see Results::skip()
     * @see Results::operator>>(Results::Manipulator)
     */
    Results& skip (Results& results);

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
        friend Results& skip (Results& results);

        /* nested types. */
    public:
        /*!
         * @brief Function that modifies the result set input.
         *
         * Manipulators may be inserted into the stream among other read
         * operations, just like manipulators for standard i/o streams.
         */
        typedef Results&(*Manipulator)(Results&);

        /*!
         * @brief Results stream state.
         */
        class State
        {
            /* class data. */
        public:
            /*!
             * @brief State is OK, ready to read.
             */
            static const State good ();

            /*!
             * @brief Got a null value, last read operation is a no-op.
             */
            static const State null ();

            /*!
             * @brief Last operation failed.
             *
             * @see clear()
             */
            static const State fail ();

            /* data. */
        private:
            unsigned int myBits;

            /* construction. */
        private:
            /*!
             * @internal
             * @brief Build from enumerated value.
             */
            State (unsigned int bits);

        public:
            /*!
             * @brief Build a state in @c good() mode.
             */
            State ();

            /* methods. */
        public:
            /*!
             * @brief Change the current state.
             * @param bits New mask, enables the corresponding state.
             */
            void set (const State& bits);

            /*!
             * @brief Obtain the current state.
             * @param bits Bit mask, checks the corresponding state.
             */
            bool get (const State& bits);

            /*!
             * @brief Reset the current state.
             * @param bits Bit mask, resets the corresponding state.
             */
            void clear (const State& bits);

            /* operators. */
        public:
            /*!
             * @brief Check for error state.
             * @return @c false if @c get(fail()), else @c true.
             *
             * @see Results::operator bool()
             */
            operator bool () const;

            /*!
             * @brief Clears the current state.
             * @param rhs State mask to clear.
             * @return @c *this, for method chaining.
             *
             * @see clear(const State&)
             */
            State& operator&= (const State& rhs);

            /*!
             * @brief Enables the current state.
             * @param rhs State mask to enable.
             * @return @c *this, for method chaining.
             *
             * @see set(const State&)
             */
            State& operator|= (const State& rhs);

            /*!
             * @brief Checks the current state.
             * @param rhs State mask to check.
             * @return The resulting state.
             *
             * @see get(const State&)
             */
            State operator& (const State& rhs) const;

            /*!
             * @brief Checks the current state.
             * @param rhs State mask to check.
             * @return The resulting state.
             *
             * @see get(const State&)
             */
            State operator| (const State& rhs) const;
        };

        /* data. */
    private:
        Statement& myStatement;
        State myState;
        ::SQLUSMALLINT myColumn;

        /* construction. */
    public:
        /*!
         * @brief Start reading results from @a statement.
         * @param statement Statement (query) that generated the results.
         */
        Results (Statement& statement)
            : myStatement(statement), myState(), myColumn(0)
        {}

        /* methods. */
    public:
        /*!
         * @brief Access the statement (query) that generated the result set.
         * @return The statement.
         */
        Statement& statement () {
            return (myStatement);
        }

        /*!
         * @brief Access the current state.
         * @return The current stream state.
         */
        const State& state () const {
            return (myState);
        }

        /*!
         * @brief Check if the last operation succeeded.
         * @return @c bool(state()).
         *
         * @see State::operator bool()
         */
        operator bool () const {
            return ((bool)myState);
        }

        /*!
         * @internal
         * @brief Access the native statement handle.
         * @return @c statement().handle().
         */
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

        /*!
         * @brief Skip the next result in the current row.
         * @return @a *this, for method chaining.
         *
         * This is typically used indirectly through @c skip(Results&), a
         * stream @c Manipulator.
         *
         * @see operator>>(Manipulator)
         * @see skip(Results&)
         */
        Results& skip ();

        /* operators. */
    public:
        /*!
         * @brief Applies a manipulator to the result set.
         */
        Results& operator>> (Manipulator manipulator) {
            return ((*manipulator)(*this));
        }

        /*!
         * @brief Fetches the next row in the results.
         */
        Results& operator>> (const Row&);

        /*!
         * @brief Reads the next value if it's null.
         */
        Results& operator>> (const Null&);

        /*!
         * @brief Reads the next column as a signed 8-bit integer field.
         */
        Results& operator>> (int8& value);

        /*!
         * @brief Reads the next column as an unsigned 8-bit integer field.
         */
        Results& operator>> (uint8& value);

        /*!
         * @brief Reads the next column as a signed 16-bit integer field.
         */
        Results& operator>> (int16& value);

        /*!
         * @brief Reads the next column as an unsigned 16-bit integer field.
         */
        Results& operator>> (uint16& value);

        /*!
         * @brief Reads the next column as a signed 32-bit integer field.
         */
        Results& operator>> (int32& value);

        /*!
         * @brief Reads the next column as an unsigned 32-bit integer field.
         */
        Results& operator>> (uint32& value);

        /*!
         * @brief Reads the next column as a signed 64-bit integer field.
         */
        Results& operator>> (int64& value);

        /*!
         * @brief Reads the next column as an unsigned 64-bit integer field.
         */
        Results& operator>> (uint64& value);

        /*!
         * @brief Reads the next column as a 32-bit floating point field.
         */
        Results& operator>> (float& value);

        /*!
         * @brief Reads the next column as a 64-bit floating point field.
         */
        Results& operator>> (double& value);

        /*!
         * @brief Reads the next column as a string field.
         *
         * The result depends on what the database field's type actually
         * is. For instance, reading a fixed lenght string field will yield
         * a string with exactly that length.
         */
        Results& operator>> (string& value);

        /*!
         * @brief Reads the next column as a wide string field.
         *
         * The result depends on what the database field's type actually
         * is. For instance, reading a fixed lenght string field will yield
         * a string with exactly that length.
         */
        Results& operator>> (wstring& value);

        /*!
         * @brief Reads the next column as a date field.
         */
        Results& operator>> (Date& value);

        /*!
         * @brief Reads the next column as a unique identifier field.
         */
        Results& operator>> (Guid& value);

        /*!
         * @brief Reads the next column as a numeric field.
         */
        Results& operator>> (Numeric& value);

        /*!
         * @brief Reads the next column as a time field.
         */
        Results& operator>> (Time& value);

        /*!
         * @brief Reads the next column as a timestamp field.
         */
        Results& operator>> (Timestamp& value);
    };

}

#endif /* _sql_Results_hpp__ */
