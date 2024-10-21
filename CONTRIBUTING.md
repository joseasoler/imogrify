# Contributing to imogrify

Thank you for being interested on contributing to imogrify! This project follows the [Contributor Covenant Code of Conduct](CODE_OF_CONDUCT.md).

## Questions and bug reports

You can use the [issue tracker](https://github.com/joseasoler/imogrify/issues) to ask questions and report bugs. Please use the search (including closed issues) to see if your entry has been discussed before.

## Contributions

Before submitting a pull request for a new feature, create an issue on the [tracker](https://github.com/joseasoler/imogrify/issues) to allow discussing and refining the idea before it is implemented.

Source code contributions must met the following requirements. All of these criteria are checked by continuous integration.

* Follow the [style guide](STYLE_GUIDE.md).

* Install clang-format. It will automatically emit format warnings during compilation.

* Enable the `IMOGRIFY_BUILD_UNIT_TESTS` CMake option and check that all unit tests are passing.

* Install clang-tidy and enable the `IMOGRIFY_CLANG_TIDY` CMake option to run clang tidy checks when your code is compiled.

* Enable the `CMAKE_COMPILE_WARNING_AS_ERROR` CMake option.
