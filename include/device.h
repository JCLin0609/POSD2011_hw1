#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Device
{
protected:
    vector<Device *> iPins;
    bool output;                   // 紀錄output的bool結果
    bool output_connected = false; // 紀錄output是否有連到其他gate
    // int type;                      // （Unused）裝置類型 0:iPin, 1:AND gate, 2:OR gate, 3:Not gate, 4:oPin.
    int name;                      // Device編號

public:
    //紀錄output已連接其他裝置
    void Set_output_connect() { output_connected = true; };

    //檢查output使否有連接其他裝置
    bool Check_output_connect() { return output_connected; };

    //增加裝置的InputPin
    void addInputPin(Device *d) { iPins.push_back(d); };
    
    //計算Output的bool結果
    virtual bool getOutput() = 0;
    
    //回傳input的所有編號, 大於0的值為gate, 小於的值為iPin
    vector<int> getInput();
};

class iPin : public Device
{
public:
    iPin(int n)
    {
        // type = 0;
        name = n;
    }
    bool getOutput();
    void setOutput(bool out);
};

class oPin : public Device
{
public:
    oPin(int n)
    {
        // type = 4;
        name = n;
    }
    bool getOutput();
};

class gateNot : public Device
{
public:
    gateNot(int n)
    {
        // type = 3;
        name = n;
    }
    bool getOutput();
};

class gateOR : public Device
{
public:
    gateOR(int n)
    {
        // type = 2;
        name = n;
    }
    bool getOutput();
};

class gateAND : public Device
{
public:
    gateAND(int n)
    {
        // type = 1;
        name = n;
    }
    bool getOutput();
};
