all: clean compile

clean:
	-rm -rf builddir

compile:
	meson builddir
	cd builddir ; ninja

check:
	cd builddir ; ninja test

.PHONY: all clean compile check

