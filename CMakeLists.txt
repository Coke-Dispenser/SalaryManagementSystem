cmake_minimum_required(VERSION 3.16)

project(SalaryManagementSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SalaryManagementSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Employee.h
        Employee.cpp
        SalaryManagenment.h
        Month.h
        SalaryManagenment.cpp
        Month.cpp
        createMonthwindow.h createMonthwindow.cpp createMonthwindow.ui
        addEmployeewindow.h addEmployeewindow.cpp addEmployeewindow.ui
        updateemployeewindow.h updateemployeewindow.cpp updateemployeewindow.ui
        deleteemployeewindow.h deleteemployeewindow.cpp deleteemployeewindow.ui
        findemployeewindow.h findemployeewindow.cpp findemployeewindow.ui
        default.qrc
        outputsalarywindow.h outputsalarywindow.cpp outputsalarywindow.ui






    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SalaryManagementSystem APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SalaryManagementSystem SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SalaryManagementSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SalaryManagementSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SalaryManagementSystem)
endif()
set_target_properties(SalaryManagementSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SalaryManagementSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SalaryManagementSystem)
endif()
if(WIN32)
    # 设置Windows图标
    set(ICON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/sms.ico")
    # 创建一个临时的rc文件
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/temp_icon.rc"
        "IDI_ICON1 ICON DISCARDABLE \"${ICON_FILE}\"")
    # 将临时rc文件添加到目标
    target_sources(SalaryManagementSystem PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/temp_icon.rc")
endif()
