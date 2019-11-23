#Bernard Steemers
#20/11/2019
#Licence: Attribution 4.0 International (CC BY 4.0)
#You are free to:
#	- Share — copy and redistribute the material in any medium or format
#	- Adapt — remix, transform, and build upon the material for any purpose, even commercially.
#	- Link: https://creativecommons.org/licenses/by/4.0/legalcode

#Joseph Kehoe 13/9/2017
#Second improved Makefile
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.

#brief Compilation instructions for files contained in this projects

CC=g++
CFLAGS= -std=c++11 -pthread -Wall

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o Barrier.o Semaphore.o
	$(CC) -o barrier main.o Barrier.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#This is customary and just deletes all .o files
CLEAN:
	rm *.o