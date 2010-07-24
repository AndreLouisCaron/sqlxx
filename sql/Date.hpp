#ifndef _sql_Date_hpp__
#define _sql_Date_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <iosfwd>
#include <string>

namespace sql {

        /*!
         * @brief Group of (year,month,day) values.
         */
    class Date
    {
        /* nested types. */
    public:
        typedef ::SQL_DATE_STRUCT Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Date () {
            myValue.year = 0, myValue.month = 0, myValue.day = 0;
        }

        Date ( int16 year, uint16 month, uint16 day ) {
            myValue.year = year, myValue.month = month, myValue.day = day;
        }

        Date ( const Value value )
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

        int16 year () const {
            return (myValue.year);
        }

        void year ( int16 value ) {
            myValue.year = value;
        }

        uint16 month () const {
            return (myValue.month);
        }

        void month ( uint16 value ) {
            myValue.month = value;
        }

        uint16 day () const {
            return (myValue.day);
        }

        void day ( uint16 value ) {
            myValue.day = value;
        }

        /* operators. */
    public:
        Date& operator= ( const Value& value )
        {
            myValue = value;
            return (*this);
        }

        bool operator== ( const Date& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) == 0);
        }

        bool operator!= ( const Date& other ) const {
            return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) != 0);
        }

        operator std::string() const;
        operator std::wstring() const;
    };

    std::ostream& operator<< ( std::ostream& out, const Date& value );
    std::wostream& operator<< ( std::wostream& out, const Date& value );

}

#endif /* _sql_Date_hpp__ */
