# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0)

Batch image format conversion tool.

## Contributing

imogrify encourages community involvement and contributions, check [CONTRIBUTING.md](CONTRIBUTING.md) for details. Contributors can be found in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file and the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ) for details.

## Building

Building imogrify requires [CMake](https://cmake.org) 3.25 or newer and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20). It supports the Windows and Linux operative systems.

### CMake options

- `CMAKE_COMPILE_WARNING_AS_ERROR`: Compilers treat warnings as errors. Off by default.
- `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Off by default.
- `IMOGRIFY_CLANG_ALL_WARNINGS`: Enables all [clang](https://clang.llvm.org) compiler warnings, except for some which are already known to cause issues. Should be used only for identifying new warnings on compiler updates. Off by default.
- `IMOGRIFY_CLANG_TIDY`: Analyze the project using [clang-tidy](https://clang.llvm.org/extra/clang-tidy). Warnings will be treated as errors if `CMAKE_COMPILE_WARNING_AS_ERROR` is enabled. Off by default.
- `IMOGRIFY_USE_LIBASSERT`: Implement asserts using [libassert](github.com/jeremy-rifkin/libassert). Off by default.

### Dependencies

Dependencies are retrieved through the `find_package` CMake feature.

- **[Catch2](https://github.com/catchorg/Catch2)**: A modern, C++-native, test framework for unit-tests. Only used if `IMOGRIFY_BUILD_UNIT_TESTS` is enabled.

- **[ConcurrentQueue](https://github.com/cameron314/concurrentqueue)**: An industrial-strength lock-free queue for C++.

- **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

 - **[libassert](github.com/jeremy-rifkin/libassert)**: The most over-engineered C++ assertion library. Only used if `IMOGRIFY_USE_LIBASSERT` is enabled.

#### vcpkg

imogrify has optional [vcpkg](https://github.com/microsoft/vcpkg) support, disabled by default. imogrify uses custom ports for some of its dependencies, which can be found in the cmake/vcpkg/ports subfolder.

### CMake presets

imogrify provides a set of CMake presets used during development.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
