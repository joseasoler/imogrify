# Contributing to imogrify

Thank you for your interest on contributing!

## Questions and bug reports

You can use the [issue tracker](https://github.com/joseasoler/imogrify/issues) to ask questions and report bugs. Please use the search (including closed issues) to see if your entry has been discussed before.

## Contributions

Create an issue on the [tracker](https://github.com/joseasoler/imogrify/issues) before submitting pull requests for new features, to allow discussing and refining the idea before it is implemented.

### Source code contributions

- Check that compilers report no warnings by enabling the `CMAKE_COMPILE_WARNING_AS_ERROR` CMake option.

- Make sure that [clang-tidy](https://clang.llvm.org/extra/clang-tidy) and [clang-format](https://clang.llvm.org/docs/ClangFormat.html) are enabled and report no issues.

- Unit tests should be upgraded as needed and run successfully.

- imogrify uses UTF-8 encoding by default. Check the [UTF-8 Everywhere Manifesto](http://utf8everywhere.org) for details.
