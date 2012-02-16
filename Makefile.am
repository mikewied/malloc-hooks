ACLOCAL_AMFLAGS = -I m4


lib_LTLIBRARIES = libmi_hooks.la

libmi_hooks_la_includedir = $(libdir)/mi_hooks
libmi_hooks_la_include_HEADERS = \
                     include/mi_hooks/malloc_hook_c.h \
                     include/mi_hooks/malloc_hook.h

libmi_hooks_la_SOURCES = \
                         src/libc_override.h \
                         src/libc_override_osx.h \
                         src/malloc_guard.h \
                         src/malloc_guard.cc \
                         src/malloc_hook-inl.h \
                         src/malloc_hook.cc

libmi_hooks_la_CPPFLAGS = $(CPPFLAGS) -g -I$(top_srcdir)/include
libmi_hooks_la_LDFLAGS =-R '$(pkglibdir)' -R '$(libdir)'
libmi_hooks_la_CFLAGS = @PROFILER_FLAGS@

check_PROGRAMS=\
               basic_hooks_test

TESTS=${check_PROGRAMS}
TEST_TIMEOUT=30

basic_hooks_test_CPPFLAGS = $(CPPFLAGS) -I$(top_srcdir)/include
basic_hooks_test_SOURCES = t/basic_hook_test.cc
basic_hooks_test_LDADD = libmi_hooks.la
basic_hooks_test_DEPENDENCIES = libmi_hooks.la

test: all check-TESTS
