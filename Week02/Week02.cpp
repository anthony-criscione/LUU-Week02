// Week02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <random>
#include <string>

void day02Challenge01() {
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

void day02Challenge02() {
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

void day03Challenge02() {
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

void day04Challenge01(int* inArray, int inSize) {
    if (inSize <= 0) return;
    int largest = inArray[0];
    for (int i = 1; i < inSize; i++)
        if (largest < inArray[i]) largest = inArray[i];
    std::cout << "The largest number in your input is: " << largest << std::endl;
}

// Day 04

class vehicle {
protected:
    double mileage = 0.0;
    double speed = 0.0;
    int year;
    std::string make, model, name, spdUnits, distUnits;
    double baseSpeed = 1.0;
    double driveStep = 60.0;
public:
    virtual void outInfo() = 0;
    virtual void drive(char inDir) = 0;
    virtual void outControls() = 0;
    //virtual void setName() = 0;
    void accel(double amnt) { speed += amnt; }
    vehicle(std::string inMake, std::string inModel, int inYear) {
        make = inMake;
        model = inModel;
        year = inYear;
    }
    virtual void outSpeed() { std::cout << "You are traveling at " << speed << " " << spdUnits << ".\n"; }
    void outDist() { std::cout << "You have traveled " << mileage << " " << distUnits << ".\n"; }
};

class car : public vehicle {
    using vehicle::vehicle;
private:

protected:
    std::string spdUnits = "mph";
    std::string distUnits = "miles";
public:
    void outInfo() override { std::cout << "You are driving a " << year << " " << make << " " << model << ".\n"; }
    void outControls() override { std::cout << "Accelerate on w, brake on s.\n"; }
    void drive(char inDir) override {
        if (inDir == 'm') {
            std::cout << "Maintaining course.\n";
        }
        else if (inDir == 'w') {
            accel(baseSpeed);
            
        }
        else if (inDir == 's') {
            accel(-baseSpeed);
        }
        else {
            std::cout << inDir << " is currently unbound.\n";
            return;
        }
        mileage = abs(speed) / driveStep;
        outSpeed();
        outDist();
    }
    
};

class boat : public vehicle {
    using vehicle::vehicle;
protected:
    double current = -4.0;
    double speed = current;
    std::string spdUnits = "knots";
    std::string distUnits = "nautical miles";
public:
    void outInfo() override { std::cout << "You are at the helm of a " << year << " " << make << " " << model << ".\n"; }
    void outControls() override { std::cout << "Accelerate on w, brake on s.\n"; }
    void outSpeed() override {
        std::cout << "You are traveling at " << speed + current << " " << spdUnits << ".\n"; 
    }
    void outInstr() {
        std::cout << "Your instruments read an engine output of " << speed << spdUnits << " and a sea current speed of " << current << spdUnits << " relative to your current heading.\n";
    }
    void drive(char inDir) override {
        if (inDir == 'm') {
            std::cout << "Maintaining course.\n";
        }
        else if (inDir == 'w') {
            accel(baseSpeed);
            
        }
        else if (inDir == 's') {
            accel(-baseSpeed);
            
        }
        else {
            std::cout << inDir << " is currently unbound.\n";
            return;
        }
        mileage = abs(speed + current) / driveStep;
        outInstr();
        outSpeed();
        outDist();
    }
};

class plane : public vehicle {
    using vehicle::vehicle;
private:
    void movePlane() {
        if (speed >= liftThresh) {
            pitch = std::max(-pitchCap, std::min(pitchCap, pitch + flapPitch));
            alt += (baseSpeed / driveStep) * pitch;
        }
        else if (alt > 0.0) {
            pitch = std::max(-pitchCap, pitch - stallPitchLoss);
            alt += (baseSpeed / driveStep) * pitch;
            if (alt != 0.0) std::cout << "!! STALL !! STALL !!\n";
        }
        if (alt < 0.0) {
            if (std::abs(alt) > shockAbs || std::abs(pitch) > landingPitchTol) {
                std::cout << "*fire-emoji* You have crashed *fire-emoji*\n";
                crashed = true;
            }
            else {
                alt = 0.0;
                pitch = 0.0;
            }
        }

    }
protected:
    bool crashed = false;
    double alt = 0.0;
    double pitch = 0.0;
    double baseSpeed = 5.0;
    double driveStep = 1.0;
    double liftThresh = 40.0;
    double stallPitchLoss = .1;
    double shockAbs = 10.0; // Will absorb up to X vertical distance to facilitate landing 
    double flapStep = .1; 
    double flapPitch = 0.0;
    double capFlap = .4;
    double pitchCap = 1.0;
    double landingPitchTol = .2;

    std::string spdUnits = "km/h";
    std::string distUnits = "meters"; 
public:
    void outInfo() override { std::cout << "You are piloting a " << year << " " << make << " " << model << ".\n"; }
    void outControls() override { std::cout << "Throttle on R/F, stick on W/S, m for maintaining course.\nInstrument readout on i, landing info on l.\n"; }

    void outLandingInfo() {
        std::cout << "Your craft will generate lift at " << liftThresh << spdUnits << ", your shocks will absorb up to " <<
                      shockAbs << distUnits << "height change, and will tolerate a pitch of up to  " << landingPitchTol << " (absolute value).\n";
        std::cout << "In current conditions, aircraft below their lift threshold will lose pitch at a rate of " << stallPitchLoss << " per input step.\n";
    }

    void outSpeed() override {
        std::cout << "You are traveling at " << speed << " " << spdUnits << ".\n";
    }
    void outInstr() {
        std::cout << "Your instruments read a speed of " << speed << spdUnits << " and an altitude of " << alt << distUnits << ".\n";
        std::cout << "Your flaps are currently set to " << flapPitch << "and your craft has a pitch of " << pitch << "\n";
    }
    void drive(char inDir) override {
        if (crashed) return;
        if (inDir == 'm') {
            std::cout << "Maintaining course.\n";
        }
        else if (inDir == 'i') {
            outInstr();
            outSpeed();
            outDist();
            return;
        }
        else if (inDir == 'l') {
            outLandingInfo();
            return;
        }
        else if (inDir == 'r') {
            accel(baseSpeed);
        }
        else if (inDir == 'f') {
            accel(-baseSpeed);
            if (alt > 0.0) speed = std::max(0.0, speed);
        }
        if (inDir == 'w') {
            flapPitch = std::max(-capFlap, flapPitch - flapStep);
        }
        else if (inDir == 's') {
            flapPitch = std::min(capFlap, flapPitch + flapStep);
        }
        else {
            std::cout << inDir << " is currently unbound.\n";
            return;
        }
        movePlane();
        mileage = abs(speed) / driveStep;
        outInstr();
        outDist();
    }
};
// ------
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

    // Day04
    std::cout << "Day 04:\n";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(0.00, 1.00);
    double distRange = 10000;
    int inCount = 10;
    int* distArray = new int[inCount];
    std::cout << "\nYour randomly generated array is ["; 
    for (int i = 0; i < inCount - 1; i++) {
        distArray[i] = distRange * distribution(generator);
        std::cout << distArray[i] << ", ";
    }
    distArray[inCount - 1] = distRange * distribution(generator);
    std::cout << distArray[inCount - 1] << "]\n";
    day04Challenge01(distArray, inCount);
    int selection = -1;
    std::cout << "Input 1 to drive a car, 2 for a boat, 3 for a plane, or 4 to exit: ";
    std::cin >> selection;
    while (selection < 1 ||  selection > 4) {
        std::cout << "Invalid selection, input 1 to drive a car, 2 for a boat, 3 for a plane, or 4 to exit: ";
        std::cin >> selection;
    }
    if (selection == 1) {
        car drivable = car(std::string("Mazda"), std::string("2"), 2014);
        drivable.outInfo();
        drivable.outControls();
        char driveInput;
        std::cout << "Driving input (q to quit): ";
        std::cin >> driveInput;
        while (driveInput != 'q') {
            drivable.drive(driveInput);
            std::cout << "Driving input (q to quit): ";
            std::cin >> driveInput;
        }
    }
    else if (selection == 2) {
        boat drivable = boat(std::string("Scrapyard"), std::string("Motorboat"), 2009);
        drivable.outInfo();
        drivable.outControls();
        char driveInput;
        std::cout << "Helm input (q to quit): ";
        std::cin >> driveInput;
        while (driveInput != 'q') {
            drivable.drive(driveInput);
            std::cout << "Helm input (q to quit): ";
            std::cin >> driveInput;
        }
    }
    else if (selection == 3) {
        plane drivable = plane(std::string("NAA"), std::string("P-51"), 1940);
        drivable.outInfo();
        drivable.outControls();
        char driveInput;
        std::cout << "Helm input (q to quit): ";
        std::cin >> driveInput;
        while (driveInput != 'q') {
            drivable.drive(driveInput);
            std::cout << "Helm input (q to quit): ";
            std::cin >> driveInput;
        }
    }
    
    std::cout << "\n-----------------------\n";



    return 0;
}