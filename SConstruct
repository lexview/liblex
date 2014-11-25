#!/usr/bin/env scons

env = Environment(platform="win32", tools=["mingw"])  # Initialize the environment

CFLAGS = ["-IC:\\Python27\\include"]
LIBPATH = ["C:\\Python27\\libs"]
LIBS = [
    "python27",
]

source = [
    "src/reader.c"
]

liblex = env.StaticLibrary(source=source, target="lex", CFLAGS = CFLAGS, LIBS = LIBS, LIBPATH = LIBPATH)

test = env.Program(source="demo/test.c", target="test", CFLAGS = CFLAGS, LIBS = [liblex])

Default([liblex, test])