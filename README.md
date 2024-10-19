# imogrify

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0) [![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](CODE_OF_CONDUCT.md)

Image conversion tool optimized for processing large batches of files.

## Contributing

imogrify encourages community involvement and contributions. Check the [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) files for details. You can check all contributors in the [contributors list](https://github.com/joseasoler/imogrify/graphs/contributors).

## License

imogrify is licensed under the Mozilla Public License, v. 2.0. See the [LICENSE](LICENSE) file for details. Check the [MPL 2.0 FAQ](https://www.mozilla.org/en-US/MPL/2.0/FAQ) to learn more.

The repository includes third party dependencies as source code in the thirdparty subfolder. Each one of them is under their own license, which is included in their respective folder. 

## Building

Building imogrify requires [Meson](https://mesonbuild.com/) and a [compiler with C++20 support](https://en.cppreference.com/w/cpp/compiler_support#cpp20).

imogrify uses UTF-8 by default. See http://utf8everywhere.org/ for details.

### Dependencies

imogrify requires the following dependencies. If they are not found on the system, Meson will compile wraps instead.

* **[doctest](https://github.com/doctest/doctest)**: Fast C++ testing framework.

* **[fmt](https://fmt.dev/latest/index.html)**: Modern formatting and printing library.

* **[Nowide](https://github.com/boostorg/nowide)**: Provides UTF-8 aware library functions on Windows without requiring to use the Wide API.

## Acknowledgements

Check the [ACKNOWLEDGEMENTS.md](ACKNOWLEDGEMENTS.md) file for details.
