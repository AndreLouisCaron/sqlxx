// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <sql/Time.hpp>
#include <iomanip>
#include <ostream>
#include <sstream>

namespace sql {

    Time::operator std::string() const
    {
        std::ostringstream stream;
        stream << (*this);
        return (stream.str());
    }

    Time::operator std::wstring() const
    {
        std::wostringstream stream;
        stream << (*this);
        return (stream.str());
    }

    std::ostream& operator<< ( std::ostream& out, const Time& time )
    {
        const Time::Value& value = time.value();
        out << std::setw(2) << std::setfill('0') << value.hour << ":"
            << std::setw(2) << std::setfill('0') << value.minute << ":"
            << std::setw(2) << std::setfill('0') << value.second;
        return (out);
    }

    std::wostream& operator<< ( std::wostream& out, const Time& time )
    {
        const Time::Value& value = time.value();
        out << std::setw(2) << std::setfill(L'0') << value.hour << L':'
            << std::setw(2) << std::setfill(L'0') << value.minute << L':'
            << std::setw(2) << std::setfill(L'0') << value.second;
        return (out);
    }

}
