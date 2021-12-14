# libgrapheme version
VERSION = 0

# Customize below to fit your system

# paths
PREFIX = /usr/local
LIBPREFIX = $(PREFIX)/lib
INCPREFIX = $(PREFIX)/include
MANPREFIX = $(PREFIX)/share/man

# flags
CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS   = -std=c99 -Os -fPIC -Wall -Wextra -Wpedantic
LDFLAGS  = -s

# tools
CC = cc
AR = ar
RANLIB = ranlib
