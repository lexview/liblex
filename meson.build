project('liblex', 'c', version: '1.0')

liblex_sources = [
    'src/parser.c',
]

inc_dir = include_directories('include')

liblex = static_library('lex', liblex_sources,
        include_directories: [ inc_dir ],
    )

test('Font', executable('01_liblex_font', 'test/01_liblex_font.c'))

liblex_dep = declare_dependency(
        link_with : liblex,
        include_directories : [ inc_dir ],
    )

executable('example1', 'example/example1.c',
        dependencies: [ liblex_dep ],
    )

