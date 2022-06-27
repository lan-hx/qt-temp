cmake_minimum_required(VERSION 3.13)

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
        MACOSX_BUNDLE_GUI_IDENTIFIER huaji
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

if(WIN32)
    set(QT_DEPLOY_EXE "${QT_PREFIX_DIR}/bin/windeployqt.exe")
    message("QT_DEPLOY_EXE: ${QT_DEPLOY_EXE}")
    add_custom_command(TARGET qt_temp POST_BUILD
            COMMAND ${QT_DEPLOY_EXE} $<TARGET_FILE:qt_temp>)
endif()