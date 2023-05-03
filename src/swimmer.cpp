#include "swimmer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex count_access;

Swimmer::Swimmer(std::string& name, double& speed)
{
    this->name = name;
    this->speed = speed;
}

Swimmer::Swimmer()
{}

std::string Swimmer::getName()
{
    return name;
}

double Swimmer::getSpeed()
{
    return speed;
}

int Swimmer::getTime()
{
    return time;
}

void Swimmer::count(const int& lenght, const int& swimmer, const int& maxTime)
{
    for (int i = 0; i < maxTime; ++i)
    {
        if(speed * time < lenght || ((speed * time <= lenght) && ((speed * (time + 1)) >= lenght)))
            time++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int meters =time * speed;
        if (meters > 100)
            meters = 100;
        count_access.lock();
        std::cout << "Swimmer" << swimmer << " swam " << meters << " meters" << std::endl;
        count_access.unlock();
    }
}

//Swimmer& Swimmer::operator=(const Swimmer& oldswimmer)
//{
//    this->name = oldswimmer.name;
//    this->speed = oldswimmer.speed;
//    this->time = oldswimmer.time;
//    return *this;
//}
