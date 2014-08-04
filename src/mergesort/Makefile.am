#   Makefile.am for building a BEEBS benchmark
#
#   Copyright (C) 2013 Embecosm Limited and University of Bristol
#
#   This file is part of the Bristol/Embecosm Energy Efficiency Benchmark
#   Suite.
#
#   Contributor: James Pallister <james.pallister@bristol.ac.uk>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS=mergesort mergesort_large mergesort_small
mergesort_SOURCES=mergesort.c
mergesort_large_SOURCES=mergesort.c
mergesort_small_SOURCES=mergesort.c

include $(top_srcdir)/src/common.mk.am

mergesort_SOURCES += ${platform_src}


mergesort_large_CFLAGS=-DLARGE_D $(AM_CFLAGS)
mergesort_small_CFLAGS=-DSMALL_D $(AM_CFLAGS)

mergesort_large_SOURCES += ${platform_src}
mergesort_small_SOURCES += ${platform_src}
