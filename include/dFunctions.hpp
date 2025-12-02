#pragma once

#ifndef D_FUNCTIONS_HPP
#define D_FUNCTIONS_HPP

#include"dataTypes.hpp" 
#include<random>
#include<limits>


NAMESPACESTART



//Mathmatical operations:

 auto sec  = [](double x) ->double {return 1/std::cos(x); };
 auto cec  = [](double x) ->double {return 1/std::sin(x); };
 auto cot  = [](double x) ->double {return 1/std::tan(x); };

 auto asec = [](double x) ->double { return std::acos(1/x); };
 auto acsc = [](double x) ->double { return std::asin(1/x); };
 auto acot = [](double x) ->double {
    if(x < 0){
        return (std::atan(1/x) + PI);
    }
    return std::atan(1/x);
 };

 auto cosh = [](double x) ->double { return (std::exp(x) + std::exp(-x)) / 2; };    
 auto sinh = [](double x) ->double { return (std::exp(x) - std::exp(-x)) / 2; };   

auto greaterThan = [](double greater,double than)->bool {
    if(greater > than){
        return true;
    }
    return false;
};

auto smallerThan = [](double smaller, double than)->bool {
    if(smaller < than){
        return true;
    }
    return false;
};


/* Functions for calculating derivarives and defined integrals, for the Dmath::singleVarFunction a typedef
 * for: std::function<double(double)> 
 * defined: datatypes.hpp 
 * Line: 16
*/


//Calculates the derivative an a given point
SHARED_LIB double derivativeAt(Dmath::singleVarFunction func, double point);

//Calculates all the derivatives in a given range in between given intervalls 
SHARED_LIB std::vector<Dmath::Scalar> derivativeVector(Dmath::singleVarFunction, double start, double end, double res);


auto sleep = [](size_t millis) ->void { std::this_thread::sleep_for(std::chrono::milliseconds(millis));};


auto sleepMicros = [](size_t micros) -> void { std::this_thread::sleep_for(std::chrono::microseconds(micros)); };


SHARED_LIB double pyth2(double a, double b);


SHARED_LIB double pyth3(double x, double y, double z);

SHARED_LIB double roundTo(double value, int digits);


//Summation Σ
SHARED_LIB double SigmaAdd(size_t start, size_t end);


SHARED_LIB double sigmaAddFunc(size_t start, size_t end, Dmath::singleVarFunction mainFunc);

//Helper function to calculate the number of total elements 
SHARED_LIB size_t numberOfElements(Dmath::Parameters params);

//Checks if parameters are correkt
SHARED_LIB bool checkParams(Dmath::Parameters params);

//Converts Kelvin to °F
SHARED_LIB double kelvinToCelsius(double Kelvin);

//converts °C to K
SHARED_LIB double CelsiusToKelvin(double celsius);

//Converts °F to °C
SHARED_LIB double fahrenheitToCelsius(double fahrenheit);


SHARED_LIB double celsiusToFahrenheit(double celsius);

SHARED_LIB double milesToKm(double miles);
SHARED_LIB double kmToMiles(double km);

// Pfund <-> Kilogramm
SHARED_LIB double poundsToKg(double pounds);

SHARED_LIB double kgToPounds(double kg);

// Bar <-> PSI
SHARED_LIB double barToPsi(double bar);

SHARED_LIB double psiToBar(double psi);



SHARED_LIB double radiansToDegrees(double radiants);

SHARED_LIB double degreesToRadians(double degrees);




SHARED_LIB double fDotProduct(Dmath::sVec2f vecOne, Dmath::sVec2f);

SHARED_LIB size_t iDotProduct(Dmath::sVec2i vecOne, Dmath::sVec2i vecTwo);

SHARED_LIB double fDotProduct(Dmath::sVec3f vecOne, Dmath::sVec3f vecTwo);

//Warning can lead to overflow!
SHARED_LIB size_t binomialCoefficient(size_t n, size_t k);

SHARED_LIB double gammaFunction(double x);

SHARED_LIB double psiFunction(double x);

SHARED_LIB double average(std::vector<double> input);

// this functions will return a function object
SHARED_LIB double lorenzFactor(double v);



//The digit Sum of a number is the sum of the individual digits of the number
SHARED_LIB int digitSum(int number);

// Function: Random Number Generator
SHARED_LIB size_t randomNumber(size_t min, size_t max);

NAMESPACEEND

#endif 