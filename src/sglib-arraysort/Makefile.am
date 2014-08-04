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

bin_PROGRAMS=sglib-arraysort sglib-arraysort_large sglib-arraysort_small
sglib-arraysort_SOURCES=arraysort.c sglib.h
sglib-arraysort_large_SOURCES=arraysort.c sglib.h
sglib-arraysort_small_SOURCES=arraysort.c sglib.h

include $(top_srcdir)/src/common.mk.am

sglib-arraysort_SOURCES += ${platform_src}

sglib-arraysort_large_CFLAGS=-DLARGE_D $(AM_CFLAGS)
sglib-arraysort_small_CFLAGS=-DSMALL_D $(AM_CFLAGS)

sglib-arraysort_large_SOURCES += ${platform_src}
sglib-arraysort_small_SOURCES += ${platform_src}
