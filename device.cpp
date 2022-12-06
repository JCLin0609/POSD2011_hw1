#include "include/device.h"

// Device
vector<int> Device::getInput()
{
    vector<int> res;
    for (auto dev : iPins)
        res.push_back(dev->name);
    return res;
}

// iPin
bool iPin::getOutput()
{
    return output;
}

void iPin::setOutput(bool out)
{
    output = out;
}

// oPin
bool oPin::getOutput()
{
    output = iPins[0]->getOutput();
    return output;
}

// gateNot計算
bool gateNot::getOutput()
{
    output = iPins[0]->getOutput() == 0 ? 1 : 0;
    return output;
}

// gateOR計算
bool gateOR::getOutput()
{
    bool ans = false;
    for (auto d : iPins)
        ans = ans || d->getOutput();
    output = ans;
    return output;
}

// gateAND計算
bool gateAND::getOutput()
{
    bool ans = true;
    for (auto d : iPins)
        ans = ans * d->getOutput();
    output = ans;
    return output;
}