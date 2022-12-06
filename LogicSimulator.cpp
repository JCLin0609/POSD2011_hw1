#include "include/LogicSimulator.h"
#include <fstream>
#include <cmath>
using namespace std;

bool LogicSim::load(string path)
{
    ifstream myfile;
    std::string mystring;
    int input_num, gate_num; //紀錄數量
    int input = -1;          //讀取file內個別的值
    int gate_pos = 0;        //紀錄現在用到第幾個gate

    //讀取電路圖資訊 並存入類別LogicSim的circuit,iPins中
    myfile.open(path);
    if (myfile.is_open())
    {
        //讀入前兩個值
        myfile >> input_num >> gate_num;

        //初始化所有elements
        circuit.clear();
        iPins.clear();
        oPins.clear();

        //建立對應數量的iPin
        for (int i = 1; i <= input_num; i++)
        {
            iPin *d = new iPin(-i);
            iPins.push_back(d);
        }
        getline(myfile, mystring);

        //處理第三行輸入之後的每一個gate描述
        bool create_new = true; //每一行的開始都需要建立新的gate
        vector<vector<int>> connected_pins;

        while (myfile)
        {
            myfile >> input;

            //遇到0代表一行的結束
            if (input == 0)
            {
                create_new = true;
                gate_pos++;
                continue;
            }

            if (create_new == true) // 遇到新的一行
            {
                vector<int> iPin_vector;
                connected_pins.push_back(iPin_vector);
                if (input == 0)
                    break;
                else if (input == 1)
                    circuit.push_back(new gateAND(gate_pos + 1));
                else if (input == 2)
                    circuit.push_back(new gateOR(gate_pos + 1));
                else if (input == 3)
                    circuit.push_back(new gateNot(gate_pos + 1));
                create_new = false;
            }
            else //每一行中間的各個值
                connected_pins[gate_pos].push_back(input);
        }

        // 處理每一個gate的InputPin
        for (int i = 0; i < gate_pos - 1; i++)
        {
            for (auto j : connected_pins[i])
            {
                int tmp = j;
                if (tmp < 0)
                    circuit[i]->addInputPin(iPins[abs(tmp + 1)]);
                else
                    circuit[i]->addInputPin(circuit[tmp - 1]);
            }
        }
    }
    else
        return false;

    //找出哪些是oPin（只要出現在任一個gate的input,就不是oPin）
    for (auto gate : circuit)
    {
        vector<int> res = gate->getInput();
        for (int name : res)
            if (name > 0) //大於0的是gate
                circuit[name - 1]->Set_output_connect();
            else //小於0的是iPin
                iPins[abs(name) - 1]->Set_output_connect();
    }

    //把oPin存入類別oPins中
    int oPin_pos = 0;
    for (auto gate : iPins) //可能有iPin沒接到gate
    {
        if (gate->Check_output_connect() == false)
        {
            oPins.push_back(new oPin(oPin_pos + 1));
            oPins.back()->addInputPin(gate);
            oPin_pos++;
        }
    }
    for (auto gate : circuit) //只要gate的ouput沒接到東西,其output就是oPin
    {
        if (gate->Check_output_connect() == false)
        {
            oPins.push_back(new oPin(oPin_pos + 1));
            oPins.back()->addInputPin(gate);
            oPin_pos++;
        }
    }

    return true;
}

string LogicSim::getSimulationResult(vector<int> input)
{
    // 把input存入iPins
    for (int i = 0; i < iPins.size(); i++)
        iPins[i]->setOutput(input[i]);

    // 計算oPin的output
    string ans = "";
    for (auto oPin : oPins)
        ans += (oPin->getOutput() + 48);

    return ans;
}

string LogicSim::getTruthTable()
{
    int input_len = Get_input_num();
    string ans = "";

    // Input會從0到2^n次方
    for (int i = 0; i < pow(2, input_len); i++)
    {
        int pos = input_len - 1;
        int tmp = i;
        //用輾轉相除法找出binary的值,並設定到iPins中
        while (tmp > 0)
        {
            int r = tmp % 2;
            tmp /= 2;
            iPins[pos]->setOutput(r);
            pos--;
        }
        while (pos >= 0)
        {
            iPins[pos]->setOutput(0);
            pos--;
        }
        //得出oPin結果
        for (auto oPin : oPins)
            ans += (oPin->getOutput() + 48);
        ans += " ";
    }
    return ans;
}