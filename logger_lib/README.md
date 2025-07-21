# Logger Library

A minimal C++ logging library built with modern CMake practices.

## Overview

This is a stub implementation of a logging library that provides a basic interface for logging functionality. The library is designed to be extended with actual logging implementation in the future and can be easily integrated into any CMake-based C++ project.

## Features

- Modern C++17 implementation
- CMake-based build system (CMake 3.15+)
- Static library compilation
- Clean namespace organization (`logger` namespace)
- Header-only interface with implementation separation
- Multiple integration methods (find_package, add_subdirectory, FetchContent)
- Proper CMake config files for easy distribution
- Cross-platform compatibility

## Quick Start

### Building the Library

```bash
mkdir build
cd build
cmake ..
make
```

### Installing System-wide

```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
```

## API Reference

The library provides the following functions in the `logger` namespace:

```cpp
namespace logger {
    void initialize();           // Initialize the logger
    void log(const char* message); // Log a message
    void cleanup();             // Cleanup the logger
}
```

## Integration

### Method 1: find_package() (Recommended)

After installation, use in your CMakeLists.txt:

```cmake
find_package(logger_lib REQUIRED)
target_link_libraries(your_target PRIVATE logger::logger_lib)
```

### Method 2: add_subdirectory()

Include as subdirectory:

```cmake
add_subdirectory(path/to/logger_lib)
target_link_libraries(your_target PRIVATE logger_lib)
```

### Method 3: FetchContent

For remote inclusion:

```cmake
include(FetchContent)
FetchContent_Declare(logger_lib GIT_REPOSITORY <repo_url>)
FetchContent_MakeAvailable(logger_lib)
target_link_libraries(your_target PRIVATE logger_lib)
```

## Usage Example

```cpp
#include <logger.hpp>

int main() {
    logger::initialize();
    logger::log("Application started");
    logger::log("Processing data...");
    logger::cleanup();
    return 0;
}
```

## Project Structure

```
logger_lib/
├── CMakeLists.txt           # Main CMake configuration
├── cmake/
│   └── logger_lib_config.cmake.in  # CMake config template
├── include/
│   └── logger.hpp           # Public header
├── src/
│   └── logger.cpp           # Implementation
└── README.md               # This file
```

## Requirements

- CMake 3.15 or later
- C++17 compatible compiler
- Standard build tools (make, ninja, etc.)

## Distribution

The library generates proper CMake config files that support:
- Version checking
- Dependency resolution
- Target namespace (`logger::logger_lib`)
- Cross-platform installation

For detailed integration examples, see the [USAGE.md](../USAGE.md) file in the workspace root.
