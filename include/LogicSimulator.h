#ifndef LOGICSIM_H_INCLUDED
#define LOGICSIM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "device.h"
using namespace std;

class LogicSim
{
    vector<Device *> circuit;
    vector<iPin *> iPins;
    vector<oPin *> oPins;

public:

    bool load(string path);
    string getSimulationResult(vector<int> input);
    string getTruthTable();
    //回傳Input（iPins）數量
    int Get_input_num() { return iPins.size(); };
    //回傳Output（oPins）數量
    int Get_output_num() { return oPins.size(); };
};

#endif