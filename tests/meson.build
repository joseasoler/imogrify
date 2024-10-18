# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

source_files = ['tests_main.cpp', 'core/build_test.cpp', 'core/markdown_test.cpp']
imogrify_test = executable('imogrify_test', source_files, include_directories : imogrify_core_include, link_with : imogrify_core_lib, dependencies : catch2_dep, install : false)

test('imogrify_unit_tests', imogrify_test)