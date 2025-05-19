<<<<<<< HEAD
cmake_minimum_required(VERSION 3.16)

project(PointerBoard VERSION 0.1 LANGUAGES CXX)
=======
cmake_minimum_required(VERSION 3.5)

project(GamePhase VERSION 0.1 LANGUAGES CXX)
>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

<<<<<<< HEAD
set(PROJECT_SOURCES
        main.cpp

        widget.h
        widget.ui
        widget.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PointerBoard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        hexagonitems.h hexagonitems.cpp
        agents.h agents.cpp
        clickablepixmapitem.h clickablepixmapitem.cpp
        agentitem.h agentitem.cpp
        hexagonagents.h hexagonagents.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PointerBoard APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PointerBoard SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PointerBoard
=======
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
>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

<<<<<<< HEAD
target_link_libraries(PointerBoard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PointerBoard)
endif()
set_target_properties(PointerBoard PROPERTIES
=======
target_link_libraries(GamePhase PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GamePhase)
endif()
set_target_properties(GamePhase PROPERTIES
>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
<<<<<<< HEAD
install(TARGETS PointerBoard
=======
install(TARGETS GamePhase
>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
<<<<<<< HEAD
    qt_finalize_executable(PointerBoard)
endif()
=======
    qt_finalize_executable(GamePhase)
endif()

>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
