cmake_minimum_required(VERSION 3.5)

project(Ecologia VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

message(STATUS "Found Qt version: ${Qt6_VERSION}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Ecologia
        MANUAL_FINALIZATION
        src/App/api.cpp
        src/App/api.hpp
        src/UI/First/First.cpp
        src/UI/First/First.hpp
        src/UI/Metodichka/Metodichka.cpp
        src/UI/Metodichka/Metodichka.hpp
        src/UI/Second/Second.cpp
        src/UI/Second/Second.hpp
        src/UI/CMainWindow.cpp
        src/UI/CMainWindow.h
        src/main.cpp
    )
else()
    if(ANDROID)
        add_library(Ecologia SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Ecologia
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Ecologia PRIVATE 
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Настройки для macOS и iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Ecologia)
endif()
set_target_properties(Ecologia PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Ecologia
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Ecologia)
endif()