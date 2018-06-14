#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2018
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Tommaso Buvoli
#

CC     = c++
OPTS   = -O3 -DNDEBUG -pthread
LANG   = -std=c++14
PICKY  = -Wall 
CFLAGS = $(LANG) $(OPTS) $(PICKY) 

OBJFILES = Matrix.o Vector.o amath583.o amath583IO.o 
EXEFILES = test_serial_norms.exe test_parallel_norms.exe test_parallel_matmul.exe prob4_1.exe prob4_a.exe prob4_b.exe prob4_c.exe prob4_5.exe
.PHONY: all clean

all: $(EXEFILES)
	
%.exe: %.o $(OBJFILES)
	$(CC) $(CFLAGS) $< $(OBJFILES) -o $@
%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm -f *.o *.exe
