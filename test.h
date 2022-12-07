#ifndef TEST_H
#define TEST_H

#include "include/device.h"
#include "include/LogicSimulator.h"
#include "include/TextUI.h"
using namespace std;

TEST(iPin, getOutput)
{
    iPin *i1 = new iPin(0);

    i1->setOutput(0);
    EXPECT_EQ(i1->getOutput(), 0);

    i1->setOutput(1);
    EXPECT_EQ(i1->getOutput(), 1);

    delete i1;
}

TEST(oPin, getOutput)
{
    iPin *i1 = new iPin(0);
    oPin *o1 = new oPin(0);

    o1->addInputPin(i1);

    i1->setOutput(0);
    EXPECT_EQ(o1->getOutput(), 0);

    i1->setOutput(1);
    EXPECT_EQ(o1->getOutput(), 1);

    delete i1, o1;
}

TEST(gateNot, getOutput)
{
    iPin *i1 = new iPin(0);
    gateNot *n1 = new gateNot(0);

    n1->addInputPin(i1);

    i1->setOutput(0);
    EXPECT_EQ(n1->getOutput(), 1);

    i1->setOutput(1);
    EXPECT_EQ(n1->getOutput(), 0);

    delete i1, n1;
}

TEST(gateOR, getOutput)
{
    iPin *i1 = new iPin(0);
    iPin *i2 = new iPin(1);
    gateOR *n1 = new gateOR(1);
    n1->addInputPin(i1);
    n1->addInputPin(i2);

    i1->setOutput(0);
    i2->setOutput(0);
    EXPECT_EQ(n1->getOutput(), 0);

    i1->setOutput(0);
    i2->setOutput(1);
    EXPECT_EQ(n1->getOutput(), 1);

    i1->setOutput(1);
    i2->setOutput(0);
    EXPECT_EQ(n1->getOutput(), 1);

    i1->setOutput(1);
    i2->setOutput(1);
    EXPECT_EQ(n1->getOutput(), 1);

    delete i1, i2, n1;
}

TEST(gateAND, getOutput)
{
    iPin *i1 = new iPin(0);
    iPin *i2 = new iPin(1);
    gateAND *n1 = new gateAND(1);
    n1->addInputPin(i1);
    n1->addInputPin(i2);

    i1->setOutput(0);
    i2->setOutput(0);
    EXPECT_EQ(n1->getOutput(), 0);

    i1->setOutput(0);
    i2->setOutput(1);
    EXPECT_EQ(n1->getOutput(), 0);

    i1->setOutput(1);
    i2->setOutput(0);
    EXPECT_EQ(n1->getOutput(), 0);

    i1->setOutput(1);
    i2->setOutput(1);
    EXPECT_EQ(n1->getOutput(), 1);

    delete i1, i2, n1;
}

TEST(LogicSim, load)
{
    string path = "File1.txt";

    LogicSim *t = new LogicSim;
    EXPECT_EQ(t->load(path), true);

    delete t;
}

TEST(LogicSim, getSimulationResult)
{
    string path = "File1.txt";
    LogicSim *t = new LogicSim;

    t->load(path);

    vector<int> input;
    input.push_back(0);
    input.push_back(0);
    input.push_back(0);
    EXPECT_EQ(t->getSimulationResult(input), "0");

    input[0] = 0;
    input[1] = 0;
    input[2] = 1;
    EXPECT_EQ(t->getSimulationResult(input), "0");

    input[0] = 0;
    input[1] = 1;
    input[2] = 0;
    EXPECT_EQ(t->getSimulationResult(input), "0");

    input[0] = 0;
    input[1] = 1;
    input[2] = 0;
    EXPECT_EQ(t->getSimulationResult(input), "0");

    input[0] = 0;
    input[1] = 1;
    input[2] = 1;
    EXPECT_EQ(t->getSimulationResult(input), "0");

    input[0] = 1;
    input[1] = 0;
    input[2] = 0;
    EXPECT_EQ(t->getSimulationResult(input), "1");

    input[0] = 1;
    input[1] = 0;
    input[2] = 1;
    EXPECT_EQ(t->getSimulationResult(input), "1");

    input[0] = 1;
    input[1] = 1;
    input[2] = 0;
    EXPECT_EQ(t->getSimulationResult(input), "0");

    input[0] = 1;
    input[1] = 1;
    input[2] = 1;
    EXPECT_EQ(t->getSimulationResult(input), "0");

    delete t;
}

TEST(LogicSim, getTruthTable)
{
    string path = "File1.txt";
    LogicSim *t = new LogicSim;

    t->load(path);
    EXPECT_EQ(t->getTruthTable(), "0 0 0 0 1 1 0 0 ");

    delete t;
}
#endif