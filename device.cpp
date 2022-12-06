#include "include/device.h"

vector<int> Device::getInput()
{
    vector<int> res;
    for (auto dev : iPins)
        res.push_back(dev->name);
    return res;
}