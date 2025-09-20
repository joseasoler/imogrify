# Style guide

Most of the style is enforced by  [.clang-format](https://clang.llvm.org/docs/ClangFormat.html) and [.clang-tidy](https://clang.llvm.org/extra/clang-tidy) files. The following rules must also be followed:

- Private member variables are prefixed by a single underscore.

- Header files use the hpp extension.

- Source files use the cpp extension.

- Use a single tab for indentation.

- Prefer NOLINTNEXTLINE with an explicit diagnostic over NOLINT.
