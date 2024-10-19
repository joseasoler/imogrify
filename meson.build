# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

project('imogrify', 'cpp', version : '0.1.0', license : 'MPL-2.0', license_files : ['LICENSE'],
        default_options : [
            'cpp_std=c++20',
            'warning_level=3'
        ])

# Third party dependencies.
doctest_dep = dependency('doctest', version : '>=2.4.0', fallback : ['doctest', 'doctest_dep'],
                         default_options : ['default_library=static', 'warning_level=0'], include_type : 'system')
fmt_dep = dependency('fmt', version : '>=11.0.0', fallback : ['fmt', 'fmt_dep'],
                     default_options : ['default_library=static', 'warning_level=0'], include_type : 'system')

# Common layers.
subdir('src/core')
# imogrify application.
subdir('src/imogrify')
# Unit testing.
subdir('tests')

if (meson.backend() == 'ninja')
    ninja_program = find_program('ninja')
    if (get_option('test_clang_format'))
        clang_format_program = find_program('clang-format', required : false)
        if (clang_format_program.found())
            test('run_clang_format_checks', ninja_program, verbose : true,
                 args : ['-C', meson.current_build_dir(), 'clang-format-check'])
        endif
    endif
    if (get_option('test_clang_tidy'))
        clang_tidy_program = find_program('clang-tidy', required : false)
        if (clang_tidy_program.found())
            test('run_clang_tidy_checks', ninja_program, verbose : true,
                 args : ['-C', meson.current_build_dir(), 'clang-tidy'])
        endif
    endif
endif

