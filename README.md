# Programming Assignment 8

In this assignment, we have to write a BigInteger ADT that can perform arithmetic operations on big numbers.

## List of Files

- `Dictionary.cpp`: Contains implementation code for the Dictionary ADT in C++.
- `DictionaryTest.cpp`: Contains implementation code for the BigInteger ADT in C++.
- `Dictionary.h`: Interface to the Dictionary ADT.
- `Order.cpp`: A client file for the Dictionary ADT.
- `WordFrequency.cpp`: The main program in this assignment, a client file for the Dictionary ADT.
- `Makefile`: Enables make commands.
- `README.md`: Contains list of files submitted, as well as information on how to run the program.

## Building

To build, use the following `make` commands:

```make
make // makes all executables
make all // makes all executables
make WordFrequency // makes the WordFrequency module
make Order // makes the Order module
make DictionaryTest // makes DictionaryTest
```

## Running

To run, type `./WordFrequency {input file} {output file}` where {input file} and {output file} are replaced with the respective names.

## Testing

To test, run `./DictionaryTest`.

## Cleaning

To clean, run `make clean`

## Citations

- I modified my pa5 Makefile to be used for this assignment, as the one provided on the webpage did not make `Order`.
- For most of the `Dictionary.h` helper functions, I used the pseudocode provided on the webpage.

## Notes

- valgrind reported about 48 bytes lost per block of memory.
