cmake_minimum_required(VERSION 3.3)
set(TARGET metadata_props)
project(${TARGET})

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(FeatureSummary)

find_package(Qt5 REQUIRED COMPONENTS Gui)
find_package(KF5 REQUIRED COMPONENTS KIO I18n Baloo FileMetaData)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")
endif()

kde_enable_exceptions()

add_definitions(-DTRANSLATION_DOMAIN=\"${TARGET}\")
set(SRCS
    util.cpp
    indexer.cpp
    file.cpp
    meta_data_model.cpp
    widget.cpp
    plugin.cpp
)

add_library(${TARGET} MODULE ${SRCS})

target_link_libraries(${TARGET}
    dl
    KF5::KIOWidgets
    KF5::I18n
    KF5::Baloo
    KF5::FileMetaData
    Qt5::Gui
)
kcoreaddons_desktop_to_json(${TARGET} metadata_props.desktop DEFAULT_SERVICE_TYPE)

install(TARGETS ${TARGET} DESTINATION ${PLUGIN_INSTALL_DIR} )
install(FILES metadata_props.desktop DESTINATION ${SERVICES_INSTALL_DIR} )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
