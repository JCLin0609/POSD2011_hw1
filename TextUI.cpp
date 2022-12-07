#include "include/TextUI.h"
#include <stack>
int const TERMINAL_EXIT = 9;
int const TERMINAL_HELP = 8;

// Command輸入為1
void Load_function(LogicSim *object, bool *file_load)
{
    string path;
    cout << "Please key in a file path: ";
    cin >> path;

    //計算結果
    bool res = object->load(path);

    if (res == false)
        cout << endl
             << "File not found or file format error!!" << endl;
    else
        *file_load = true;
}

// Command輸入為2
void Simulation(LogicSim *object, bool *file_load)
{
    if (*file_load == false)
    {
        cout << "Plead load an file, before using this operation" << endl;
        return;
    }

    int input_num = object->Get_input_num();
    int output_num = object->Get_output_num();

    // 使用者輸入Input
    vector<int> input;
    for (int i = 0; i < input_num;)
    {
        int key;
        cout << "Please key in the value of input pin " << i + 1 << ": ";
        cin >> key;
        if (cin.fail())
        {
            cout << "The value of input pin must be 0/1" << endl;
            cin.clear();
            cin.get();
        }
        else if (key != 0 && key != 1)
            cout << "The value of input pin must be 0/1" << endl;
        else
        {
            input.push_back(key);
            i++;
        }
    }

    //計算結果
    string ans = object->getSimulationResult(input);

    //按照格式印出
    cout << "Simulation Result:" << endl;
    for (int i = 0; i < input_num; i++)
        cout << "i ";
    cout << "| ";
    for (int i = 0; i < output_num; i++)
        cout << "o ";
    cout << endl;

    for (int i = 0; i < input_num; i++)
        cout << i + 1 << " ";
    cout << "| ";
    for (int i = 0; i < output_num; i++)
        cout << i + 1 << " ";
    cout << endl;

    for (int i = 0; i < input_num * 2; i++)
        cout << "-";
    cout << "+";
    for (int i = 0; i < output_num * 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < input_num; i++)
        cout << input[i] << " ";
    cout << "| ";
    for (int i = 0; i < output_num; i++)
        cout << ans[i] << " ";
    cout << endl;

    return;
}

// Command輸入為3
void Display_truth_table(LogicSim *object, bool *file_load)
{
    if (*file_load == false)
    {
        cout << "Plead load an file, before using this operation" << endl;
        return;
    }
    cout << endl;

    //計算結果
    string ans = object->getTruthTable();

    //按照格式印出
    int input_num = object->Get_input_num();
    int output_num = object->Get_output_num();
    cout << "Truth table:" << endl;
    for (int i = 0; i < input_num; i++)
        cout << "i ";
    cout << "| ";
    for (int i = 0; i < output_num; i++)
        cout << "o ";
    cout << endl;

    for (int i = 0; i < input_num; i++)
        cout << i + 1 << " ";
    cout << "| ";
    for (int i = 0; i < output_num; i++)
        cout << i + 1 << " ";
    cout << endl;

    for (int i = 0; i < input_num * 2; i++)
        cout << "-";
    cout << "+";
    for (int i = 0; i < output_num * 2; i++)
        cout << "-";
    cout << endl;

    int count = 0; //計算truth table長度;
    for (auto c : ans)
        if (c == ' ')
            count++;

    int ans_pos = 0;
    for (int i = 0; i < count; i++) //一個循環為trueth table的一行
    {
        int pos = input_num - 1;
        int tmp = i;
        stack<bool> Bvalue; //儲存binary的值
        while (tmp > 0)     //算出每個值的binary
        {
            int r = tmp % 2;
            tmp /= 2;
            Bvalue.push(r);
            pos--;
        }
        while (pos >= 0)
        {
            Bvalue.push(0);
            pos--;
        }
        while (!Bvalue.empty()) //印出Input值
        {
            cout << Bvalue.top() << " ";
            Bvalue.pop();
        }
        cout << "| ";
        for (int i = 0; i < output_num; i++) //印出output值
        {
            cout << ans[ans_pos] << " ";
            ans_pos++;
        }
        ans_pos++;
        cout << endl;
    }
}

void TextUI::displayMenu()
{
    cout << endl;
    cout << "1. Load logic circuit file" << endl;
    cout << "2. Simulation" << endl;
    cout << "3. Display Truth table" << endl;
    cout << "4. Exit" << endl;
}

void TextUI::processCommand()
{
    int command;

    cout << "Command: ";
    cin >> command;
    if (cin.fail())
    {
        cout << endl
             << "Please enter only interger" << endl;
        cin.clear();
        cin.get();
        return;
    }
    cout << endl;

    switch (command)
    {
    case 1:
        Load_function(object, &file_load);
        break;
    case 2:
        Simulation(object, &file_load);
        break;
    case 3:
        Display_truth_table(object, &file_load);
        break;
    case 4:
        cout << "Goodbye, thanks for using LS." << endl;
        delete object;
        exit(1);
    default:
        cout << "Function not exist." << endl;
        break;
    }
}