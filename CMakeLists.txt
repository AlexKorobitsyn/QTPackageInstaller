cmake_minimum_required(VERSION 3.16)

project(PackageInstallerQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES PackageInstallerQT_ru_RU.ts)

set(RESOURCE_FILES resources.qrc)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
        ${RESOURCE_FILES} # <--- ресурсы
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PackageInstallerQT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

else()
    if(ANDROID)
        add_library(PackageInstallerQT SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(PackageInstallerQT
            ${PROJECT_SOURCES}

            interfaces/IPage.h
            pages/namepage.h pages/namepage.cpp
            pages/installpage.h pages/installpage.cpp
            installer/localpackageinstaller.h installer/localpackageinstaller.cpp
            installer/IPackageInstaller.h
        )

        qt5_add_resources(COMPILED_RESOURCES ${RESOURCE_FILES})
        target_sources(PackageInstallerQT PRIVATE ${COMPILED_RESOURCES})
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(PackageInstallerQT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PackageInstallerQT)
endif()
set_target_properties(PackageInstallerQT PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PackageInstallerQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PackageInstallerQT)
endif()
