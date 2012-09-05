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
        /*!
         * @internal
         * @brief Native representation.
         */
        typedef ::SQLGUID Value;

        /* class data. */
    public:
        /*!
         * @brief All zeroes.
         */
        static const Guid zero;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        /*!
         * @brief Default-initialize to all zeroes.
         */
        Guid ();

        /*!
         * @brief Value-initialize from its components.
         * @param a 1st component: 8 hex digit.
         * @param b 2nd component: 4 hex digit.
         * @param c 3nd component: 4 hex digit.
         * @param d 4th component: 2 hex digit.
         * @param e 5th component: 2 hex digit.
         * @param f 6th component: 2 hex digit.
         * @param g 7th component: 2 hex digit.
         * @param h 8th component: 2 hex digit.
         * @param i 9th component: 2 hex digit.
         * @param j 10th component: 2 hex digit.
         * @param k 11th component: 2 hex digit.
         *
         * The format used is similar to that used by the Windows Registry.
         */
        Guid (uint32 a, uint16 b, uint16 c,
              uint8 d, uint8 e, uint8 f, uint8 g,
              uint8 h, uint8 i, uint8 j, uint8 k);

        /*!
         * @internal
         * @brief Copy-initialize from the native representation.
         */
        Guid (const Value& value);

        /* methods. */
    public:
        /*!
         * @internal
         * @brief Access the native representation.
         * @return The wrapped value.
         */
        Value& value ();

        /*!
         * @internal
         * @brief Access the native representation.
         * @return The wrapped value.
         */
        const Value& value () const;

        /* operators. */
    public:
        /*!
         * @internal
         * @brief Assign directly from the native representation.
         * @return @c *this, for method chaining.
         */
        Guid& operator= (const Value& value);

        /*!
         * @brief Compare two guids for equality.
         * @param rhs Right-hand-side argument to compare with.
         * @return @c true if @c *this and @a rhs are an exact match.
         */
        bool operator== (const Guid& rhs) const;

        /*!
         * @brief Compare two guids for equality.
         * @param rhs Right-hand-side argument to compare with.
         * @return @c true if @c *this and @a rhs are not an exact match.
         */
        bool operator!= (const Guid& rhs) const;

        /*!
         * @brief Convert the guid to a string.
         * @return *this, formatted as a string.
         *
         * @see operator<<(std::ostream&,const Guid&)
         */
        operator std::string() const;

        /*!
         * @brief Convert the guid to a string.
         * @return *this, formatted as a string.
         *
         * @see operator<<(std::wostream&,const Guid&)
         */
        operator std::wstring() const;
    };

    /*!
     * @brief Serialize the GUID.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::ostream& operator<< (std::ostream& stream, const Guid& value);

    /*!
     * @brief Serialize the GUID.
     * @param stream Destination output stream.
     * @param value Value to write.
     * @return @a stream, for method chaining.
     */
    std::wostream& operator<< (std::wostream& stream, const Guid& value);

}

#endif /* _sql_Guid_hpp__ */
