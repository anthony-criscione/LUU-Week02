// Week02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>

void day02Challenge01() 
{
    double compIn[3];
    std::cout << "Input the three numbers to be summed/ averaged\nNumber 1: ";
    std::cin >> compIn[0];
    std::cout << "Number 2: ";
    std::cin >> compIn[1];
    std::cout << "Number 3: ";
    std::cin >> compIn[2];
        std::cout << "\nThe sum of your input is: " << compIn[0] + compIn[1] + compIn[2];
    std::cout << "\nThe average of your input is: " << (compIn[0] + compIn[1] + compIn[2]) / 3.0 << std::endl;
    return;
}

void day02Challenge02() 
{
    double tempFloat;
    std::cout << "Input a number to be cubed: ";
    std::cin >> tempFloat;
    std::cout << "Your number cubed is : " << tempFloat * tempFloat * tempFloat << std::endl;
    return;
}

void day03Challenge01(int* yearOverride = nullptr) {
    int yearOp;
    if (yearOverride != nullptr)  yearOp = *yearOverride;
    else {
        std::time_t tempTime = std::time(NULL);
        std::tm* const timeStruct = std::localtime(&tempTime);
        yearOp = 1900 + timeStruct->tm_year;
    }
    if ((yearOp % 400 == 0) || ((yearOp % 4 == 0) && (yearOp % 100 != 0))) std::cout << yearOp << " is a leap year.\n";
    else std::cout << yearOp << " is not a leap year.\n";
}

void day03Challenge02()
{
    double tempFloat;
    std::cout << "Input a number to be factorized (Non-zero integers only): ";
    std::cin >> tempFloat;
    while ((floor(tempFloat) != tempFloat) || (tempFloat == 0))
    {
        std::cout << "I asked you for a non-zero integer. I trusted you :(\n\n";
        std::cout << "Input a number to be factorized (Non-zero integers only): ";
        std::cin >> tempFloat;
    }

    std::cout << "The factors of your input " << int(tempFloat) << " are: \n";
    int incDir = tempFloat / abs(tempFloat);
    for (int i = incDir; i != tempFloat; i += incDir)
        if (int(tempFloat) % i == 0) {
          if (incDir == -1) std::cout << i * -1 << ", " << i << ", ";
          else std::cout << i << ", ";
        }

    if (incDir == -1) std::cout << int(tempFloat) * -1 << ", ";
    std::cout << int(tempFloat) << std::endl;
    return;
}

int main()
{
    std::cout << "----- LUU Week 02 -----\n-- Anthony Criscione --\n=======================\n\n";
    // The VectorTesting repository is what I messed around with for Day 01

    // Day02
    std::cout << "Day 02:\n";
    day02Challenge01();
    std::cout << std::endl;
    day02Challenge02();
    std::cout << "\n-----------------------\n";

    // Day03
    std::cout << "Day 03:\n";
    int override = 2008;
    day03Challenge01();
    day03Challenge01(&override);
    std::cout << std::endl;
    day03Challenge02();
    std::cout << "\n-----------------------\n";

    return 0;
}