# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0) [![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)

An image conversion tool optimized for batch processing.

## Contributing

imogrify encourages community involvement and contributions. Check the [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) files for details. You can check all contributors in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file for details. Check the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ) to learn more.

## Building

Building imogrify requires [CMake](https://cmake.org) and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20).

* **Clang:** Version 16 or newer.
* **GCC:** Version 11 or newer.
* **MSVC:** Version 19.30 or newer.

### CMake options

* `CMAKE_COMPILE_WARNING_AS_ERROR`: Compilers will treat warnings as errors. If `IMOGRIFY_CLANG_TIDY` is enabled, [clang-tidy](https://clang.llvm.org/extra/clang-tidy) will also treat its warnings as errors.
* `IMOGRIFY_BUILD_CPU_INFORMATION`: Imogrify can display runtime information about the CPU in use. Off by default.
* `IMOGRIFY_BUILD_MICROBENCHMARKS`: Builds microbenchmarks. Off by default.
* `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Off by default.
* `IMOGRIFY_CLANG_ALL_WARNINGS`: Only available with the [clang](https://clang.llvm.org) compiler. Enables almost every warning from this compiler, except for a few that cause issues with imogrify. This may trigger unexpected positives when using newer clang versions. Off by default.
* `IMOGRIFY_CLANG_TIDY`: If a [clang-tidy](https://clang.llvm.org/extra/clang-tidy) binary can be found, it will be used to analyze the project. Off by default.
* `IMOGRIFY_USE_LIBASSERT`: When enabled, imogrify will use [libassert](https://github.com/jeremy-rifkin/libassert) for improved assertions. Off by default.

### Dependencies

Building imogrify requires the following dependencies to be available through the `find_package` CMake feature.

* **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

* **[Highway](https://google.github.io/highway/en/master)**: Provides portable SIMD/vector intrinsics and aligned memory allocation utilities.

* **[libpng](http://www.libpng.org)**: A library implementing an interface for reading and writing PNG (Portable Network Graphics) format files.

* **[tl-expected](https://github.com/TartanLlama/expected):** Single header implementation of `std::expected` with functional-style extensions.

* **[zlib](https://www.zlib.net)**: A free, lossless data-compression library.

With the `IMOGRIFY_BUILD_CPU_INFORMATION` CMake option:

* **[libcpuid](https://github.com/anrieff/libcpuid)**: Provides CPU identification.

With the `IMOGRIFY_BUILD_UNIT_TESTS` CMake option. This dependency is not used by the main imogrify binary.

* **[doctest](https://github.com/doctest/doctest)**: Fast C++ testing framework.

With the `IMOGRIFY_BUILD_MICROBENCHMARKS` CMake option. These dependencies are not used by the main imogrify binary.

* **[nanobench](https://nanobench.ankerl.com)**: A platform independent microbenchmarking library for C++.

* **[libspng](https://libspng.org)**: libspng (simple png) is a C library for reading and writing Portable Network Graphics (PNG) format files with a focus on security and ease of use.

* **[lodepng](https://lodev.org/lodepng)**: LodePNG is a PNG image decoder and encoder, all in one, no dependency or linkage to zlib or libpng required.

With the `IMOGRIFY_USE_LIBASSERT` CMake option:

* **[libassert](https://github.com/jeremy-rifkin/libassert)**: The most over-engineered C++ assertion library.

### vcpkg support

imogrify can be built using [vcpkg](https://github.com/microsoft/vcpkg) to retrieve dependencies. vcpkg support in imogrify uses custom triplets and ports found in the `cmake/custom_vcpkg` subfolder.

When using vcpkg, the following CMake options are also available:

* `IMOGRIFY_VCPKG_USE_ZLIB_NG`: Replaces [zlib](https://www.zlib.net) with **[zlib-ng](https://github.com/zlib-ng/zlib-ng)**. zlib-ng is a zlib data compression library for the next generation systems. [libpng](http://www.libpng.org)** and [libspng](https://libspng.org) will also use zlib-ng. On by default.

vcpkg will enable the following CMake options: `IMOGRIFY_BUILD_CPU_INFORMATION`, `IMOGRIFY_BUILD_MICROBENCHMARKS`, `IMOGRIFY_BUILD_UNIT_TESTS`, `IMOGRIFY_USE_LIBASSERT`.

### CMake presets

imogrify includes a set of CMake presets. ci presets are intended for continuous integration, and dev presets are for development.

These presets require [installing vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started) and setting the environment variable `VCPKG_ROOT` to its path. It is recommended to install vcpkg in a short path to avoid building issues with some dependencies.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
