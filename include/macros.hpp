#pragma once
//File /include/macros.hpp
//No Corresponding .cpp-file


#ifndef DK_MACROS_HPP
#define DK_MACROS_HPP

/* This File contains all the necessary constants, librarys and macros for the project */


    //Librarys needed for this project
    #include <cmath>
    #include <vector>
    #include <functional>
    #include <stdint.h>
    #include <algorithm>
    #include <thread>
    #include <type_traits>
    #include <string>
    

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
    #define RAD_TO_DEG (180.f/PI)              //Radiants to Degrees
    #define DEG_TO_RAD (PI/180.f)              //Degres to Radiants
    #define DEGTORAD(ANGLE) ((ANGLE)*DEG_TO_RAD)
    #define RADTODEG(RADIANT) ((RADIANT)*RAD_TO_DEG)
    


    #define STDRES     0.05f                 //The standard resolution for more dimensional vector systems
    #define ZERO       0                     //Standard zero used as a constant for the startpoint in more dimensional vector systems
    #define ROOT_TWO   1.41421               //The squareroot of 2
    #define ROOT_THREE 1.7320                //The squareroot of 3
    #define CNULL      ((void *)0)
    //Main Namespaces
    #define NAMESPACETEST         namespace Testing {
    #define NAMESPACEWORKING      namespace Working{
    #define NAMESPACESTART        namespace Dmath {
    #define NAMESPACEEXPERIMENTAL namespace Experimental{
    #define NAMESPACEEND        }

    //For functional math later:
    #define SINGLENULLFUNCTION [](double x) ->double                      { return 0; }
    #define DOUBLENULLFUNCTION [](double x, double y) ->double            { return 0; }
    #define TRIPLENULLFUNCTION [](double x, double y, double z) -> double { return 0; }  

    #define SQUARED(data) ((data) * (data))
    #define CUBED(data) ((data) * (data) * (data))

    //Satz des pytagoras
    #define PYTH(inputA, inputB) (std::sqrt((inputA * inputA) + (inputB * inputB)))
    #define PYTH3(inputX, inputY, inputZ) (std::sqrt((inputX * inputX)+(inputY*inputY)+(inputZ*inputZ)))


    #define THIS_FILE __FILE__
    #define THIS_LINE __LINE__

    #define  byte uint8_t
    
    #define CARTESIAN_IS_3D_STANDARD
    #define CARTESIAN_IS_2D_STANDARD
 #if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD)) &&                              \
        defined(CARTESIAN_IS_3D_STANDARD)
        #warning "Warning: More than one system is defined!"
        #define COORDINATES_READY
        #undef CARTESIAN_IS_STANDARD

        #ifdef SPHERE_IS_STANDARD
            #undef CYLINDER_IS_STANDARD
            #warning "Sphere system will be standart!"
            #define COORDINATES_READY
        #endif
        
        #else
        #define COORDINATES_READY
        

    #endif

#if (defined(_WIN32) || defined(_WIN64))
    #include"Windows.h"
    #ifdef BUILD_DLL
        #define SHARED_LIB __declspec(dllexport)
    #else
        #define SHARED_LIB __declspec(dllimport)
    #endif

#else
    // Für andere Plattformen: möglicherweise SHARED_LIB leer lassen oder anders definieren
    #define SHARED_LIB
#endif


    #if (defined(CARTESIAN_IS_2D_STANDARD) && defined(POLAR_IS_STANDARD))
        #undef POLAR_IS_STANDARD
#
    #elif defined(CARTESIAN_IS_2D_STANDARD)
        #define COORDINATES_READY

    #endif //defined(CARTESIAN_IS_2D_STANDARD) && defined(POLAR_IS_STANDARD)

    #if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD) ||                               \
        defined(CARTESIAN_IS_3D_STANDARD) || defined(POLAR_IS_STANDARD) ||                            \
        defined(CARTESIAN_IS_2D_STANDARD))
        #define COORDINATES_READY
        #else

    #endif

    #ifdef WORKING
        #warning "DEBUGMODE"
        
        #ifdef RELEASE
            #undef RELEASE
        #endif

        #include <iostream>
        #include <fstream>

        

      
     
    #endif //WORKING
    
    
  
//Choose your prefered angle unit with (un)commenting the fitting macro
#define STANDARD_ANGLE_UNIT_DEG
//#define STANDARD_ANGLE_UNIT_RAD
#if(defined(STANDARD_ANGLE_UNIT_DEG) || defined(STANDARD_ANGLE_UNIT_RAD))
#define ANGLE_UNIT_SET
#else
#if(defined(STANDARD_ANGLE_UNIT_DEG) && defined(STANDARD_ANGLE_UNIT_RAD))
#warning "Both angle units are set standard will be radiants!"
#undef STANDARD_ANGLE_UNIT_DEG
#define ANGLE_UNIT_SET
#endif
#endif

//Uncomment to choose your standard coordinate system

#define CARTESIAN_IS_2D_STANDARD   // Cartesian system: X,Y
//#define POLAR_IS_STANDARD        //Polar system: Radius, phi

#define CARTESIAN_IS_3D_STANDARD   //Cartesian system: X,Y,Z
//#define SPHERE_IS_STANDARD       // Sphere system: Radius, phi, phi
//#define CYLINDER_IS_STANDARD     //Cylinder system: Radius, phi, height

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD)) &&                              \
    defined(CARTESIAN_IS_3D_STANDARD)
#warning "Warning: More than one system is defined!"
#undef CARTESIAN_IS_STANDARD
#ifdef SPHERE_IS_STANDARD
#undef CYLINDER_IS_STANDARD
#warning "Sphere system will be standart!"
#endif
#warning "Cylinder system will be standart!"

#endif

#ifdef POLAR_IS_STANDARD
#ifdef CARTESIAN_IS_2D_STANDARD
#undef CARTESIAN_IS_2D_STANDARD
#warning                                                                                           \
    "Warning: You defined polar coordinates as standard and cartesian as 2D standard. Polar will be standard."
#endif
#endif

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD) ||                               \
     defined(CARTESIAN_IS_3D_STANDARD) || defined(POLAR_IS_STANDARD) ||                            \
     defined(CARTESIAN_IS_2D_STANDARD))
#define SYSTEM_IS_SET
#else
#error "FATAL ERROR NO SYSTEM SET"
#endif

#if (defined(SYSTEM_IS_SET) && defined(ANGLE_UNIT_SET))
#define SYSTEM_READY

#endif


   
  


#endif //DK_MACROS_HPP