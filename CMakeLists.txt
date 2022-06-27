cmake_minimum_required(VERSION 3.5)

message("Qt5_DIR: ${Qt5_DIR}")
set(QT_PREFIX_DIR "${Qt5_DIR}/../..")
message("QT_PREFIX_DIR: ${QT_PREFIX_DIR}")
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})

project(qt_temp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(qt_temp
    ${PROJECT_SOURCES}
)

target_link_libraries(qt_temp PRIVATE Qt5::Widgets)

set_target_properties(qt_temp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(WIN32)
    set(QT_BIN "${QT_PREFIX_DIR}/bin")
    message("QT_BIN: ${QT_BIN}")
    add_custom_command(TARGET qt_temp POST_BUILD
            COMMAND windeployqt.exe $<TARGET_FILE:qt_temp>
            WORKING_DIRECTORY ${QT_BIN})
endif()

