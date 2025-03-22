# Contributing to imogrify

Thank you for being interested on contributing to imogrify! This project follows the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md).

## Questions and bug reports

You can use the [issue tracker](https://github.com/joseasoler/imogrify/issues) to ask questions and report bugs. Please use the search (including closed issues) to see if your entry has been discussed before.

## Contributions

Before submitting a pull request for a new feature, create an issue on the [tracker](https://github.com/joseasoler/imogrify/issues) to allow discussing and refining the idea before it is implemented.

### Source code contributions

Source code contributions must met the following requirements. These criteria are checked by continuous integration.

* clang-format should issue no warnings. If the tool is installed, it will automatically emit format warnings during compilation.

* Recent versions of clang-tidy should not trigger any warnings. Enable the `IMOGRIFY_CLANG_TIDY` CMake option to run clang tidy checks each time your code is compiled.

* Follow the [style guide](STYLE_GUIDE.md). Most but not all of its rules are enforced by clang-format and clang-tidy.

* Compilation should not issue any warnings in supported compilers. Enable the `CMAKE_COMPILE_WARNING_AS_ERROR` CMake option to check this.

* Unit tests should be passing. Enable the `IMOGRIFY_BUILD_UNIT_TESTS` CMake option and run the tests to check this.

* NOLINT should not be used, use NOLINTNEXTLINE instead.

* These conditions must be met for all supported CMake options.

#### Other considerations

imogrify assumes UTF-8 encoding by default. Check the [UTF-8 Everywhere Manifesto](http://utf8everywhere.org) for details.
