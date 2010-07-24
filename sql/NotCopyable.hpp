#ifndef _sql_NotCopyable_hpp__
#define _sql_NotCopyable_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

namespace sql {

        /*!
         * @brief Inherit from this class to prevent copying and assignment.
         */
    class NotCopyable
    {
        /* construction. */
    protected:
        NotCopyable () {
        }

    private:
        NotCopyable ( const NotCopyable& );

        /* operators. */
    private:
        NotCopyable& operator= ( const NotCopyable& );
    };

}

#endif /* _sql_NotCopyable_hpp__ */
