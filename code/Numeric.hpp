#ifndef _sql_Numeric_hpp__
#define _sql_Numeric_hpp__

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
