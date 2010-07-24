#ifndef _sql_Guid_hpp__
#define _sql_Guid_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <cstring>
#include <iosfwd>
#include <string>

namespace sql {

        /*!
         * @brief 128-bit globally unique identifier.
         */
    class Guid
    {
        /* nested types. */
    public:
        typedef ::SQLGUID Value;

        /* class data. */
    public:
        static const Guid zero;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Guid ();
        Guid (
            uint32 a, uint16 b, uint16 c,
            uint8 d, uint8 e, uint8 f, uint8 g,
            uint8 h, uint8 i, uint8 j, uint8 k
            );

        Guid ( const Value& value );

        /* methods. */
    public:
        Value& value ();
        const Value& value () const;

        /* operators. */
    public:
        Guid& operator= ( const Value& value );
        bool operator== ( const Guid& other ) const;
        bool operator!= ( const Guid& other ) const;

        operator std::string() const;
        operator std::wstring() const;
    };

    std::ostream& operator<< ( std::ostream& out, const Guid& value );
    std::wostream& operator<< ( std::wostream& out, const Guid& value );

}

#endif /* _sql_Guid_hpp__ */
