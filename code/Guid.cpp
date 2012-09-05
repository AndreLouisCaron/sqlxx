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

#include "Guid.hpp"
#include <iomanip>
#include <ostream>
#include <sstream>

namespace {

    const ::SQLGUID Zero = { 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0, 0} };

    template<typename Char, class Traits>
    std::basic_ostream<Char, Traits>& h2
        (std::basic_ostream<Char, Traits>& stream)
    {
        return (stream << std::setw(2) << std::setfill(stream.widen('0')));
    }

    template<typename Char, class Traits>
    std::basic_ostream<Char, Traits>& h4
        (std::basic_ostream<Char, Traits>& stream)
    {
        return (stream << std::setw(4) << std::setfill(stream.widen('0')));
    }

    template<typename Char, class Traits>
    std::basic_ostream<Char, Traits>& h8
        (std::basic_ostream<Char, Traits>& stream)
    {
        return (stream << std::setw(8) << std::setfill(stream.widen('0')));
    }

}

namespace sql {

    const Guid Guid::zero(Zero);

    Guid::Guid ()
    {
        std::memset(&myValue,0,sizeof(myValue));
    }

    Guid::Guid (uint32 a, uint16 b, uint16 c,
                uint8 d, uint8 e, uint8 f, uint8 g,
                uint8 h, uint8 i, uint8 j, uint8 k)
    {
        const ::SQLGUID value = {
            a, b, c, { d, e, f, g, h, i, j, k }
        };
        myValue = value;
    }

    Guid::Guid (const Value& value)
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

    Guid& Guid::operator= (const Value& value)
    {
        myValue = value;
        return (*this);
    }

    bool Guid::operator== (const Guid& rhs) const
    {
        return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) == 0);
    }

    bool Guid::operator!= (const Guid& rhs) const
    {
        return (std::memcmp(&myValue,&rhs.myValue,sizeof(Value)) == 1);
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

    std::ostream& operator<< (std::ostream& stream, const Guid& guid)
    {
        const Guid::Value& value = guid.value();
        stream << std::hex
               << h8 << value.Data1 << '-'
               << h4 << value.Data2 << '-'
               << h4 << value.Data3 << '-'
               << h2 << value.Data4[0]
               << h2 << value.Data4[1] << '-'
               << h2 << value.Data4[2]
               << h2 << value.Data4[3]
               << h2 << value.Data4[4]
               << h2 << value.Data4[5]
               << h2 << value.Data4[6]
               << h2 << value.Data4[7]
               << std::dec;
        return (stream);
    }

    std::wostream& operator<< (std::wostream& stream, const Guid& guid)
    {
        const Guid::Value& value = guid.value();
        stream << std::hex
               << h8 << value.Data1 << L'-'
               << h4 << value.Data2 << L'-'
               << h4 << value.Data3 << L'-'
               << h2 << value.Data4[0]
               << h2 << value.Data4[1] << L'-'
               << h2 << value.Data4[2]
               << h2 << value.Data4[3]
               << h2 << value.Data4[4]
               << h2 << value.Data4[5]
               << h2 << value.Data4[6]
               << h2 << value.Data4[7]
               << std::dec;
        return (stream);
    }

}
