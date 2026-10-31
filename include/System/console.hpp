#pragma once

#ifndef DMATH_CONSOLE_HPP
#define DMATH_CONSOLE_HPP

#include"../Utils/dataTypes.hpp"
#include<iostream>

NAMESPACESTART


constexpr const char* Reset  = "\033[0m";
constexpr const char* Red    = "\033[31m";
constexpr const char* Green  = "\033[32m";
constexpr const char* Yellow = "\033[33m";
constexpr const char* Blue   = "\033[34m";
constexpr const char* Cyan   = "\033[36m";

constexpr inline void Error(const std::string& msg, Dmath::ERROR_CODE& err = GENERAL_ERROR){
    std::cout << Red << "[Dmath::Error]: " << err << std::endl << msg << std::endl;
} 

constexpr inline void Warn(const std::string& msg){
    std::cout << Yellow << "[Dmath::Warning]: " << msg << std::endl;
} 




NAMESPACEEND

#endif