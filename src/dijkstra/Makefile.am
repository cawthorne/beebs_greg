# Makefile.am for BEEBS Dijkstra test
# 
# Copyright (C) 2013 Embecosm Limited and University of Bristol
# 
# Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>
# 
# This file is part of the Bristol/Embecosm Embedded Energy Benchmark Suite.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS=dijkstra dijkstra_large dijkstra_small
dijkstra_SOURCES=dijkstra.c

EXTRA_DIST = LICENSE

dijkstra_large_SOURCES=dijkstra.c
dijkstra_small_SOURCES=dijkstra.c

include $(top_srcdir)/src/common.mk.am

dijkstra_SOURCES += ${platform_src}

dijkstra_large_CFLAGS=-DLARGE_D $(AM_CFLAGS)
dijkstra_small_CFLAGS=-DSMALL_D $(AM_CFLAGS)

dijkstra_large_SOURCES += ${platform_src}
dijkstra_small_SOURCES += ${platform_src}