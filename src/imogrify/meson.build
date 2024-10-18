# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

imogrify = executable('imogrify', 'imogrify.cpp', include_directories : imogrify_core_include, link_with : imogrify_core_lib, dependencies : fmt_dep, install : true)

test('imogrify_is_executable', imogrify)
