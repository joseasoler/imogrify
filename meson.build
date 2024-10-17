# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

project('imogrify', 'cpp',
        version : '0.1',
        default_options : ['warning_level=everything',
                           'cpp_std=c++20'])

fmt_dep = dependency('fmt', version : '>=11.0.0', fallback : ['fmt', 'fmt_dep'], default_options : ['default_library=static', 'warning_level=0'], include_type : 'system')

imogrify = executable('imogrify', 'src/app/imogrify.cpp', dependencies : fmt_dep, install : true)

test('basic', imogrify)
