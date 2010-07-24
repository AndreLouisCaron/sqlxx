// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Guid.hpp>
#include <iomanip>
#include <ostream>
#include <sstream>

namespace {

    const ::SQLGUID Zero = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0} };

    template<typename Char, class Traits>
    std::basic_ostream<Char, Traits>& h2
        ( std::basic_ostream<Char, Traits>& out )
    {
        return (out << std::setw(2) << std::setfill(out.widen('0')));
    }

    template<typename Char, class Traits>
    std::basic_ostream<Char, Traits>& h4
        ( std::basic_ostream<Char, Traits>& out )
    {
        return (out << std::setw(4) << std::setfill(out.widen('0')));
    }

    template<typename Char, class Traits>
    std::basic_ostream<Char, Traits>& h8
        ( std::basic_ostream<Char, Traits>& out )
    {
        return (out << std::setw(8) << std::setfill(out.widen('0')));
    }

}

namespace sql {

    const Guid Guid::zero(Zero);

    Guid::Guid ()
    {
        std::memset(&myValue,0,sizeof(myValue));
    }

    Guid::Guid (
        uint32 a, uint16 b, uint16 c,
        uint8 d, uint8 e, uint8 f, uint8 g,
        uint8 h, uint8 i, uint8 j, uint8 k
        )
    {
        const ::SQLGUID value = {
            a, b, c, { d, e, f, g, h, i, j, k }
        };
        myValue = value;
    }

    Guid::Guid ( const Value& value )
        : myValue(value)
    {
    }

    Guid::Value& Guid::value ()
    {
        return (myValue);
    }

    const Guid::Value& Guid::value () const
    {
        return (myValue);
    }

    Guid& Guid::operator= ( const Value& value )
    {
        myValue = value;
        return (*this);
    }

    bool Guid::operator== ( const Guid& other ) const
    {
        return (std::memcmp(&myValue,&other.myValue,sizeof(Value)) == 0);
    }

    bool Guid::operator!= ( const Guid& other ) const
    {
        return ( !((*this) == other) );
    }

    Guid::operator std::string() const
    {
        std::ostringstream stream;
        stream << (*this);
        return (stream.str());
    }

    Guid::operator std::wstring() const
    {
        std::wostringstream stream;
        stream << (*this);
        return (stream.str());
    }

    std::ostream& operator<< ( std::ostream& out, const Guid& guid )
    {
        const Guid::Value& value = guid.value();
        out << std::hex << h8 << value.Data1 << '-'
            << h4 << value.Data2 << '-'
            << h4 << value.Data3 << '-'
            << h2 << value.Data4[0]
            << h2 << value.Data4[1] << '-'
            << h2 << value.Data4[2]
            << h2 << value.Data4[3]
            << h2 << value.Data4[4]
            << h2 << value.Data4[5]
            << h2 << value.Data4[6]
            << h2 << value.Data4[7] << std::dec;
        return (out);
    }

    std::wostream& operator<< ( std::wostream& out, const Guid& guid )
    {
        const Guid::Value& value = guid.value();
        out << std::hex << h8 << value.Data1 << L'-'
            << h4 << value.Data2 << L'-'
            << h4 << value.Data3 << L'-'
            << h2 << value.Data4[0]
            << h2 << value.Data4[1] << L'-'
            << h2 << value.Data4[2]
            << h2 << value.Data4[3]
            << h2 << value.Data4[4]
            << h2 << value.Data4[5]
            << h2 << value.Data4[6]
            << h2 << value.Data4[7] << std::dec;
        return (out);
    }

}
