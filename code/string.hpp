#ifndef _sql_string_hpp__
#define _sql_string_hpp__

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
#include <algorithm>
#include <ostream>
#include <string>

namespace sql {

    template<typename C> struct char_traits;

    template<> struct char_traits<character>
    {
        typedef char std_char;
    };

    template<> struct char_traits<wcharacter>
    {
        typedef wchar_t std_char;
    };

        /*!
         * @brief Replacement for std::string which does not allow to write
         *    directly into it's buffer because it wishes to support optional
         *    copy-on-write semantics.
         */
    template<typename Char>
    class basic_string
    {
        /* nested types. */
    public:
        typedef Char char_type;
        typedef size_t size_type;
        typedef char_type * iterator;
        typedef const char_type * const_iterator;

        typedef typename char_traits<char_type>::std_char std_char_type;
        typedef std::basic_string<std_char_type> std_string_type;

    private:
            // To make this template class somewhat readable.
        typedef basic_string<Char> self_type;

        /* data. */
    private:
        size_type myCapacity;
        char_type * myData;

        /* construction. */
    public:
            /*!
             * @brief Creates a copy of the given string.
             *
             * @note Although this is a convenient way to convert ASCII strings
             *    to other types of characters, this will not account for multi
             *    byte character sets, such as UTF-8.
             *
             * @param value Pointer to the first character in the null
             *    terminated string.
             */
        basic_string ( const char * value = "" )
            : myCapacity(0), myData(0)
        {
            const char *const termination = endof(value);
            self_type buffer(static_cast<size_type>(termination-value));
            std::copy(value,termination,buffer.begin());
            buffer.swap(*this);
        }

            /*!
             * @brief Creates a copy of the given string.
             */
        basic_string ( const char_type * value )
            : myCapacity(0), myData(0)
        {
            const char_type *const termination = endof(value);
            self_type buffer(static_cast<size_type>(termination-value));
            std::copy(value,termination,buffer.begin());
            buffer.swap(*this);
        }

            /*!
             * @brief Allocates the buffer for a string with at least
             *    \c capacity, but with no characters (\c size() returns 0).
             */
        explicit basic_string ( size_type capacity )
            : myCapacity(capacity), myData(new char_type[myCapacity+1])
        {
            myData[myCapacity] = myData[0] = '\0';
        }

        basic_string ( const self_type& other )
            : myCapacity(0), myData(0)
        {
            self_type buffer(other.capacity());
            std::copy(other.begin(),other.end(),buffer.begin());
            buffer.swap(*this);
        }

        template<typename Traits>
        basic_string ( const std::basic_string<Char, Traits>& other )
            : myCapacity(0), myData(0)
        {
            self_type buffer(other.capacity());
            std::copy(other.begin(),other.end(),buffer.begin());
            buffer.swap(*this);
        }

        basic_string ( const std_string_type& other )
            : myCapacity(0), myData(0)
        {
            self_type buffer(other.capacity());
            std::copy(other.begin(),other.end(),buffer.begin());
            buffer.swap(*this);
        }

            /*!
             * @brief Frees up all acquired resources (memory).
             */
        ~basic_string () {
            delete [] myData;
        }

        /* class methods. */
    private:
            // Returns the first null character.
        template<typename T>
        static T * endof ( T * current )
        {
            if ( current != 0 )
            {
                while ( *current ) {
                    ++current;
                }
            }
            return (current);
        }

        /* methods. */
    public:
            /*!
             * @brief Truncates the string to 0 characters. Does not deallocate
             *    the buffer.
             */
        void clear () throw()
        {
            if ( myData != 0 ) {
                myData[0] = '\0';
            }
        }

            /*!
             * @brief Returns the length of the string, based on where it finds
             *    the first null character.
             *
             * Although this is not constant time, it accounts for greater
             * flexibility (in particular, allowing you to write directly to the
             * buffer).
             */
        size_type length () const throw() {
            return (end()-begin());
        }

            /*!
             * @brief Returns the total size of the buffer.
             */
        size_type capacity () const throw() {
            return (myCapacity);
        }

            /*!
             * @brief Returns a pointer to the first character in the buffer.
             *
             * As this is a write-buffer, this returns a null pointer if no
             * buffer was allocated (like if default constructed).
             *
             * @note Do NOT deallocate this value, or else!
             */
        char_type * data () throw() {
            return (myData);
        }

            /*!
             * @brief Returns a pointer to the first character in the buffer.
             *
             * This is a read only buffer, so if you request this operation on
             * a const string, it will return a buffer with only a null
             * character.
             */
        const char_type * data () const throw()
        {
            static const char_type empty[] = { static_cast<char_type>(0) };
            return ((myData != 0)? myData : empty);
        }

            /*!
             * @brief Returns an iterator to the first element.
             */
        iterator begin () throw() {
            return (data());
        }

            /*!
             * @brief Returns an iterator to the first element.
             */
        const_iterator begin () const throw() {
            return (data());
        }

            /*!
             * @brief Returns an iterator to one-past-the-last element.
             */
        iterator end () throw() {
            return (endof(myData));
        }

            /*!
             * @brief Returns an iterator to one-past-the-last element.
             */
        const_iterator end () const throw() {
            return (endof(myData));
        }

            /*!
             * @brief Ensures that the capacity is at least \c minimum.
             */
        void reserve ( size_type minimum )
        {
            if ((minimum+1) > myCapacity ) {
                self_type other(minimum);
                std::copy(begin(),end(),other.begin());
                other.swap(*this);
            }
        }

            /*!
             * @brief Constant time exchange of buffers.
             */
        void swap ( self_type& other ) throw()
        {
            std::swap(myData,other.myData);
            std::swap(myCapacity,other.myCapacity);
        }

        /* operators. */
    public:
        self_type& operator= ( const self_type& other )
        {
            self_type copy(other);
            copy.swap(*this);
            return (*this);
        }

        self_type& operator= ( const char_type * value )
        {
            const char_type * last = endof(value);
            reserve(last-value);
            std::copy(value,last+1,end());
            return (*this);
        }

        self_type& operator= ( const char * value )
        {
            const char * last = endof(value);
            reserve(last-value);
            std::copy(value,last+1,end());
            return (*this);
        }

        self_type& operator+= ( const self_type& suffix )
        {
            reserve(length()+suffix.length());
            std::copy(suffix.begin(),suffix.end()+1,end());
            return (*this);
        }

        self_type& operator+= ( const char_type * suffix )
        {
            const_iterator last = endof(suffix);
            reserve(length()+(last-suffix));
            std::copy(suffix,last+1,end());
            return (*this);
        }
    };

    typedef basic_string<character> string;
    typedef basic_string<wcharacter> wstring;

    template<typename Char> inline
    void swap ( basic_string<Char>& lhs, basic_string<Char>& rhs )
    {
        lhs.swap(rhs);
    }

    inline
    std::ostream& operator<< ( std::ostream& out, const string& value )
    {
        return (out << reinterpret_cast<const char*>(value.data()));
    }

    inline
    std::wostream& operator<< ( std::wostream& out, const wstring& value )
    {
        return (out << reinterpret_cast<const wchar_t*>(value.data()));
    }

}

#endif /* _sql_string_hpp__ */
