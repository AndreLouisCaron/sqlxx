#ifndef _sql_PreformattedConnectionString_hpp__
#define _sql_PreformattedConnectionString_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <sql/ConnectionString.hpp>
#include <sql/types.hpp>
#include <sql/string.hpp>

namespace sql {

        /*!
         * @brief Connection string that is pre-formated.
         */
    class PreformattedConnectionString :
        public ConnectionString
    {
        /* data. */
    private:
        string myValue;

        /* construction. */
    public:
        explicit PreformattedConnectionString ( const string& value )
            : myValue(value)
        {}

        /* overrides. */
    protected:
        virtual std::ostream& put ( std::ostream& out ) const {
            return (out << myValue);
        }
    };

}

#endif /* _sql_PreformattedConnectionString_hpp__ */
