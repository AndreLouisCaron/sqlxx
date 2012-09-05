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

#include "Time.hpp"
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

    std::ostream& operator<< (std::ostream& stream, const Time& time)
    {
        const Time::Value& value = time.value();
        stream << std::setw(2) << std::setfill('0') << value.hour << ":"
               << std::setw(2) << std::setfill('0') << value.minute << ":"
               << std::setw(2) << std::setfill('0') << value.second;
        return (stream);
    }

    std::wostream& operator<< (std::wostream& stream, const Time& time)
    {
        const Time::Value& value = time.value();
        stream << std::setw(2) << std::setfill(L'0') << value.hour << L':'
               << std::setw(2) << std::setfill(L'0') << value.minute << L':'
               << std::setw(2) << std::setfill(L'0') << value.second;
        return (stream);
    }

}
