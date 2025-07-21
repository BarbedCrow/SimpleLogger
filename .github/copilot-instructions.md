<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

# C++ CMake Project Instructions

This workspace contains C++ projects using modern CMake practices. When working on this codebase:

## General Guidelines
- Use C++17 standard features and best practices
- Follow modern CMake conventions (3.15+)
- Maintain clear separation between library and application code
- Use proper namespace organization (`logger` namespace for the library)

## Code Style
- Use snake_case for function names and variables
- Use PascalCase for class names
- Include guards should use `#pragma once`
- Maintain consistent indentation (4 spaces)

## CMake Practices
- Use target-based CMake commands (target_link_libraries, target_include_directories)
- Prefer BUILD_INTERFACE and INSTALL_INTERFACE generators
- Set C++ standard using target_compile_features when possible
- Use modern CMake idioms and avoid deprecated functions

## Library Development (logger_lib)
- Keep the library interface minimal and focused
- Provide stub implementations that can be extended later
- Use proper include directory structure (include/ and src/ separation)
- Design for both static and shared library usage

## Test Project Development
- Demonstrate clear usage examples of the library
- Handle errors gracefully
- Provide meaningful output to users
- Keep dependencies minimal
