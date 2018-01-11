### Makefile.am
### Copyright 2017 Mac Radigan
### All Rights Reserved

AM_LDFLAGS  = -pthread                                                         \
              -L/usr/lib -ldl -lm                                              \
              -L/usr/lib/x86_64-linux-gnu                                      \
              -lstdc++fs                                                        

AM_CPPFLAGS = -I$(top_srcdir)/include                                          \
              -std=c++1z                                                       \
              -O3
AM_FCFLAGS  = -Jmod

cli_ldadd             = libcli.la                                              \
                        -ldl -lm                                               \
                        -lrt                                                   \
                        -lstdc++fs                                             \
                        -lboost_system                                         \
                        -lboost_program_options                                 

bin_PROGRAMS          = test_cli

test_cli_SOURCES      = src/tests/test_cli.cc
test_cli_LDADD        = $(cli_ldadd)

lib_LTLIBRARIES       = libcli.la                                               

libcli_la_SOURCES     = src/packages/cli/Cli.cc
libcli_la_LIBADD      = -L/usr/lib/x86_64-linux-gnu -lrt
libcli_la_LDFLAGS     = -export-symbols-regex '^cli_[^_]' -fPIC                \
                        -shared -pthread                                       \
                        -L/usr/lib/x86_64-linux-gnu -lrt                        

pkginclude_HEADERS    = include/packages/cli/Cli.h

### *EOF*
