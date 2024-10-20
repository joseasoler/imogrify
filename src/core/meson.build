# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

subdir('include/imfy')

imogrify_core_include = include_directories('include')
imogrify_core_dependencies = [fmt_dep, magic_enum_dep]
imogrify_core_lib = library('imogrify_core', 'markdown.cpp', include_directories : imogrify_core_include, dependencies : imogrify_core_dependencies)
