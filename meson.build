# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

project('imogrify', 'cpp', version : '0.1', license : 'MPL-2.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

# Third party dependencies.
fmt_dep = dependency('fmt', version : '>=11.0.0', fallback : ['fmt', 'fmt_dep'],
                     default_options : ['default_library=static', 'warning_level=0'], include_type : 'system')

subdir('src/core')
subdir('src/app')
