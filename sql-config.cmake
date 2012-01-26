# Library configuration file used by dependent projects
# via find_package() built-in directive in "config" mode.

if(NOT DEFINED sql_FOUND)

  # Locate library headers.
  find_path(sql_include_dirs
    NAMES sql.hpp
    PATHS ${sql_DIR}/code
  )

  # Common name for exported library targets.
  set(sql_libraries
    sql
    CACHE INTERNAL "sql library" FORCE
  )

  # Usual "required" et. al. directive logic.
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(
    sql DEFAULT_MSG
    sql_include_dirs
    sql_libraries
  )

  # Add targets to dependent project.
  add_subdirectory(
    ${sql_DIR}
    ${CMAKE_BINARY_DIR}/sql
  )
endif()
