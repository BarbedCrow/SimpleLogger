# Logger Library

[![CMake](https://github.com/BarbedCrow/SimpleLogger.git/workflows/CMake/badge.svg)](https://github.com/BarbedCrow/SimpleLogger.git/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A minimal C++ logging library built with modern CMake practices. Perfect as a starting point for building production logging solutions.

## Features

- 🚀 **Modern C++17** implementation
- 📦 **CMake Integration** - Supports find_package, add_subdirectory, and FetchContent
- 🔧 **Easy Installation** - System-wide installation with proper CMake config files
- 🌍 **Cross-Platform** - Works on Linux, macOS, and Windows
- 📚 **Well Documented** - Comprehensive usage examples and API documentation

## Quick Start

### Using find_package (Recommended)
```bash
# Install the library
git clone https://github.com/BarbedCrow/SimpleLogger.git.git
cd logger-lib/logger_lib
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make && sudo make install
```

Then in your CMakeLists.txt:
```cmake
find_package(logger_lib REQUIRED)
target_link_libraries(your_app PRIVATE logger::logger_lib)
```

### Using FetchContent
```cmake
include(FetchContent)
FetchContent_Declare(
    logger_lib
    GIT_REPOSITORY https://github.com/BarbedCrow/SimpleLogger.git.git
    GIT_TAG main
)
FetchContent_MakeAvailable(logger_lib)
target_link_libraries(your_app PRIVATE logger_lib)
```

## API Reference

```cpp
#include <logger.hpp>

int main() {
    logger::initialize();           // Initialize the logger
    logger::log("Hello, World!");  // Log a message
    logger::cleanup();             // Cleanup resources
    return 0;
}
```

## Building from Source

```bash
git clone https://github.com/BarbedCrow/SimpleLogger.git.git
cd logger-lib/logger_test_project
mkdir build && cd build
cmake .. && make
./logger_test_project
```

## Project Structure

- `logger_lib/` - The main static library
- `logger_test_project/` - Example usage and tests
- `USAGE.md` - Detailed integration guide

## Requirements

- CMake 3.15+
- C++17 compatible compiler
- Standard build tools (make/ninja)

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with modern CMake best practices
- Designed for easy integration and distribution
