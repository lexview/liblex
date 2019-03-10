project('liblex', 'c', version: '1.0')

liblex_sources = [
    'src/parser.c',
]

inc = include_directories('include')

liblex = static_library('lex', liblex_sources,
        include_directories: [inc],
    )

test('Font', executable('01_liblex_font', 'test/01_liblex_font.c'))

