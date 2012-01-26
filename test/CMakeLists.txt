# sql library unit tests.

macro(add_test_program name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} sql odbc32.lib)
  add_dependencies(${name} sql)
endmacro()

add_subdirectory(data-type)
