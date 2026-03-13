#pragma once

#ifndef LOGGER_HPP
#define LOGGER_HPP
// #include<Dmath/dataTypes.hpp>
#include<iostream>
#include<fstream>
#include<chrono>
#include<string>


#include<windows.h>


#ifdef BUILD_DLL

    #define SHARED_LIB  __declspec(dllexport)

#else 

    #define SHARED_LIB  __declspec(dllimport)

#endif

namespace DEBUG{
 class SHARED_LIB LOGGER{
private: //Private members

    bool logFile = false;
    std::string filePath = "";
    std::string currentInformation = "";
    std::chrono::time_point<std::chrono::system_clock> start;

    size_t numberOfWarnings = 0;
    size_t numberOfErrors   = 0;

private:

 
    double getMilliseconds();





public:

    LOGGER(std::string ProjectName);

    LOGGER(std::string ProjectName, std::string file);


    ~LOGGER();

public:
    //For info
    void operator<<(const std::string& info);

    //Prints out file, line and the current Information
    void LOG(const std::string& info, const char* FILE, int LINE);


    void LOG(const std::string& info);

    void WARN(std::string warning);

    void Error(int err, std::string errorMessage);
    
    void addText(std::string info);

};
}

#endif