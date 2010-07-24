// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <boost/python.hpp>
#include <sql.hpp>
#include <sql/firebird.hpp>
#include <sql/mysql.hpp>
#include <sql/sqlite.hpp>
#include <sstream>

    // Exception translators.
namespace {

    void translate ( const sql::Environment::Failure& )
    {
        static const char message[]
            = "Could not allocate SQL/ODBC environment.";
        PyErr_SetString(PyExc_RuntimeError, message);
    }

    void translate ( const sql::Diagnostic& diagnostic )
    {
        std::ostringstream message;
        message << diagnostic;
        PyErr_SetString(PyExc_RuntimeError, message.str().c_str());
    }

}

BOOST_PYTHON_MODULE(pysql)
{
        // Export general library exceptions.
    boost::python::register_exception_translator
        < sql::Environment::Failure >(
            (void(*)(const sql::Environment::Failure&))translate
            );
    boost::python::register_exception_translator
        < sql::Diagnostic >(
            (void(*)(const sql::Diagnostic&))translate
            );

        // Export version class.
    boost::python::class_< sql::Version > Version
        ( "Version", boost::python::no_init );

        // Define version class constants.
    Version
        .def_readonly( "odbc2", sql::Version::odbc2 )
        .def_readonly( "odbc3", sql::Version::odbc3 )
        ;

        // Export environment class.
    boost::python::class_< sql::Environment, boost::noncopyable > Environment
        ( "Environment", boost::python::init<const sql::Version&>() );
    Environment
        .def( "commit", &sql::Environment::commit )
        .def( "rollback", &sql::Environment::rollback )
        ;

        // Export connection class.
    boost::python::class_< sql::Connection, boost::noncopyable > Connection
        ( "Connection", boost::python::no_init );
    Connection
        .def( "commit", &sql::Connection::commit )
        .def( "rollback", &sql::Connection::rollback )
        ;

        // Export statement class.
    boost::python::class_< sql::Statement, boost::noncopyable > Statement
        ( "Statement", boost::python::no_init );
    Statement
        .def( "cancel", &sql::Statement::cancel )
        .def( "execute", &sql::Statement::execute )
        ;
    boost::python::class_<
        sql::DirectStatement, boost::noncopyable,
        boost::python::bases< sql::Statement >
        > DirectStatement
        ( "DirectStatement",
          boost::python::init< sql::Connection&, const std::string& >() );
    boost::python::class_<
        sql::PreparedStatement, boost::noncopyable,
        boost::python::bases< sql::Statement >
        > PreparedStatement
        ( "PreparedStatement",
          boost::python::init< sql::Connection&, const std::string& >() );

        // Export connection string class.
    boost::python::class_< sql::ConnectionString, boost::noncopyable >
        ConnectionString ( "ConnectionString", boost::python::no_init );
    ConnectionString
        .def( "__str__", &sql::ConnectionString::operator std::string )
        ;

        // Export pre-formatted connection string class.
    boost::python::class_<
        sql::PreformattedConnectionString, boost::noncopyable,
        boost::python::bases< sql::ConnectionString >
    >
    PreformattedConnectionString (
        "PreformattedConnectionString",
        boost::python::init<const sql::string&>()
        );
    PreformattedConnectionString
        .def( boost::python::init<const char*>() )
        ;

        // Export driver connection class.
    boost::python::class_<
        sql::Driver, boost::noncopyable,
        boost::python::bases< sql::Connection >
    > driver (
        "Driver",
        boost::python::init<sql::Environment&,const sql::ConnectionString&>()
        );

        // Export string class.
    boost::python::class_< sql::string > string (
        "string",
        boost::python::init<const char*>()
        );

        // Export wide character string class.
    boost::python::class_< sql::wstring > wstring (
        "wstring",
        boost::python::init<const wchar_t*>()
        );

        // Export guid class.
    boost::python::class_< sql::Guid > guid (
        "Guid",
        boost::python::init<>()
        );

        // Export time class.
    boost::python::class_< sql::Date > date (
        "Date",
        boost::python::init<>()
        );

        // Export date class.
    boost::python::class_< sql::Time > time (
        "Time",
        boost::python::init<>()
        );

        // Export firebird connection string class.
    boost::python::class_<
        sql::firebird::ConnectionString,
        boost::python::bases< sql::ConnectionString >
        >
        firebirdconnection (
            "FirebirdConnectionString",
            boost::python::init<
                const sql::string&,
                const sql::string&,
                const sql::string&
            >()
        );

        // Export sqlite connection string class.
    boost::python::class_<
        sql::sqlite::ConnectionString,
        boost::python::bases< sql::ConnectionString >
        >
        sqliteconnection (
            "SqliteConnectionString",
            boost::python::init<const sql::string&>()
            );

}
