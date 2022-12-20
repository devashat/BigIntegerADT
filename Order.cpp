/********************************************************************************* 
* Devasha Trivedi, detrived
* 2022 Spring CSE101 PA8
* Order.cpp
* Top level client for PA8
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

#include "Dictionary.h"

using namespace std;

int main(int argc, char *argv[]) {

    string filename_i, filename_o;
    Dictionary A;
    int line_count;
    string line;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        exit(EXIT_FAILURE);
    }

    filename_i = argv[1];
    filename_o = argv[2];

    ifstream ifile(filename_i);
    ofstream ofile(filename_o);

    if (ifile.is_open() && ofile.is_open()) {
        line_count = 1;
        while (getline(ifile, line)) {
            A.setValue(line, line_count);
            line_count++;
        }

        ifile.close();
    } else {
        cout << "Unable to open files";
    }

    ofile << A.to_string() << endl;

    ofile << A.pre_string();

    return 0;
}
