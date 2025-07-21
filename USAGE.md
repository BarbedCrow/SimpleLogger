# Using logger_lib in Your Project

The logger_lib is designed to be easily integrated into any CMake-based C++ project. Here are the different ways you can use it:

## Method 1: Using find_package() (Recommended for installed library)

After installing the library system-wide, you can use it in your CMake project:

```cmake
cmake_minimum_required(VERSION 3.15)
project(my_project)

# Find the installed logger library
find_package(logger_lib REQUIRED)

# Create your executable
add_executable(my_app main.cpp)

# Link against the logger library
target_link_libraries(my_app PRIVATE logger::logger_lib)
target_compile_features(my_app PRIVATE cxx_std_17)
```

## Method 2: Using add_subdirectory() (For source inclusion)

If you include the logger_lib source in your project:

```cmake
cmake_minimum_required(VERSION 3.15)
project(my_project)

# Add logger_lib as subdirectory
add_subdirectory(path/to/logger_lib)

# Create your executable
add_executable(my_app main.cpp)

# Link against the logger library
target_link_libraries(my_app PRIVATE logger_lib)
target_compile_features(my_app PRIVATE cxx_std_17)
```

## Method 3: Using FetchContent (For remote repositories)

```cmake
cmake_minimum_required(VERSION 3.15)
project(my_project)

include(FetchContent)

FetchContent_Declare(
    logger_lib
    GIT_REPOSITORY https://github.com/your-username/logger_lib.git
    GIT_TAG main
)

FetchContent_MakeAvailable(logger_lib)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE logger_lib)
target_compile_features(my_app PRIVATE cxx_std_17)
```

## Example Usage in Code

```cpp
#include <logger.hpp>

int main() {
    logger::initialize();
    logger::log("Hello from my application!");
    logger::log("Logger is working perfectly!");
    logger::cleanup();
    return 0;
}
```

## Installation

To install the library system-wide:

```bash
cd logger_lib
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
```

For a custom installation directory:

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/your/install/dir
make
make install
```

## Integration Examples

### Simple Application Structure
```
my_project/
├── CMakeLists.txt
├── main.cpp
└── logger_lib/          # If using as subdirectory
    ├── CMakeLists.txt
    ├── include/
    └── src/
```

### Using with Git Submodule
```bash
# Add logger_lib as a git submodule
git submodule add https://github.com/your-username/logger_lib.git external/logger_lib
git submodule update --init --recursive
```

Then in your CMakeLists.txt:
```cmake
add_subdirectory(external/logger_lib)
target_link_libraries(my_app PRIVATE logger_lib)
```

## Requirements

- CMake 3.15 or later
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Standard build tools (make, ninja, etc.)

## Troubleshooting

### find_package() fails
- Ensure the library is installed correctly
- Check CMAKE_PREFIX_PATH includes the installation directory
- Verify CMake can find the config files

### Include errors
- Make sure you're including `logger.hpp` (not `logger.h`)
- Verify the include directories are set correctly in your CMakeLists.txt

### Linking errors
- Ensure you're linking against the correct target (`logger_lib` or `logger::logger_lib`)
- Check that C++17 is enabled in your project
