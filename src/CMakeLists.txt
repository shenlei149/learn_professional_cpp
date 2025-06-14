cmake_minimum_required(VERSION 3.31)

project(ProfessionalC++)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-fmodules)
add_compile_options(-finput-charset=UTF-8)
add_compile_options(-Wall -Wextra -pedantic -Werror)

if (NOT EXISTS "gcm.cache/std.gcm")
execute_process (
    COMMAND bash -c "g++ -std=c++23 -fmodules -fsearch-include-path bits/std.cc > /dev/null 2>&1"
    OUTPUT_VARIABLE ignored
)
endif()

add_library(Employee Employee.cc)

add_executable(String String.cc)
add_executable(CustomException CustomException.cc)
target_link_libraries(CustomException PRIVATE stdc++exp)

add_subdirectory(test)
add_subdirectory(Spreadsheet)
add_subdirectory(Grid)
add_subdirectory(DirectedGraph)
