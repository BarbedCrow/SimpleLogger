# Logger Library

[![CMake](https://github.com/BarbedCrow/SimpleLogger.git/workflows/CMake%20Build/badge.svg)](https://github.com/BarbedCrow/SimpleLogger.git/actions)
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
git clone https://github.com/BarbedCrow/SimpleLogger.git
cd SimpleLogger/logger_lib
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
    GIT_REPOSITORY https://github.com/BarbedCrow/SimpleLogger.git
    GIT_TAG main
)
FetchContent_MakeAvailable(logger_lib)
target_link_libraries(your_app PRIVATE logger_lib)
```

### Using add_subdirectory
```bash
# Copy logger_lib to your project
cp -r logger_lib /path/to/your/project/
```
In your CMakeLists.txt:
```cmake
add_subdirectory(logger_lib)
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
git clone https://github.com/BarbedCrow/SimpleLogger.git
cd SimpleLogger/logger_test_project
mkdir build && cd build
cmake .. && make
./logger_test_project
```

## Project Structure

- `logger_lib/` - The main static library with CMake integration
- `logger_test_project/` - Example usage and tests  
- `USAGE.md` - Detailed integration guide

## Requirements

- CMake 3.15 or later
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Standard build tools (make, ninja, etc.)
- clang-format (optional, for code formatting)

## Development

### Code Formatting
This project uses clang-format for consistent code styling. To format all source files:

```bash
./format.sh
```

The project includes:
- `.clang-format` - Formatting configuration based on Google style with 4-space indentation
- `format.sh` - Script to format all C++ files in the project
- VS Code settings for automatic formatting on save (local only)

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)  
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Production Ready Features

✅ **Modern CMake** - Uses target-based commands and proper generators  
✅ **Package Support** - Generate CMake config files for find_package()  
✅ **Version Management** - Semantic versioning with compatibility checks  
✅ **Installation** - System-wide installation with proper file layout  
✅ **Cross-platform** - Works on Linux, macOS, and Windows  
✅ **Multiple Integration** - Supports all modern CMake inclusion methods  
✅ **Documentation** - Comprehensive usage examples and API docs  
✅ **CI/CD Ready** - GitHub Actions workflow for automated testing

## Acknowledgments

- Built with modern CMake best practices
- Designed for easy integration and distribution
- Perfect starting point for production logging solutions
