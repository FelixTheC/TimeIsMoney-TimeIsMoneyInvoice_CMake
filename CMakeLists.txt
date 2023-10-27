cmake_minimum_required(VERSION 3.5)

project(TimeIsMoneyInvoice_CMake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/felix/Qt/6.5.0/gcc_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(IsLibrary ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

if (IsLibrary)
    set(PROJECT_SOURCES
        invoice.cpp
        invoice.hpp
        invoice.ui
    )
else ()
    link_directories(../TimeIsMoneyDB_CMake/cmake-build-debug)
    include_directories(../TimeIsMoneyDB_CMake)
    set(PROJECT_SOURCES
            main.cpp
            invoice.cpp
            invoice.hpp
            invoice.ui
    )
endif ()

if (IsLibrary)
    qt_add_library(TimeIsMoneyInvoice_CMake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    target_link_libraries(TimeIsMoneyInvoice_CMake
            PRIVATE
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Sql
            Qt${QT_VERSION_MAJOR}::PrintSupport
    )
else ()
    qt_add_executable(TimeIsMoneyInvoice_CMake
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )

    target_link_libraries(TimeIsMoneyInvoice_CMake
            PRIVATE
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Sql
            Qt${QT_VERSION_MAJOR}::PrintSupport
            TimeIsMoneyDB_CMake
    )
endif ()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TimeIsMoneyInvoice_CMake)
endif()

set_target_properties(TimeIsMoneyInvoice_CMake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TimeIsMoneyInvoice_CMake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TimeIsMoneyInvoice_CMake)
endif()
