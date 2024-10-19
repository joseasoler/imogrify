# Style guide

Code formatting is handled by the rules set in the [.clang-format](https://clang.llvm.org/docs/ClangFormat.html) and [.clang-tidy](https://clang.llvm.org/extra/clang-tidy) files. Besides the rules described in those files, there are some additional points to keep in mind:

* Private member variables must be prefixed by a single underscore (_).

* Header files must use the hpp extension.

* Source files must use the cpp extension.

* The project uses a single tab for indentation.

## Tooling

When clang-format and clang-tidy are installed and the Ninja backend is in use, Meson will enable additional targets that can check and fix the style of the project.

### Checking format errors

These checks will be performed automatically if the `test_clang_format` and `test_clang_tidy` Meson options are enabled. These checks will be performed by GitHub actions on pull requests.

* `ninja -C buildDir clang-format-check`

* `ninja -C buildDir clang-tidy`

### Fixing format errors

These can be used manually to fix issues during development.

* `ninja -C buildDir clang-format`

* `ninja -C buildDir clang-tidy-fix`

