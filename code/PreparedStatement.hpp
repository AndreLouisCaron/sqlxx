#ifndef _sql_PreparedStatement_hpp__
#define _sql_PreparedStatement_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include "types.hpp"
#include "string.hpp"
#include "Date.hpp"
#include "Guid.hpp"
#include "Numeric.hpp"
#include "Statement.hpp"
#include "Time.hpp"
#include "Timestamp.hpp"

namespace sql {

    class Connection;

        /*!
         * @brief Fast, safe and convenient way to write queries.
         */
    class PreparedStatement :
        public Statement
    {
        /* nested types. */
    public:
            /*!
             * @brief Function that can be passed in a convenient fashion.
             */
        typedef PreparedStatement&(*Manipulator)(PreparedStatement&);

        /* data. */
    private:
        uint16 myNext;

        /* construction. */
    public:
        PreparedStatement ( Connection& connection, const string& query );

        /* methods. */
    public:
            /*!
             * @brief Makes the next call to \c bind() bind the value to the
             *    first parameter.
             *
             * You usually need this to call this between two different updates
             * on the same prepared update object.
             */
        void reset ();

            /*!
             * @brief Binds a signed 8-bit integer to the next parameter.
             */
        void bind ( const int8& value );

            /*!
             * @brief Binds an unsigned 8-bit integer to the next parameter.
             */
        void bind ( const uint8& value );

            /*!
             * @brief Binds a signed 16-bit integer to the next parameter.
             */
        void bind ( const int16& value );

            /*!
             * @brief Binds an unsigned 16-bit integer to the next parameter.
             */
        void bind ( const uint16& value );

            /*!
             * @brief Binds a signed 32-bit integer to the next parameter.
             */
        void bind ( const int32& value );

            /*!
             * @brief Binds an unsigned 32-bit integer to the next parameter.
             */
        void bind ( const uint32& value );

            /*!
             * @brief Binds a signed 64-bit integer to the next parameter.
             */
        void bind ( const int64& value );

            /*!
             * @brief Binds an unsigned 64-bit integer to the next parameter.
             */
        void bind ( const uint64& value );

            /*!
             * @brief Binds a 32-bit floating point to the next parameter.
             */
        void bind ( const float& value );

            /*!
             * @brief Binds a 64-bit floating point to the next parameter.
             */
        void bind ( const double& value );

            /*!
             * @brief Binds a string to the next parameter.
             */
        void bind ( const string& value );

            /*!
             * @brief Binds a wide string to the next parameter.
             */
        void bind ( const wstring& value );

            /*!
             * @brief Binds a date value to the next parameter.
             */
        void bind ( const Date& date );

            /*!
             * @brief Binds a unique identifier value to the next parameter.
             */
        void bind ( const Guid& guid );

            /*!
             * @brief Binds a numeric value to the next parameter.
             */
        void bind ( const Numeric& numeric );

            /*!
             * @brief Binds a time value to the next parameter.
             */
        void bind ( const Time& time );

            /*!
             * @brief Binds a timestamp value to the next parameter.
             */
        void bind ( const Timestamp& timestamp );

            /*!
             * @brief Applies a manipulator to the update object.
             */
        PreparedStatement& operator<< ( Manipulator manipulator ) {
            return ((*manipulator)(*this));
        }

        /* overrides. */
    public:
            /*!
             * @brief Executes as a prepared statement, and \c reset()s.
             */
        void execute ();
    };

        /*!
         * @brief Binds any supported value to the next available parameter.
         */
    template<typename Value>
        inline
    PreparedStatement& operator<< ( PreparedStatement& update, const Value& value )
    {
        update.bind(value);
        return (update);
    }

        /*!
         * @brief Make the next binding operation bind to the first parameter.
         */
    PreparedStatement& reset ( PreparedStatement& update );

}

#endif /* _sql_PreparedStatement_hpp__ */
