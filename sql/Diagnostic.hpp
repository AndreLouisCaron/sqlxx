#ifndef _sql_Diagnostic_hpp__
#define _sql_Diagnostic_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/types.hpp>
#include <sql/Handle.hpp>
#include <sql/Status.hpp>

namespace sql {

        /*!
         * @brief SQL related error.
         *
         * When an error related with SQL occurs, an exception of this type
         * occurs to signal what the error is. It is meant to signal the
         * user about failed transactions in general.
         */
    class Diagnostic
    {
        /* class data. */
    private:
            // Do not dynamically allocate memory to avoid possible memory
            // allocation failure (in particular throwing of std::bad_alloc)
            // during exception processing: this would crash the program!
        static const unsigned int MessageLength = 128;

        /* members. */
    private:
        Status myStatus;
        character myMessage[MessageLength];

        /* construction. */
    public:
            /*!
             * @brief Reads Diagnostics for an error on a given Handle.
             */
        Diagnostic ( const Handle& culprit ) throw();

            /*!
             * @brief Copies \c other's error code.
             *
             * @param other Object whose SQL error code is to be duplicated.
             */
        Diagnostic ( const Diagnostic& other ) throw ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the diagnostic's 5-character status code.
             */
        const Status& status () const throw();

            /*!
             * @brief Obtains the description as an ASCIIZ string.
             * @return An ASCIIZ string containing a description message.
             */
        const character * what () const throw();

        /* operators. */
    public:
            /*!
             * @brief Copies \c other's error code.
             *
             * Note : although assigning to exceptions is uncommon, this
             * is here for the sake of consistency.
             *
             * @param other Object whose SQL error code is to be duplicated.
             */
        Diagnostic& operator= ( const Diagnostic& other ) throw();
    };

        /*!
         * @brief Puts the error diagnostic to a stream.
         */
    std::ostream& operator<< (
        std::ostream& out, const Diagnostic& diagnostic
        );

}

#endif /* _sql_Diagnostic_hpp__ */
