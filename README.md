# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0) [![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)

Image conversion tool optimized for processing large batches of files.

## Contributing

imogrify encourages community involvement and contributions. Check the [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) files for details. You can check all contributors in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file for details. Check the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ) to learn more.

The repository includes third party dependencies as source code in the thirdparty subfolder. Each one of them is under their own license, which is included in their respective folder. 

## Building

Building imogrify requires [CMake](https://cmake.org) and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20).

* **Clang:** Version 16 or newer.
* **GCC:** Version 11 or newer.
* **MSVC:** Version 19.30 or newer.

### Dependencies

Building imogrify requires the following dependencies. imogrify expects to find them through the standard `find_package` CMake feature.

* **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

* **[libpng](http://www.libpng.org)**: A library implementing an interface for reading and writing PNG (Portable Network Graphics) format files.

* **[Magic Enum](https://github.com/Neargye/magic_enum)**: Provides static reflection for enums.

* **[zlib](https://www.zlib.net)**: A free, lossless data-compression library.

Building with the `IMOGRIFY_BUILD_UNIT_TESTS` CMake option requires the following additional dependency. This dependency is not used by main the imogrify binary.

* **[doctest](https://github.com/doctest/doctest)**: Fast C++ testing framework.

Building with the `IMOGRIFY_BUILD_BENCHMARKS` CMake option enabled requires the following additional dependencies. These dependencies is not used by main the imogrify binary.

* **[nanobench](https://nanobench.ankerl.com)**: A platform independent microbenchmarking library for C++.

* **[libspng](https://libspng.org)**: libspng (simple png) is a C library for reading and writing Portable Network Graphics (PNG) format files with a focus on security and ease of use.

* **[lodepng](https://lodev.org/lodepng)**: LodePNG is a PNG image decoder and encoder, all in one, no dependency or linkage to zlib or libpng required.

#### Included dependencies

The following dependencies are included in the imogrify code base. Each one of them has its own COPYING or LICENSE file.

* **[tl-expected](https://github.com/TartanLlama/expected):** Single header implementation of `std::expected` with functional-style extensions.

### CMake options

* `CMAKE_COMPILE_WARNING_AS_ERROR`: When this option is enabled, compilers will treat warnings as errors. If `IMOGRIFY_CLANG_TIDY` is enabled, [clang-tidy](https://clang.llvm.org/extra/clang-tidy) will also treat its warnings as errors.
* `IMOGRIFY_BUILD_BENCHMARKS`: Builds benchmarks. Requires the [nanobench](https://nanobench.ankerl.com) library. Off by default.
* `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Requires the [doctest](https://github.com/doctest/doctest) library. Off by default.
* `IMOGRIFY_CLANG_ALL_WARNINGS`: This option is only available when the [clang](https://clang.llvm.org) compiler is in use. This option enables almost every warning from this compiler, except for a few that cause issues with imogrify. This may trigger unexpected positives when using newer clang versions. Off by default.
* `IMOGRIFY_CLANG_TIDY`: If [clang-tidy](https://clang.llvm.org/extra/clang-tidy) is available, it will be used to analyze the project. Off by default.

### vcpkg support

Alternatively, imogrify can be built using [vcpkg](https://github.com/microsoft/vcpkg) to retrieve dependencies. The CMake presets found in the `CMakePresets.json` file are used for continuous integration, but they can also be used for development. 

To use these presets locally, you will need to [install vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started) and set the environment variable `VCPKG_ROOT` to its path. It is recommended to install vcpkg in a short path to avoid building issues with some dependencies. Keep in mind that [vcpkg collects telemetry data by default](https://learn.microsoft.com/en-us/vcpkg/about/privacy). It is possible to disable it by setting the `VCPKG_DISABLE_METRICS` environment variable.

vcpkg builds replace zlib with **[zlib-ng](https://github.com/zlib-ng/zlib-ng)**. zlib-ng is a zlib data compression library for the next generation systems.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
