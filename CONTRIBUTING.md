# Contributing to imogrify

Thank you for being interested on contributing to imogrify! This project follows the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md).

## Questions and bug reports

You can use the [issue tracker](https://github.com/joseasoler/imogrify/issues) to ask questions and report bugs. Please use the search (including closed issues) to see if your entry has been discussed before.

## Contributions

Before submitting pull requests for new features, create an issue on the [tracker](https://github.com/joseasoler/imogrify/issues) to allow discussing and refining the idea before it is implemented.

### Source code contributions

Pull requests are checked with continuous integration, using the ci CMake presets. To perform the same checks locally during development, there are two options:

* Use one of the dev CMake presets supplied by imogrify. They require [installing vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started) and setting the environment variable `VCPKG_ROOT` to its path.

* Enable the following CMake options: `CMAKE_COMPILE_WARNING_AS_ERROR`, `IMOGRIFY_BUILD_CPU_INFORMATION`, `IMOGRIFY_BUILD_MICROBENCHMARKS`, `IMOGRIFY_BUILD_UNIT_TESTS`, `IMOGRIFY_CLANG_TIDY`.

In both cases, [clang-tidy](https://clang.llvm.org/extra/clang-tidy) and [clang-format](https://clang.llvm.org/docs/ClangFormat.html) must be installed.

Make sure to run the unit tests to ensure they are passing. Most of the [style guide](STYLE_GUIDE.md) rules are checked automatically by clang-format and clang-tidy during compilation.

Since CI will check multiple compilers and platforms, it might report additional warnings that did not appear in your compiler and platform of choice.

imogrify uses UTF-8 encoding by default. Check the [UTF-8 Everywhere Manifesto](http://utf8everywhere.org) for details.
