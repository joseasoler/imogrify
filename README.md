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

### CMake presets

imogrify includes a set of CMake presets intended for use in CI, which can also be used for development. These presets use [vcpkg](https://github.com/microsoft/vcpkg) to retrieve and build the dependencies.

To use these presets locally, you will need to [install vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started) and set the environment variable `VCPKG_ROOT` to its path. It is recommended to install vcpkg in a short path to avoid building issues with some dependencies. Keep in mind that [vcpkg collects telemetry data by default](https://learn.microsoft.com/en-us/vcpkg/about/privacy). It is possible to disable it by setting the `VCPKG_DISABLE_METRICS` environment variable.

### Dependencies

Building imogrify requires the following dependencies.

* **[doctest](https://github.com/doctest/doctest)**: Fast C++ testing framework.

* **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

* **[Magic Enum](https://github.com/Neargye/magic_enum)**: Provides static reflection for enums.

### CMake options

* `CMAKE_COMPILE_WARNING_AS_ERROR`: When this option is enabled, compilers will treat warnings as errors. If `IMOGRIFY_CLANG_TIDY` is enabled, [clang-tidy](https://clang.llvm.org/extra/clang-tidy) will also treat its warnings as errors.
* `IMOGRIFY_BUILD_UNIT_TESTS`: Builds unit tests. Requires the [doctest](https://github.com/doctest/doctest) library. Off by default.
* `IMOGRIFY_CLANG_ALL_WARNINGS`: This option is only available when the [clang](https://clang.llvm.org) compiler is in use. This option enables almost every warning from this compiler, except for a few that cause issues with imogrify. This may trigger unexpected positives when using newer clang versions. Off by default.
* `IMOGRIFY_CLANG_TIDY`: If [clang-tidy](https://clang.llvm.org/extra/clang-tidy) is available, it will be used to analyze the project. Off by default.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
