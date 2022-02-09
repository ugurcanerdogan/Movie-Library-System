// Assignment 2 - Linked Lists
// Uğurcan ERDOĞAN * 21827373
#include "LibrarySystem.h"
#include <string>

ifstream commandFileObj;
ofstream outputFileObj;

int main(int argc, char** argv) {
    freopen ("output.txt","w",stdout); // method for writing to output file.
    commandFileObj.open(argv[1]);                   // opening command file.
    outputFileObj.open(argv[2],ios::out);           // opening output file.
    LibrarySystem library = LibrarySystem();           // creating a library object.
    outputFileObj.close();                             // closing output file.
    commandFileObj.close();                            // closing command file.
    fclose(stdout);                                    // closing the method for external write.
    return 0;
}
