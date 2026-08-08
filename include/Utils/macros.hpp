#pragma once
//File /include/macros.hpp
//No Corresponding .cpp-file


#ifndef DK_MACROS_HPP
#define DK_MACROS_HPP

/* This File contains all the necessary constants, librarys and macros for the project */

#pragma region Librarys
    //Librarys needed for this project

    #include <cmath>       //Mathmatical operations
    #include <vector>      //Container
    #include <functional>  
    #include <stdint.h>
    #include <algorithm>
    #include <thread>
    #include <type_traits>
    #include <string>
    #include <limits>

#pragma endregion


#pragma region Constants
    //Physical and mathmatical constants, and constants
    #define ZERO_KELVINK -273.17   //0Kelvin in celsius degrees
    #define ZERO_KELVINC  273.17   //0Degrees Celsius in Kelvin
    #define TOLLERANCE  0.000001   //the standard resolution for clculating the area or slope aof a function


    #define PI              3.14159265358979323846
    #define EULER           2.718281828459045
    #define MILES_TO_KM     1.60934
    #define POUNDS_TO_KG    0.453592
    #define BAR_TO_PSI      14.5038
    #define CAUSALITY       299792458 //basicly the speed of light C
    #define ROUNDING_VALUE  3 //rounding 3 digits after the decimal point/komma
    #define HALF_PI    (PI / 2)
    #define THREE_PI   (PI * 3)
    #define QUARTER_PI (PI / 4)
    


    #define TWOPI      (2 * PI)
    #define FOUR_PI    (4 * PI)
    #define EIGHT_PI   (8 * PI)
    #define SIXTEEN_PI (16 * PI)
    #define RAD_TO_DEG (180.f/PI)              //Radiants to Degrees
    #define DEG_TO_RAD (PI/180.f)              //Degres to Radiants

    


    #define STDRES     0.05f                 //The standard resolution for more dimensional vector systems
    #define ZERO       0                     //Standard zero used as a constant for the startpoint in more dimensional vector systems
    #define ROOT_TWO   1.41421               //The squareroot of 2
    #define ROOT_THREE 1.7320                //The squareroot of 3
    


#pragma region Types


    #define CNULL      ((void *)0)

    #define THIS_FILE __FILE__
    #define THIS_LINE __LINE__
    

    //Main Namespaces
    #define NAMESPACEWORKING      namespace Working {
    #define NAMESPACESTART        namespace Dmath   {
    #define NAMESPACEEXPERIMENTAL namespace Experimental{
    #define NAMESPACEEND        }

    //For functional math:
    #define NULLFUNCTION       []() -> double                             { return 0; }
    #define SINGLENULLFUNCTION [](double x) -> double                     { return 0; }
    #define DOUBLENULLFUNCTION [](double x, double y) -> double           { return 0; }
    #define TRIPLENULLFUNCTION [](double x, double y, double z) -> double { return 0; }  

#pragma endregion

//////////////////////////

#pragma region Functional

    #define SQUARED(data) ((data) * (data))
    #define CUBED(data) ((data) * (data) * (data))

    #define DEGTORAD(ANGLE) ((ANGLE)*DEG_TO_RAD)
    #define RADTODEG(RADIANT) ((RADIANT)*RAD_TO_DEG)

    //Satz des pytagoras
    #define PYTH(inputA, inputB) (std::sqrt((inputA * inputA) + (inputB * inputB)))
    #define PYTH3(inputX, inputY, inputZ) (std::sqrt((inputX * inputX)+(inputY*inputY)+(inputZ*inputZ)))


#pragma endregion



#pragma region controll macros

    #define CARTESIAN_IS_2D_STANDARD
    //#define POLAR_IS_STANDARD

    #define CARTESIAN_IS_3D_STANDARD
    //#define SPHERE_IS_STANDARD
    //#define CYLINDER_IS_STANDARD


    #if defined(CARTESIAN_IS_2D_STANDARD) && defined(POLAR_IS_STANDARD)

        #warning "Both 2D systems defined. Using Cartesian."
        #undef POLAR_IS_STANDARD

    #endif




    #if defined(CARTESIAN_IS_3D_STANDARD) && \
        (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD))

        #warning "Cartesian 3D overrides other 3D systems."

        #undef SPHERE_IS_STANDARD
        #undef CYLINDER_IS_STANDARD

    #endif

    #if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD) ||                               \
        defined(CARTESIAN_IS_3D_STANDARD) || defined(POLAR_IS_STANDARD) ||                            \
        defined(CARTESIAN_IS_2D_STANDARD))
        #define SYSTEM_IS_SET
    #else
        #error "FATAL ERROR NO SYSTEM SET"
    #endif





    #if defined(_WIN32) || defined(_WIN64)

        #define OS_WINDOWS
        #include"Windows.h"
        #warning "Compiling for Windows"

        #ifdef BUILD_DLL
            #define SHARED_LIB __declspec(dllexport)
        #else
            #define SHARED_LIB __declspec(dllimport)
        #endif

    #elif defined(__linux__)

        #define OS_LINUX
        #warning "Compiling for Linux"
        #ifdef BUILD_DLL
            #warning "No Dlls in linux"
            #undef BUILD_DLL
        #endif

    #elif defined(__APPLE__) && defined(__MACH__)

        #define OS_MAC
        #warning "Compiling for MacOS"

    #else

        #error "Unknown Operating System"

    #endif


//==============================
// OS READY FLAG
//==============================

#if defined(OS_WINDOWS) || defined(OS_LINUX) || defined(OS_MAC)
    #define OS_IS_SET
#endif
 


    #define ANGLE_UNIT_RADIANTS
    //#define ANGLE_UNIT_DEGREES

    #if defined(ANGLE_UNIT_RADIANTS) && defined(ANGLE_UNIT_DEGREES)

        #warning "Both angle units defined. Using radians."
        #undef ANGLE_UNIT_DEGREES

    #endif

    //Radiants is standard in c++ so no conversion needed
    #ifdef ANGLE_UNIT_RADIANTS
        #define getAngle(data) (data)
        #define ANGLE_UNIT_SET
    #endif

    //If degree is set, redefine getAngle 
    #ifdef ANGLE_UNIT_DEGREES
        #define getAngle(data) (RADTODEG(data))
        #define ANGLE_UNIT_SET
    #endif 


    #if (defined(SYSTEM_IS_SET) && defined(ANGLE_UNIT_SET))
        #define SYSTEM_READY //Wird in anderen dateien verwendet

    #endif
  
    

#pragma endregion



#if defined(_MSC_VER)

    #define COMPILER_MSVC
    #warning "Compiler: MSVC"

#elif defined(__clang__)

    #define COMPILER_CLANG
    #warning "Compiler: Clang"

#elif defined(__GNUC__)

    #define COMPILER_GCC
    #warning "Compiler: GCC"

#else

    #warning "Unknown compiler"

#endif



#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)

    #define ARCH_64BIT
    #warning "64 Bit Architecture"

#else

    #define ARCH_32BIT
    #warning "32 Bit Architecture"

#endif
















#endif //DK_MACROS_HPP