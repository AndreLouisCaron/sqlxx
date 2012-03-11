#ifndef _sql_Guid_hpp__
#define _sql_Guid_hpp__

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
