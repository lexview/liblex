#!/usr/bin/env scons

env = Environment(platform="win32", MSVC="12.0")


CFLAGS = ["-IC:\\Python27\\include", "-Iinclude"]
LIBPATH = ["C:\\Python27\\libs"]
LIBS = [
    "python27",
]

source = [
    "src/parser.c"
]

liblex = env.StaticLibrary(source=source, target="lex", CFLAGS = CFLAGS, LIBS = LIBS, LIBPATH = LIBPATH)

test = env.Program(source="demo/test.c", target="test", CFLAGS = CFLAGS, LIBS = [liblex])

Default([liblex, test])