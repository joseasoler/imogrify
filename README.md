<!--
SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
SPDX-License-Identifier: AGPL-3.0-or-later
-->
# imogrify

Batch image format conversion tool.

## Contributing

imogrify encourages community involvement and contributions, check [CONTRIBUTING.md](CONTRIBUTING.md) for details. Contributors can be found in the [contributors list](ToDo).

## License

imogrify is licensed under the GNU Affero General Public License Version 3 or any later version. See the [LICENSE](LICENSES/AGPL-3.0-or-later.txt) file and the [FAQ](https://www.gnu.org/licenses/gpl-faq.html) for details. This project is compliant with version 3.3 of the [REUSE Specification](https://reuse.software/faq/).

## Building

Building imogrify requires [CMake](https://cmake.org) 3.25 or newer and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20). It supports the Windows and Linux operative systems.

### CMake options

- `CMAKE_COMPILE_WARNING_AS_ERROR`: Compilers treat warnings as errors. Off by default.
- `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Off by default.
- `IMOGRIFY_CLANG_FORMAT`: Check code formatting using [clang-format](https://clang.llvm.org/docs/ClangFormat.html). Warnings will be treated as errors if `CMAKE_COMPILE_WARNING_AS_ERROR` is enabled. Off by default.
- `IMOGRIFY_CLANG_TIDY`: Analyze the project using [clang-tidy](https://clang.llvm.org/extra/clang-tidy). Warnings will be treated as errors if `CMAKE_COMPILE_WARNING_AS_ERROR` is enabled. Off by default.
- `IMOGRIFY_CMAKE_VERBOSE`: Show additional information during CMake configuration. Off by default.
- `IMOGRIFY_SHOW_DEBUG_REPORTS`: Display debug reports on release builds. Off by default.
- `IMOGRIFY_USE_LIBCPUID`: Provide runtime information using [libcpuid](https://libcpuid.sourceforge.net/). Off by default.
- `IMOGRIFY_USE_LIBASSERT`: Implement asserts using [libassert](https://github.com/jeremy-rifkin/libassert). Off by default.

### Dependencies

Dependencies are retrieved through the `find_package` CMake feature.

- **[ConcurrentQueue](https://github.com/cameron314/concurrentqueue)**: An industrial-strength lock-free queue for C++.

- **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

* **[tl-expected](https://github.com/TartanLlama/expected):** Single header implementation of `std::expected` with functional-style extensions.

#### Optional dependencies

These are only required if a CMake option is enabled.

- **[Catch2](https://github.com/catchorg/Catch2)**: A modern, C++-native, test framework for unit-tests. `IMOGRIFY_BUILD_UNIT_TESTS`.

- **[libcpuid](https://libcpuid.sourceforge.net/)**: Provides CPU identification. `IMOGRIFY_USE_LIBCPUID`.

- **[libassert](https://github.com/jeremy-rifkin/libassert)**: The most over-engineered C++ assertion library. `IMOGRIFY_USE_LIBASSERT`.

#### vcpkg

imogrify has optional [vcpkg](https://github.com/microsoft/vcpkg) support, disabled by default. imogrify uses custom ports for some of its dependencies, which can be found in the cmake/vcpkg/ports subfolder.

### CMake presets

imogrify provides a set of CMake presets used during development.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
