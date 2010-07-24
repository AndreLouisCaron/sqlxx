#!python

import pysql

def create ( connection ):
    statement = pysql.DirectStatement(
        connection, "create table Employee ( name varchar(30), age int )"
        )
    statement.execute()

def list ( connection ):
    statement = pysql.DirectStatement(
        connection, "select * from Employee"
        )
    # ...

def drop ( connection ):
    statement = pysql.DirectStatement(
        connection, "drop table Employee"
        )
    statement.execute()

def main ( arguments ):
    functions = [
        create, list, drop
        ]
    environment = pysql.Environment(pysql.Version.odbc3)
    path = pysql.string(".\\test.sqlite")
    connection = pysql.Driver(
        environment, pysql.SqliteConnectionString(path)
        )
    f = filter(lambda x: x.__name__ == arguments[0], functions)
    if not f:
        raise Exception, "No such function '%s'." % arguments[0]
    f = f[0]
    f(connection)

if __name__ == '__main__':
    import sys
    main(sys.argv[1:])
