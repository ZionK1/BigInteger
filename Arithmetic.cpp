/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA6
 * Arithmetic.cpp
 * Arithmetic Program
 * ***************************************************************************/
#include "BigInteger.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // line 1: an optional sign character (+ or −) followed by any number of decimal digits
    // line 2: a blank line
    // line 3: an optional sign character (+ or −) followed by any number of decimal digits 
    string curr; // var for holding curr line
    getline(in, curr); // take in curr line
    BigInteger A (curr); // make BigInt A with line 1

    getline(in, curr); // take in blank line
    getline(in, curr); // take in line 3
    BigInteger B (curr); // make BigInt B with line 3

    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << A - A << endl << endl;
    out << BigInteger("3").mult(A) - BigInteger("2").mult(B) << endl << endl; // 3A - 2B
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << BigInteger("9").mult(A * A * A * A) + BigInteger("16").mult(B * B * B * B * B) << endl << endl; // 9A^4 + 16B^5

    return 0;
}