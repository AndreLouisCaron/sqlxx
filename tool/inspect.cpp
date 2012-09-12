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

#include "tool-program.hpp"

namespace {

    int run (sql::Connection& connection, int argc, char ** argv)
    {
        { sql::Catalogs catalogs(connection);
          sql::Results results(catalogs);
          std::cout
              << "Max catalog name length: "
              << connection.max_catalog_name_size() << "."
              << std::endl;
          sql::string catalog(connection.max_catalog_name_size());
          while ((results >> sql::row) && (results >> catalog))
          {
              std::cout
                  << "Catalog: '" << catalog << "'."
                  << std::endl;
          }
        }

        { sql::Schemas schemas(connection);
          sql::Results results(schemas);
          std::cout
              << "Max schema name length: "
              << connection.max_schema_name_size() << "."
              << std::endl;
          sql::string schema(connection.max_schema_name_size());
          while ((results >> sql::row) &&
                 (results >> sql::skip) &&
                 (results >> schema))
          {
              std::cout
                  << "Schema: '" << schema << "'."
                  << std::endl;
          }
        }

        { sql::TableTypes types(connection);
          sql::Results results(types);
          std::cout
              << "Max table name length: "
              << connection.max_table_name_size() << "."
              << std::endl;
          sql::string type(connection.max_table_name_size());
          while ((results >> sql::row) &&
                 (results >> sql::skip) &&
                 (results >> sql::skip) &&
                 (results >> sql::skip) &&
                 (results >> type))
          {
              std::cout
                  << "Table type: '" << type << "'."
                  << std::endl;
          }
        }

        { sql::Tables tables(connection);
          sql::Results results(tables);
          std::cout
              << "Max table name length: "
              << connection.max_table_name_size() << "."
              << std::endl;
          sql::string table(connection.max_table_name_size());
          while ((results >> sql::row) &&
                 (results >> sql::skip) &&
                 (results >> sql::skip) &&
                 (results >> table))
          {
              std::cout
                  << "Table: '" << table << "'."
                  << std::endl;
              { sql::PrimaryKeys keys(connection, table);
                sql::Results results(keys);
                sql::string pk_column(256);
                while ((results >> sql::row) &&
                       (results >> sql::skip) && // catalog name.
                       (results >> sql::skip) && // schema name.
                       (results >> sql::skip) && // table name.
                       (results >> pk_column))
                {
                    std::cout
                        << "  pk: '" << pk_column << "'."
                        << std::endl;
                }
              }
              { sql::ForeignKeys keys(connection, table);
                sql::Results results(keys);
                sql::string fk_table(256);
                sql::string fk_column(256);
                while ((results >> sql::row) &&
                       (results >> sql::skip) && // catalog name.
                       (results >> sql::skip) && // schema name.
                       (results >> fk_table) &&
                       (results >> fk_column))
                {
                    std::cout
                        << "  fk: '" << fk_table << "'@'" << fk_column << "'."
                        << std::endl;
                }
              }
          }
        }

        return (EXIT_SUCCESS);
    }

}

#include "tool-program.cpp"
