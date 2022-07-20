// Week02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

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

    return 0;
}