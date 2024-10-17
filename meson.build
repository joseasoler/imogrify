# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

project('imogrify', 'cpp',
        version : '0.1',
        default_options : ['warning_level=everything',
                           'cpp_std=c++20'])

fmt_dependency = dependency('fmt', version : '>=11.0.0')

imogrify = executable('imogrify', 'src/app/imogrify.cpp', dependencies : fmt_dependency, install : true)

test('basic', imogrify)
