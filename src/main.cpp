#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include "swimmer.h"

const int SIZE(4);
const int LENGTH(100);

void checkName(std::string& name)
{
    while(1)
    {
        auto is = std::find_if(name.begin(), name.end(), [](const char &c)
        {
            return !std::isalpha(c);
        });

        if(is == name.end())
            break;

        std::cout << "Enter the correct name: ";
        std::cin >> name;
    }
}

void checkSpeed(double& speed)
{
    while(speed <=0)
    {
        std::cout << "Enter the correct speed: ";
        std::cin >> speed;
    }
}

int main()
{
    std::vector<Swimmer*> swimmers;
    std::cout << "The program swimmers 100 meters." << std::endl;

    std::cout << std::thread::hardware_concurrency() << std::endl;
    for(int i = 0; i < SIZE; ++i)
    {
        std::string name;
        std::cout << "Enter the swimmer`s name: ";
        std::cin >> name;
        checkName(name);

        double speed;
        std::cout << "Enter the speed of " << name << " swimmer: ";
        std::cin >> speed;
        checkSpeed(speed);

        Swimmer* swimmer = new Swimmer(name, speed);
        swimmers.push_back(swimmer);
    }

    int minInd = 0;

    for(int i = 0; i < SIZE - 1; ++i)
    {
        if(swimmers[i]->getSpeed() > swimmers[i+1]->getSpeed())
            minInd = i+1;
    }

    int time = 0;
    if((LENGTH / (swimmers[minInd]->getSpeed())) == 0)
        time = ((LENGTH)/ (swimmers[minInd]->getSpeed()));
    else
        time = ((LENGTH)/(swimmers[minInd]->getSpeed())) + 1;

    std::thread swimmer1(&Swimmer::count, swimmers[0], LENGTH, 0, time);
    std::thread swimmer2(&Swimmer::count, swimmers[1], LENGTH, 1, time);
    std::thread swimmer3(&Swimmer::count, swimmers[2], LENGTH, 2, time);
    std::thread swimmer4(&Swimmer::count, swimmers[3], LENGTH, 3, time);
//    std::thread swimmer5(&Swimmer::count, swimmers[4], LENGTH, 4, time);
//    std::thread swimmer6(&Swimmer::count, swimmers[5], LENGTH, 5, time);

    swimmer1.join();
    swimmer2.join();
    swimmer3.join();
    swimmer4.join();
//    swimmer5.join();
//    swimmer6.join();

if(minInd != SIZE -1)
    {
        Swimmer* swim = new Swimmer(*swimmers[SIZE-1]);
        (*swimmers[SIZE - 1]) = (*swimmers[minInd]);
        (*swimmers[minInd]) = (*swim);
        delete swim;
    }

    for(int i = 1; i < SIZE - 1; ++i)
    {
        for(int j = (SIZE - 1) - i; j > 0; --j)
        {
            if(swimmers[j]->getSpeed() > swimmers[j-1]->getSpeed())
                minInd = j-1;
        }
        Swimmer* temp = new Swimmer();
        (*temp) = (*swimmers[minInd]);
        (*swimmers[minInd]) = (*swimmers[(SIZE-1)-i]);
        (*swimmers[(SIZE-1)-i]) = (*temp);
        delete temp;
    }



    for(int i = 0; i < SIZE; ++i)
        std::cout << swimmers[i]->getName() << " " << swimmers[i]->getTime() << " " << std::endl;

    for (int i = 0; i < SIZE; ++i)
    {
        delete swimmers[i];
    }

    return 0;
}
