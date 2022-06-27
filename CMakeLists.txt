cmake_minimum_required(VERSION 3.13)

# update qt variables
message("Qt5_DIR: ${Qt5_DIR}")
set(QT_PREFIX_DIR "${Qt5_DIR}/../..")
message("QT_PREFIX_DIR: ${QT_PREFIX_DIR}")
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})

project(qt_temp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets)

# clang-format
if (NOT DEFINED CLANG_FORMAT_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_FORMAT_BIN
            NAMES clang-format clang-format-12
            HINTS ${CLANG_SEARCH_PATH})
endif()
if ("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(WARNING "couldn't find clang-format.")
else()
    message(STATUS "found clang-format at ${CLANG_FORMAT_BIN}")
endif()

file(GLOB_RECURSE ALL_SOURCE_FILES src/**/*.cpp src/**/*.h src/*.cpp src/*.h)
if(NOT DEFINED NO_CLANG_FORMAT)
    add_custom_target(clang_format
            ${CLANG_FORMAT_BIN}
            ALL
            COMMAND clang-format -style=google -i
            ${ALL_SOURCE_FILES}
    )
    message(STATUS "run clang-format on: ${ALL_SOURCE_FILES}")
endif()

# clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (NOT DEFINED CLANG_TIDY_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_TIDY_BIN
            NAMES clang-tidy clang-tidy-12
            HINTS ${CLANG_SEARCH_PATH})
endif()
if ("${CLANG_TIDY_BIN}" STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(WARNING "couldn't find clang-tidy.")
else()
    message(STATUS "found clang-tidy at ${CLANG_TIDY_BIN}")
endif()

set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_BIN}")

# Add Subdirectory
ADD_SUBDIRECTORY(src ${CMAKE_BINARY_DIR}/bin)
#ADD_SUBDIRECTORY(test ${CMAKE_BINARY_DIR}/test)

