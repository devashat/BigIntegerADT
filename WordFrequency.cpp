/********************************************************************************* 
* Devasha Trivedi, detrived
* 2022 Spring CSE101 PA8
* WordFrequency.cpp
* Main program, top level client for PA8
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

#include "Dictionary.h"

using namespace std;

int main(int argc, char *argv[]) {

    string filename_i, filename_o;
    Dictionary A;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t begin, end, len;
    string line, token = "";

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        exit(EXIT_FAILURE);
    }

    filename_i = argv[1];
    filename_o = argv[2];

    ifstream ifile(filename_i);
    ofstream ofile(filename_o);

    if (ifile.is_open() && ofile.is_open()) {
        while (getline(ifile, line)) {
            len = line.length();
            begin = min(line.find_first_not_of(delim, 0), len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end - begin);

            while (token != "") { // we have a token
                transform(token.begin(), token.end(), token.begin(),
                    [](unsigned char c) { return std::tolower(c); });

                if (A.contains(token)) {
                    A.setValue(token, A.getValue(token) + 1);
                } else {
                    A.setValue(token, 1);
                }
                begin = min(line.find_first_not_of(delim, end + 1), len);
                end = min(line.find_first_of(delim, begin), len);
                token = line.substr(begin, end - begin);
            }
        }

        ifile.close();
    } else {
        cout << "Unable to open files";
    }

    ofile << A.to_string() << endl;

    return 0;
}
