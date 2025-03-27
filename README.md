# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0) [![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)

Image conversion tool optimized for batch processing.

## Contributing

imogrify encourages community involvement and contributions, check [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for details. Contributors can be found in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file and the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ) for details.

## Building

imogrify is a cross-platform application supporting the Windows and Linux operative systems, and the x64 and AArch64 CPU architectures. Building imogrify requires [CMake](https://cmake.org) and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20).

* **Clang:** 16 or newer.
* **GCC:** 11 or newer.
* **MSVC:** 19.30 or newer.

Continuous integration checks MacOS platforms as well, but there may be other issues as no further testing is done. Contributions are welcome!

### CMake options

* `CMAKE_COMPILE_WARNING_AS_ERROR`: Compilers treat warnings as errors. Off by default.
* `IMOGRIFY_BUILD_CPU_INFORMATION`: Imogrify can display runtime information about the CPU in use. Off by default.
* `IMOGRIFY_BUILD_MICROBENCHMARKS`: Builds microbenchmarks. Off by default.
* `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Off by default.
* `IMOGRIFY_CLANG_ALL_WARNINGS`: Only available with the [clang](https://clang.llvm.org) compiler. Enables almost every warning from this compiler, except for a few that cause issues with imogrify. This may trigger unexpected positives when using newer clang versions. Off by default.
* `IMOGRIFY_CLANG_TIDY`: Analyze the project using [clang-tidy](https://clang.llvm.org/extra/clang-tidy). Warnings will be treated as errors if `CMAKE_COMPILE_WARNING_AS_ERROR` is enabled. Off by default.

### Dependencies

The following dependencies must be available through the `find_package` CMake feature.

* **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

* **[Highway](https://google.github.io/highway/en/master)**: Provides portable SIMD/vector intrinsics.

* **[libpng](http://www.libpng.org)**: A library implementing an interface for reading and writing PNG (Portable Network Graphics) format files.

* **[tl-expected](https://github.com/TartanLlama/expected):** Single header implementation of `std::expected` with functional-style extensions.

* **[zlib](https://www.zlib.net)**: A free, lossless data-compression library.

With `IMOGRIFY_BUILD_CPU_INFORMATION`:

* **[libcpuid](https://github.com/anrieff/libcpuid)**: Provides CPU identification.

With `IMOGRIFY_BUILD_UNIT_TESTS`:

* **[doctest](https://github.com/doctest/doctest)**: Fast C++ testing framework.

With `IMOGRIFY_BUILD_MICROBENCHMARKS`:

* **[libspng](https://libspng.org)**: Library for reading and writing Portable Network Graphics (PNG) format files.

* **[lodepng](https://lodev.org/lodepng)**: PNG image decoder and encoder, all in one.

* **[nanobench](https://nanobench.ankerl.com)**: A platform independent microbenchmarking library for C++.

### vcpkg support

Dependencies can optionally be retrieved and built using [vcpkg](https://github.com/microsoft/vcpkg). This is disabled by default, but it is enabled by default in the provided CMake presets. vcpkg support in imogrify uses custom triplets and ports found in the `cmake/custom_vcpkg` subfolder.

Using vcpkg enables extra CMake options:

* `IMOGRIFY_VCPKG_USE_ZLIB_NG`: Replaces [zlib](https://www.zlib.net) with **[zlib-ng](https://github.com/zlib-ng/zlib-ng)**. zlib-ng is a zlib data compression library for the next generation systems. [libpng](http://www.libpng.org)** and [libspng](https://libspng.org) will use zlib-ng instead of zlib. On by default.

### CMake presets

imogrify includes a set of CMake presets. ci presets are used for continuous integration, while the dev presets can be used locally for development. More detail about them can be found in the [CONTRIBUTING.md](CONTRIBUTING.md) guide.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
