# data type unit tests for sql library.

add_test_program(date)
add_test_program(int32)
add_test_program(int64)
add_test_program(guid)
add_test_program(time)
add_test_program(timestamp)

set(date-test ${CMAKE_CURRENT_BINARY_DIR}/date)
set(int32-test ${CMAKE_CURRENT_BINARY_DIR}/int32)
set(int64-test ${CMAKE_CURRENT_BINARY_DIR}/int64)
set(guid-test ${CMAKE_CURRENT_BINARY_DIR}/guid)
set(time-test ${CMAKE_CURRENT_BINARY_DIR}/time)
set(timestamp-test ${CMAKE_CURRENT_BINARY_DIR}/timestamp)

# TODO: create an sqlite database for testing, then run tests.
