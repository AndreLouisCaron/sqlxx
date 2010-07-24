#ifndef _sql_Numeric_hpp__
#define _sql_Numeric_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace sql {

        /*!
         * @brief Number with fixed precision and scale.
         */
    class Numeric
    {
        /* nested types. */
    public:
        typedef ::SQL_NUMERIC_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Numeric () {
            std::memset(&myValue,0,sizeof(myValue));
        }

        Numeric ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value& value () {
            return (myValue);
        }

        const Value& value () const {
            return (myValue);
        }

        /* operators. */
    public:
        Numeric& operator= ( const Value& value )
        {
            myValue = value;
            return (*this);
        }

        bool operator== ( const Numeric& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) == 0);
        }
    };

}

#endif /* _sql_Numeric_hpp__ */
