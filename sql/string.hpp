#ifndef _sql_string_hpp__
#define _sql_string_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include "types.hpp"
#include <algorithm>
#include <ostream>
#include <string>

namespace sql {

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

        basic_string ( const std::string& other )
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
