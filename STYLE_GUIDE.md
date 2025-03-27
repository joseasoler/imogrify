# Style guide

Code formatting is handled by the rules set in the [.clang-format](https://clang.llvm.org/docs/ClangFormat.html) and [.clang-tidy](https://clang.llvm.org/extra/clang-tidy) files. Besides the rules described in those files, there are some additional points to keep in mind:

* Private member variables must be prefixed by a single underscore (_).

* Header files must use the hpp extension.

* Source files must use the cpp extension.

* The project uses a single tab for indentation.

* Prefer NOLINTNEXTLINE over NOLINT.
