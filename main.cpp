#include <iostream>
#include "include/TextUI.h"
using namespace std;

int main()
{
    TextUI test;
    while(1){
        test.displayMenu();
        test.processCommand();
    }
    return 0;
}


