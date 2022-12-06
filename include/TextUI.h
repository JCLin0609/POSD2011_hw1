#include <iostream>
#include "LogicSimulator.h"
using namespace std;

class TextUI
{
protected:
    LogicSim *object;       //使用類別LogicSim
    bool file_load = false; //紀錄是否有載入檔案

public:
    TextUI()
    {
        object = new LogicSim;
    }
    void displayMenu();
    void processCommand();
};