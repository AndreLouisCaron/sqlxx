#ifndef _sql_Status_hpp__
#define _sql_Status_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include "types.hpp"
#include "Handle.hpp"
#include <ostream>

namespace sql {

        /*!
         * @brief Generic 5 character SQL status code.
         *
         * The status can be obtained as soon as an error occurs. Note that
         * there can be more than one diagnostic for a given error/status,
         * although it is not clear when or how this happens...
         */
    class Status
    {
        /* class data. */
    public:
        static const Status none;

        /* data. */
    private:
            // Standard 5 characters, plus a null terminator.
        character myValue[6];

        /* construction. */
    public:
            /*!
             * @brief Null status (equivalent to the empty string).
             */
        Status () throw ();

            /*!
             * @brief Creates a status from a 5-character status code.
             *
             * @param value 5-character status code, no terminator required.
             */
        explicit Status ( const character * value ) throw();

            /*!
             * @brief Obtains the 'n'th diagnostic for a given handle.
             *
             * @param culprit Handle to the resource which cause a problem.
             * @param index Identifier for the diagnostic you want. Because
             *    there is usually only one and that is the one you want, the
             *    default is the first. These are numbers from 1, not 0.
             */
        explicit Status ( const Handle& culprit, int16 index = 1 ) throw();

        /* methods. */
    public:
            /*!
             * @brief Obtains the 5-character status code.
             *
             * @return Status code, always null terminated.
             */
        const character * raw () const throw();

            /*!
             * @brief Sets the 5-character status code.
             *
             * @param value 5-character code, no terminator required.
             */
        void raw ( const character * value ) throw();
    };

        /*!
         * @brief Puts the status to a stream.
         */
    std::ostream& operator<< ( std::ostream& out, const Status& status );

}

#endif /* _sql_Status_hpp__ */
