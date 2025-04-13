#first commit added
cmake_minimum_required(VERSION 3.5)

project(GamePhase VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Add resource file separately
qt_add_resources(GAME_RESOURCES resources.qrc)

set(PROJECT_SOURCES
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    ${GAME_RESOURCES}  # ✅ compiled resource added here
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GamePhase
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        images.qrc
        second.h second.cpp second.ui
        gallery.h gallery.cpp gallery.ui

    )
else()
    if(ANDROID)
        add_library(GamePhase SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(GamePhase
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GamePhase PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GamePhase)
endif()
set_target_properties(GamePhase PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GamePhase
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GamePhase)
endif()

