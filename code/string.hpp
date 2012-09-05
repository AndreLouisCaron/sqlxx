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

    /*!
     * @brief Unintrusive compile-time type information for characters.
     */
    template<typename C> struct char_traits;

    /*!
     * @brief Unintrusive compile-time type information for 8-bit strings.
     */
    template<> struct char_traits<character>
    {
        /*!
         * @brief Native character type.
         */
        typedef char std_char;

        /*!
         * @brief SQL character type.
         */
        typedef ::SQLCHAR sql_char;
    };

    /*!
     * @brief Unintrusive compile-time type information for UTF-16 strings.
     */
    template<> struct char_traits<wcharacter>
    {
        /*!
         * @brief Native character type.
         */
        typedef wchar_t std_char;

        /*!
         * @brief SQL character type.
         */
        typedef ::SQLWCHAR sql_char;
    };

    /*!
     * @brief Replacement for std::string which does not allow to write
     *  directly into it's buffer because it wishes to support optional
     *  copy-on-write semantics.
     */
    template<typename Char>
    class basic_string
    {
        /* nested types. */
    public:
        /*!
         * @brief Character traits for the string.
         *
         * @see char_traits
         */
        typedef char_traits<Char> traits;

        /*!
         * @brief SQL character type for the string.
         */
        typedef typename traits::sql_char sql_char_type;

        /*!
         * @brief Native character type for the string.
         */
        typedef typename traits::std_char std_char_type;

        /*!
         * @brief SQL character type for the string.
         */
        typedef sql_char_type char_type;

        /*!
         * @brief Standard string type equivalent, for compatibility.
         */
        typedef typename std::basic_string<std_char_type> std_string_type;

        /*!
         * @brief Integer type used to compute the length of strings.
         */
        typedef size_t size_type;

        /*!
         * @brief Iterator to character units.
         */
        typedef char_type * iterator;

        /*!
         * @brief Iterator to character units.
         */
        typedef const char_type * const_iterator;


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
         * @param value Pointer to the first character in the null terminated
         *  string.
         *
         * @note Although this is a convenient way to wrap string litterals,
         *  the string is not character encoding aware and it will not
         *  especially account for multi byte character sets, such as UTF-8.
         *
         * @todo Figure out where this is used.  @c wstring should not support
         *  this operation.
         */
        basic_string (const char * value = "")
            : myCapacity(0), myData(0)
        {
            const char *const termination = endof(value);
            self_type buffer(static_cast<size_type>(termination-value));
            *std::copy(value,termination,buffer.begin()) = 0;
            buffer.swap(*this);
        }

        /*!
         * @brief Creates a copy of the given string.
         * @param value Pointer to the first character in the null terminated
         *  string.
         *
         * @note Although this is a convenient way to convert ASCII strings to
         *  other types of characters, this will not account for multi byte
         *  character sets, such as UTF-8.
         */
        basic_string (const sql_char_type * value)
            : myCapacity(0), myData(0)
        {
            const char_type *const termination = endof(value);
            self_type buffer(static_cast<size_type>(termination-value));
            *std::copy(value,termination,buffer.begin()) = 0;
            buffer.swap(*this);
        }

        /*!
         * @brief Allocates the buffer for a string with at least
         *    \c capacity, but with no characters (\c size() returns 0).
         * @param capacity Minimum size of the character buffer, in characeter
         *  units.
         */
        explicit basic_string (size_type capacity)
            : myCapacity(capacity), myData(new char_type[myCapacity+1])
        {
            myData[myCapacity] = myData[0] = '\0';
        }

        /*!
         * @brief Creates a copy of the given string.
         * @param other String whose contents we want to copy.
         */
        basic_string (const self_type& other)
            : myCapacity(0), myData(0)
        {
            self_type buffer(other.capacity());
            *std::copy(other.begin(),other.end(),buffer.begin()) = 0;
            buffer.swap(*this);
        }

        /*!
         * @brief Creates a copy of the given string.
         * @param other String whose contents we want to copy.
         */
        template<typename Traits>
        basic_string (const std::basic_string<Char, Traits>& other)
            : myCapacity(0), myData(0)
        {
            self_type buffer(other.capacity());
            *std::copy(other.begin(),other.end(),buffer.begin()) = 0;
            buffer.swap(*this);
        }

        /*!
         * @brief Creates a copy of the given string.
         * @param other String whose contents we want to copy.
         */
        explicit basic_string (const std_string_type& other)
            : myCapacity(0), myData(0)
        {
            self_type buffer(other.capacity());
            *std::copy(other.begin(),other.end(),buffer.begin()) = 0;
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
        /*!
         * @internal
         * @brief Find a null-terminated string's terminator.
         * @param current Pointer to the first character in the string.
         */
        template<typename T>
        static T * endof (T * current)
        {
            if (current != 0)
            {
                while (*current != 0) {
                    ++current;
                }
            }
            return (current);
        }

        /* methods. */
    public:
        /*!
         * @brief Truncates the string to 0 characters.
         *
         * The buffer is not deallocated and the capactity does not change.
         */
        void clear () throw()
        {
            if (myData != 0) {
                myData[0] = '\0';
            }
        }

        /*!
         * @brief Number of chacaters until the first null terminator.
         *
         * Although this is not constant time, it accounts for greater
         * flexibility (in particular, allowing you to write directly to the
         * buffer).
         *
         * @see size()
         */
        size_type length () const throw() {
            return (end()-begin());
        }

        /*!
         * @brief Number of chacaters until the first null terminator.
         *
         * Although this is not constant time, it accounts for greater
         * flexibility (in particular, allowing you to write directly to the
         * buffer).
         *
         * @see length()
         */
        size_type size () const throw() {
            return (end()-begin());
        }

        /*!
         * @brief Returns the total size of the buffer.
         */
        size_type capacity () const throw() {
            return (myCapacity);
        }

        /*!
         * @brief Access the underlying character buffer.
         * @return A pointer to the first character in the buffer or a null
         *  pointer if the capacity is 0.
         *
         * @warning Do @e not deallocate this value, or else!
         */
        char_type * data () throw() {
            return (myData);
        }

        /*!
         * @brief Access the underlying character buffer.
         * @return A pointer to the first character in the buffer.  This will
         *  never be a null pointer.
         *
         * This is a read only buffer, so if you request this operation on
         * an empty string, it will return a buffer with only a null
         * character.
         *
         * @warning Do @e not deallocate this value, or else!
         */
        const char_type * data () const throw()
        {
            static const char_type empty[] = { static_cast<char_type>(0) };
            return ((myData != 0)? myData : empty);
        }

        /*!
         * @brief Access the underlying character buffer.
         * @return A pointer to the first character in the buffer or a null
         *  pointer if the capacity is 0.
         *
         * @warning Do @e not deallocate this value, or else!
         */
        std_char_type * c_str () throw () {
            return (reinterpret_cast<std_char_type*>(data()));
        }

        /*!
         * @brief Access the underlying character buffer.
         * @return A pointer to the first character in the buffer.  This will
         *  never be a null pointer.
         *
         * @warning Do @e not deallocate this value, or else!
         */
        const std_char_type * c_str () const throw () {
            return (reinterpret_cast<const std_char_type*>(data()));
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
        void reserve (size_type minimum)
        {
            if (minimum > myCapacity) {
                self_type other(minimum);
                *std::copy(begin(),end(),other.begin()) = 0;
                other.swap(*this);
            }
        }

        /*!
         * @brief Constant time exchange of buffers.
         *
         * @see swap()
         */
        void swap (self_type& other) throw()
        {
            std::swap(myData,other.myData);
            std::swap(myCapacity,other.myCapacity);
        }

        /*!
         * @brief Concatenate the range [@a begin, @a end).
         * @param begin Start of the character range to append.
         * @param end End of the character range to append.
         *
         * @see operator+=
         */
        template<typename Iterator>
        void append (Iterator begin, Iterator end)
        {
            reserve(length()+std::distance(begin,end));
            *std::copy(begin,end,this->end()) = 0;
        }

        /*!
         * @brief Replace contents with [@a begin, @a end).
         * @param begin Start of the character range to copy.
         * @param end End of the character range to copy.
         */
        template<typename Iterator>
        void assign (Iterator begin, Iterator end)
        {
            reserve(std::distance(begin,end));
            *std::copy(begin,end,this->begin()) = 0;
        }

        /* operators. */
    public:
        /*!
         * @brief Replace contents with @a other's contents.
         * @param other New contents to copy.
         * @return @c *this, for method chaining.
         *
         * @see assign()
         */
        self_type& operator= (const self_type& other)
        {
            self_type copy(other);
            copy.swap(*this);
            return (*this);
        }

        /*!
         * @brief Replace contents with @a value's contents.
         * @param value New contents to copy.
         * @return @c *this, for method chaining.
         *
         * @see assign()
         */
        self_type& operator= (const sql_char_type * value)
        {
            const char_type * last = endof(value);
            reserve(last-value);
            *std::copy(value,last,end()) = 0;
            return (*this);
        }

        /*!
         * @brief Replace contents with @a value's contents.
         * @param value New contents to copy.
         * @return @c *this, for method chaining.
         *
         * @note Although this is a convenient way to wrap string litterals,
         *  the string is not character encoding aware and it will not
         *  especially account for multi byte character sets, such as UTF-8.
         *
         * @see assign()
         *
         * @todo Figure out where this is used.  @c wstring should not support
         *  this operation.
         */
        self_type& operator= (const char * value)
        {
            const char * last = endof(value);
            reserve(last-value);
            *std::copy(value,last,end()) = 0;
            return (*this);
        }

        /*!
         * @brief Concatenate with @a suffix.
         * @param suffix String to append.
         * @return @c *this, for method chaining.
         *
         * @see append()
         */
        self_type& operator+= (const self_type& suffix)
        {
            reserve(length()+suffix.length());
            *std::copy(suffix.begin(),suffix.end(),end()) = 0;
            return (*this);
        }

        /*!
         * @brief Concatenate with @a suffix.
         * @param suffix String to append.
         * @return @c *this, for method chaining.
         *
         * @see append()
         */
        self_type& operator+= (const char_type * suffix)
        {
            const_iterator last = endof(suffix);
            reserve(length()+(last-suffix));
            *std::copy(suffix,last,end()) = 0;
            return (*this);
        }
    };

    /*!
     * @brief 8-bit unit string, unspecified encoding.
     */
    typedef basic_string<character> string;

    /*!
     * @brief 16-bit unit string, UTF-16.
     */
    typedef basic_string<wcharacter> wstring;

    /*!
     * @brief basic_string<Char>::swap for argument-dependent lookup.
     */
    template<typename Char> inline
    void swap (basic_string<Char>& lhs, basic_string<Char>& rhs)
    {
        lhs.swap(rhs);
    }

    /*!
     * @brief Writes a string to a standard output stream.
     * @param stream Destination output stream.
     * @param value String to write.
     * @return @a stream, for method chaining.
     */
    inline
    std::ostream& operator<< (std::ostream& stream, const string& value)
    {
        return (stream << reinterpret_cast<const char*>(value.data()));
    }

    /*!
     * @brief Writes a string to a standard output stream.
     * @param stream Destination output stream.
     * @param value String to write.
     * @return @a stream, for method chaining.
     */
    inline
    std::wostream& operator<< (std::wostream& stream, const wstring& value)
    {
        return (stream << reinterpret_cast<const wchar_t*>(value.data()));
    }

}

#endif /* _sql_string_hpp__ */
