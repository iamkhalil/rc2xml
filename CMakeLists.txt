cmake_minimum_required(VERSION 3.20)
project(rc2xml)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
  option(WARNINGS_AS_ERRORS "Make all warnings into errors" TRUE)
  set(MSVC_WARNINGS /W4)
  set(GCC_WARNINGS -Wall -Wextra -Wpedantic)
  if(WARNING_AS_ERRORS)
    set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
    set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
  endif()

  if(MSVC)
    set(WARNINGS ${MSVC_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS ${GCC_WARNINGS})
  else()
    message("No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${target} PRIVATE ${WARNINGS})
endfunction()

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)

FetchContent_MakeAvailable(fmt)

add_library(internals
  token.hpp
  token.cpp
  scanner.hpp
  scanner.cpp
  ast_printer.hpp
  ast_printer.cpp
  parser.hpp
  parser.cpp
  genxml.hpp
  genxml.cpp
)

target_link_libraries(internals
  PRIVATE
  fmt::fmt
)

enable_warnings(internals)

add_executable(rc2xml
  main.cpp
)

target_link_libraries(rc2xml
  internals
)
