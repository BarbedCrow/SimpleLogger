cmake_minimum_required(VERSION 3.15)

project(logger_lib 
    VERSION 1.0.0
    DESCRIPTION "A minimal logging library"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add concurrentqueue library (header-only)
add_library(concurrentqueue INTERFACE)
target_include_directories(concurrentqueue INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../external/concurrentqueue>
    $<INSTALL_INTERFACE:include>
)

# Create the static library
add_library(logger_lib STATIC
    src/logger.cpp
)

# Set C++ standard using target_compile_features
target_compile_features(logger_lib PUBLIC cxx_std_17)

# Link concurrentqueue to logger_lib
target_link_libraries(logger_lib PUBLIC concurrentqueue)

# Configure include directories for build and install
target_include_directories(logger_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Set library properties
set_target_properties(logger_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "logger"
)

# Installation rules for standalone distribution
include(GNUInstallDirs)

# Install the library
install(TARGETS logger_lib concurrentqueue
    EXPORT logger_lib_targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(FILES include/logger.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install concurrentqueue headers
install(DIRECTORY ../external/concurrentqueue/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# Create and install CMake config files for find_package support
install(EXPORT logger_lib_targets
    FILE logger_lib_targets.cmake
    NAMESPACE logger::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/logger_lib
)

# Create config file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/logger_lib_config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/logger_lib_config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/logger_lib
)

# Create version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/logger_lib_config_version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/logger_lib_config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/logger_lib_config_version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/logger_lib
)
