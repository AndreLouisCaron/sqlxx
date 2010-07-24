// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Date.hpp>
#include <iomanip>
#include <ostream>
#include <sstream>

namespace sql {

    Date::operator std::string() const
    {
        std::ostringstream stream;
        stream << (*this);
        return (stream.str());
    }

    Date::operator std::wstring() const
    {
        std::wostringstream stream;
        stream << (*this);
        return (stream.str());
    }

    std::ostream& operator<< ( std::ostream& out, const Date& date )
    {
        const Date::Value& value = date.value();
        out << value.year << '-'
            << std::setfill('0') << std::setw(2) << value.month << '-'
            << std::setfill('0') << std::setw(2) << value.day;
        return (out);
    }

    std::wostream& operator<< ( std::wostream& out, const Date& date )
    {
        const Date::Value& value = date.value();
        out << value.year << L'-'
            << std::setfill(L'0') << std::setw(2) << value.month << L'-'
            << std::setfill(L'0') << std::setw(2) << value.day;
        return (out);
    }

}
