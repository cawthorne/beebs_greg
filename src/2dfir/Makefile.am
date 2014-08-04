bin_PROGRAMS=2dfir 2dfir_large 2dfir_small
2dfir_SOURCES=fir2dim.c

2dfir_large_SOURCES=fir2dim.c
2dfir_small_SOURCES=fir2dim.c

include $(top_srcdir)/src/common.mk.am

2dfir_SOURCES += ${platform_src}

2dfir_large_CFLAGS=-DLARGE_D $(AM_CFLAGS)
2dfir_small_CFLAGS=-DSMALL_D $(AM_CFLAGS)

2dfir_large_SOURCES += ${platform_src}
2dfir_small_SOURCES += ${platform_src}
