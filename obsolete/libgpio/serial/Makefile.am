## Specify some includes and versioning
INCLUDES = -I../ $(VERSION_FLAGS) -I$(top_srcdir)/include
VERSION_FLAGS = -DLIBGPIO_VERSION=\"@LIBGPIO_VERSION@\" -DHAVE_TERMIOS_H
CFLAGS = @CFLAGS@ @IOLIB_CFLAGS@ -g
LDFLAGS = @LDFLAGS@ -g 

## Compile the IO library into a shared library
iolibdir = $(prefix)/lib/gpio
iolib_LTLIBRARIES = libgpio_serial.la
libgpio_serial_la_LDFLAGS = -version-info @LIBGPIO_VERSION_INFO@ -DHAVE_TERMIOS_H 
libgpio_serial_la_SOURCES = unix.c
