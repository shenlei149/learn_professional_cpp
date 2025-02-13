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

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(AllTest EmployeeTest.cc)
target_include_directories(AllTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(AllTest Employee ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

