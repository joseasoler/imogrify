# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

compiler = meson.get_compiler('cpp')

dependency_metadata_template = '\t{"@0@","@1@","@2@"},\n'
dependency_metadata = ''
dependency_metadata += dependency_metadata_template.format('fmt', fmt_dep.version(), 'MIT')


conf_data_dict = {
    'PROJECT_NAME' : meson.project_name(),
    'PROJECT_VERSION' : meson.project_version(),
    'PROJECT_LICENSE' : meson.project_license()[0],
    'BUILD_TYPE' : get_option('buildtype'),
    'COMPILER_NAME' : compiler.get_id(),
    'COMPILER_VERSION' : compiler.version(),
    'DEPENDENCY_METADATA' : dependency_metadata
}

imogrify_core_conf_data = configuration_data(conf_data_dict)

configure_file(input : 'build.hpp.in',
               output : 'build.hpp',
               configuration : imogrify_core_conf_data)
