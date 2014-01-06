#include "stdutil.h"
#include <iostream>
#include <cstdlib> /*for  "system("pause")" */

using namespace std;

void pause() {
    //system("pause");
    //cin.ignore();
    cin.sync();
    cout << endl <<"Press enter for quit...";
    cin.get();
    cin.sync();
}

char* boolToCharPtr(bool boolVal) {
    char* boolCharPtr;
    if (boolVal) {
        boolCharPtr = "true";
    } else {
        boolCharPtr ="false";
    }
    return boolCharPtr;
}