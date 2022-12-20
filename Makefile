#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryTest    makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------
CC = g++
CFLAGS = -g -std=c++17 -Wall 

all : Order WordFrequency DictionaryTest

Order: Order.o Dictionary.o
	$(CC) $(CFLAGS) -o Order Order.o Dictionary.o 

DictionaryTest: DictionaryTest.o Dictionary.o
	$(CC) $(CFLAGS) -o DictionaryTest DictionaryTest.o Dictionary.o

WordFrequency: WordFrequency.o Dictionary.o
	$(CC) $(CFLAGS) -o WordFrequency WordFrequency.o Dictionary.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean :
	rm -f Order WordFrequency DictionaryTest *.o

clean-gs :
	rm -f *.txt

checkDictionary : DictionaryTest
	valgrind --leak-check=full DictionaryTest

checkOrder : Order
	valgrind --leak-check=full Order 35
