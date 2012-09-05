#ifndef _sql_types_hpp_
#define _sql_types_hpp_

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
     * @brief 8-bit character unit.
     */
    typedef ::SQLCHAR character;

    /*!
     * @brief UTF-16 16-bit unit.
     *
     * It is guaranteed that 16-bit units cannot always represent a character.
     * A single unit cannot represent code points outside the basic
     * multilingual plain and cannot handle decomposed characters.  Moreoever,
     * some code points may represent more than one "user-perceived character".
     */
    typedef ::SQLWCHAR wcharacter;

    /*!
     * @brief Unsigned integral type used for representing sizes.
     */
    typedef ::SQLLEN size_t;

    /*!
     * @brief 8-bit signed integer (SQL tiny integer).
     */
    typedef ::SQLSCHAR int8;

    /*!
     * @brief 8-bit unsigned integer (SQL tiny integer).
     */
    typedef ::SQLCHAR uint8;

    /*!
     * @brief 16-bit signed integer (SQL small integer).
     */
    typedef ::SQLSMALLINT int16;

    /*!
     * @brief 16-bit unsigned signed integer (SQL small integer).
     */
    typedef ::SQLUSMALLINT uint16;

    /*!
     * @brief 32-bit signed integer (SQL integer).
     */
    typedef ::SQLINTEGER int32;

    /*!
     * @brief 32-bit unsigned integer (SQL integer).
     */
    typedef ::SQLUINTEGER uint32;

    /*!
     * @brief 64-bit signed integer (SQL big integer).
     */
    typedef ::SQLBIGINT int64;

    /*!
     * @brief 64-bit unsigned integer (SQL big integer).
     */
    typedef ::SQLUBIGINT uint64;

    /*!
     * @internal
     * @brief Placeholder type for implementing @c null.
     */
    class Null {};

    /*!
     * @brief Placeholder for "null" database values.
     */
    static const Null null;

}

#endif /* _sql_types_hpp_ */
