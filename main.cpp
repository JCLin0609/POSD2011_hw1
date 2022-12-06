#include <iostream>
using namespace std;
#include "include/TextUI.h"

int main()
{
    TextUI test;
    while(1){
        test.displayMenu();
        test.processCommand();
    }
    return 0;
}