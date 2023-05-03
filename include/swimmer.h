#pragma once
#include <string>

struct Swimmer
{
    std::string name = "No name";
    double speed = 0;
    int time = 0;
public:
    Swimmer(std::string& name, double& speed);
    Swimmer();
    std::string getName();
    double getSpeed();
    int getTime();
    void count(const int& lenght, const int& swimmer, const int& maxTime);
//    Swimmer& operator=(const Swimmer& oldswimmer);
};
