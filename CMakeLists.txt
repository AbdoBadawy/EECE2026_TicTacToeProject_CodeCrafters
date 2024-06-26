cmake_minimum_required(VERSION 3.5)

project(TicTacToe_Project VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#find_package(SQLite3 REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        loginwindow.h
        loginwindow.cpp
        loginwindow.ui
        tictactoeboard.cpp
        tictactoeboard.h
        historypage.h
        historypage.cpp
        historypage.ui
        sqlite3.h
        sqlite3ext.h
        sqlite3.c

        database_interface.cpp
        database_interface.h
        md5.cpp
        md5.h
        signup.cpp
        signup.ui
        signup.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TicTacToe_Project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        signup.h signup.cpp signup.ui
        profile.h profile.cpp profile.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TicTacToe_Project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TicTacToe_Project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TicTacToe_Project
            ${PROJECT_SOURCES} sqlite3.c
        )
    endif()
endif()

#target_link_libraries(TicTacToe_Project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets sqlite3)

target_link_libraries(TicTacToe_Project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(TicTacToe_Project PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(DATABASE_FILE project_database.db)
set(DATABASE_INSTALL_DIR "${CMAKE_BINARY_DIR}")  # Adjust as needed
#this is a test
add_custom_command(
    TARGET TicTacToe_Project
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/${DATABASE_FILE}"
    "${DATABASE_INSTALL_DIR}/${DATABASE_FILE}"
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TicTacToe_Project)
endif()
