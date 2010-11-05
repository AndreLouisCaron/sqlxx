#ifndef _sql_hpp__
#define _sql_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

namespace sql {}

#include <sql/Connection.hpp>
#include <sql/ConnectionString.hpp>
#include <sql/Date.hpp>
#include <sql/Diagnostic.hpp>
#include <sql/DirectStatement.hpp>
#include <sql/Driver.hpp>
#include <sql/Environment.hpp>
#include <sql/Guid.hpp>
#include <sql/Handle.hpp>
#include <sql/Numeric.hpp>
#include <sql/PreformattedConnectionString.hpp>
#include <sql/PreparedStatement.hpp>
#include <sql/PreparedUpdate.hpp>
#include <sql/Results.hpp>
#include <sql/Row.hpp>
#include <sql/Statement.hpp>
#include <sql/Status.hpp>
#include <sql/Time.hpp>
#include <sql/Timestamp.hpp>
#include <sql/Version.hpp>

/*!
 * @mainpage
 *
 * @section prelude About this project
 *
 * This project is written and maintained by Andre Caron, whom you can reach at
 * andre.l.caron@gmail.com. The author wishes that as many people as possible
 * will use the software library, which is why it is released under an open
 * source license.
 *
 * @section intro Introduction
 *
 * The SQL standard defines a standard API for the C programming language, but
 * it proves to have notoriously poor undocumentation and shady interfaces full
 * of ackward casts and the like. Moreover, proper management of resources and
 * error handling is hard to validate in the midst of all the bloated function
 * calls.
 *
 * This API aims at providing tools that allow the programmer to focus on the
 * details that matter. Examples include:
 * - the ODBC version should be visible, such as an argument to the SQL
 *   environment's constructor (see sql::Environment::Environment()).
 * - connecting to a database should be a one-liner, as simple as declaring a
 *   sql::Connection variable (see sql::Driver::Driver()).
 * .
 *
 * @section design Design Philosophy
 *
 * @section starting Getting Started
 *
 */

#endif /* _sql_hpp__ */
