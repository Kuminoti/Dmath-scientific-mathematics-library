#pragma once 

#ifndef DMATH_FUNCTIONAL_HPP
#define DMATH_FUNCTIONAL_HPP


/*
 * File: mathFunction.hpp
 *
 * This file defines a custom function wrapper that mimics the behavior 
 * of std::function, specifically optimized for handling mathematical 
 * functions represented as double lambda expressions.
 * 
 * Example: f(x) = x² ; code [](double x) ->double { return (x*x); };
 * 
 * The primary  purpose of this class is to provide a flexible and type-safe
 * way to store and invoke mathematical functions that take a single double 
 * argument and return a double value.
 * 
 * Definition:
 * a function describes a relationship between two sets that assigns exactly 
 * one element of the other set (function value, dependent variable, y, y-value)
 * to each element of one set   (function argument, independent variable, x, x-value).
 *
 * Key Features:
 * - Supports any callable that matches the signature `double(double)`.
 * - Provides an interface for invoking stored functions.
 * - Can be easily integrated into existing C++ codebases.
 * 
 */


#include"macros.hpp"
#include"dataTypes.hpp"
#include"mathVector.hpp"
#include"mathmaticalCondition.hpp"
#include"dFunctions.hpp"
#include<memory>
#include<windows.h>


NAMESPACESTART

#pragma region BASECLASS

//Base class for the other classes


// Basis-Klasse für Funktionen
// Base class for functions
class FunctionBase {
public:
    FunctionBase() = default;
    virtual ~FunctionBase() = default;
    virtual double Call() = 0;
    virtual double Callx(double x) = 0;             // For f(x)
    virtual double CallXY(double x, double y) = 0;  // For f(x, y)
    virtual double CallXYZ(double x, double y, double z) = 0; //For f(x,y,z)


    virtual std::shared_ptr<FunctionBase> clone() const = 0;
};

#pragma endregion



#pragma region FUNCWRAPPER

template<typename Func>
class FunctionWrapperConst : public FunctionBase {
private:
    Func func;

public:
    FunctionWrapperConst(Func function) : func(function){}

    double Call() override {  return func(); }

    double Callx(double x) override {
        throw std::runtime_error("This function does not support Callx."); // Not implemented for double variable function
    }

    double CallXY(double x, double y) override {
        throw std::runtime_error("This function does not support Callxy."); // Not implemented for double variable function
    }
    double CallXYZ(double x, double y, double z) override {
        throw std::runtime_error("This function does not support Callxy."); // Not implemented for double variable function

    }

    std::shared_ptr<FunctionBase> clone() const override {
        return std::make_shared<FunctionWrapper<Func>>(*this);
    }

};

// Template class for function functionality
template<typename FuncX>
class FunctionWrapper : public FunctionBase {
private:
    FuncX singleFunction;       // Function for f(x)

public:
    // Constructor for single variable function
    FunctionWrapper(FuncX funX) : singleFunction(funX) {}

    double Call() override {
        throw std::runtime_error("Error0");
    }

    double Callx(double x) override { return singleFunction(x); }

    double CallXY(double x, double y) override {
        throw std::runtime_error("Single variable function does not support CallXY."); // Not implemented for single variable function
    }

    double CallXYZ(double x, double y, double z) override {
        throw std::runtime_error("Single variable function does not support CallXY."); // Not implemented for single variable function
    }

    std::shared_ptr<FunctionBase> clone() const override {
    return std::make_shared<FunctionWrapper<FuncX>>(*this);
}

};

template<typename FuncXY>
class FunctionWrapperXY : public FunctionBase {
private:
    FuncXY doubleFunction;      // Function for f(x, y)

public:
    // Constructor for double variable function
    FunctionWrapperXY(FuncXY funXY) : doubleFunction(funXY) {}

    double Call() override {
        throw std::runtime_error("Error0");
    }

    double Callx(double x) override {
        throw std::runtime_error("This function does not support Callx."); // Not implemented for double variable function
    }

    double CallXY(double x, double y) override {
        return doubleFunction(x, y); // Call for f(x, y)
    }
    double CallXYZ(double x, double y, double z) override {
        throw std::runtime_error("Single variable function does not support CallXY."); // Not implemented for single variable function
    }

    std::shared_ptr<FunctionBase> clone() const override {
        return std::make_shared<FunctionWrapperXY<FuncXY>>(*this);
    }
};

template<typename FuncXYZ>
class FunctionWrapperXYZ : public FunctionBase{
private:
    FuncXYZ tripleFunc;

public:
    FunctionWrapperXYZ(FuncXYZ funXYZ) : tripleFunc(funXYZ) {}

    double Call() override {
        throw std::runtime_error("Error0");
    }

    double Callx(double x) override {
        throw std::runtime_error("This function does not support Callx."); // Not implemented for double variable function
    }

    double CallXY(double x, double y) override {
        throw std::runtime_error("This function does not support Callxy."); // Not implemented for double variable function
    }
    double CallXYZ(double x, double y, double z) override {
        return tripleFunc(x,y,z);
    }
    std::shared_ptr<FunctionBase> clone() const override {
        return std::make_shared<FunctionWrapperXYZ<FuncXYZ>>(*this);
    }
    
};

#pragma endregion

#pragma region Function


class SHARED_LIB Function{

private: // Private members:
    std::shared_ptr<FunctionBase> funcBase;

public: 

    Function& operator=(const Function& other){
        if (this != &other) {
            this->funcBase = other.funcBase ? other.funcBase->clone() : nullptr;
        }
        return *this;
    }

    template<typename Callable>
    Function& operator=(Callable func) {
        this->funcBase = std::make_shared<FunctionWrapperConst<Callable>>(func);
        return *this;
    }

    // Move-Zuweisung
    Function& operator=(Function&& other) noexcept {
        if (this != &other) {
            this->funcBase = std::move(other.funcBase);
        }
        return *this;
    }




    template<typename Callable>
    Function(Callable func) : funcBase(std::make_shared<FunctionWrapperConst<Callable>>(func)) {}

    Function(const Function& other)
    : funcBase(other.funcBase ? other.funcBase->clone() : nullptr) {}

    Function() = default;


    double operator()() {
        if (funcBase) {
            return funcBase->Call(); // Delegate the call to the stored function
        }
        return 0.0; // Return a default value if no function is stored
    }

};



#pragma endregion




#pragma region SINGLE

class SHARED_LIB SingleVarFunction {

private: //Private members:
    std::shared_ptr<FunctionBase> funcBase; // Smart pointer for memory management
   
    double dx = 0.000001;

    
    

    bool conditionSet = false;

private: //private methods: 

    bool checkParams(Dmath::Parameters params);


public: //public getters
    double getDataAt(double x){ return this->funcBase->Callx(x);  }


public: //operator overloading


    SingleVarFunction& operator=(const SingleVarFunction& other) {
    if (this != &other) {
        funcBase = other.funcBase ? other.funcBase->clone() : nullptr;
    }
    return *this;
}

    // Lambda-Zuweisung
    template<typename Callable>
    SingleVarFunction& operator=(Callable func) {
        funcBase = std::make_shared<FunctionWrapper<Callable>>(std::move(func));
        return *this;
    }

    // Move-Zuweisung
    
    SingleVarFunction& operator=(SingleVarFunction&& other) noexcept = default;


    /* Calculates the number of elements for exapmle if you want
     * to create the derivative 
     * Parameters is a datatype wich holds 3 values:
     * @param 1. param.one   = start
     * @param 2. param.two   = end
     * @param 3. param.three = stepps or resolution
     */
    size_t numOfElements(Dmath::Parameters param);

public:


    template<typename Callable>
    SingleVarFunction(Callable func)
        : funcBase(std::make_shared<FunctionWrapper<Callable>>(std::move(func))) {}

    SingleVarFunction(const SingleVarFunction& other) : funcBase(other.funcBase ? other.funcBase->clone() : nullptr) {}

    SingleVarFunction() = default;

    // Move-Konstruktor
SingleVarFunction(SingleVarFunction&& other) noexcept
    : funcBase(std::move(other.funcBase)) {}

//Operator overloading

    double operator()(double x) const;
    
    
    
    SingleVarFunction operator+ ( Function funcOne) const;
    SingleVarFunction operator- ( Function funcOne) const;
    SingleVarFunction operator* ( Function funcOne) const;
    SingleVarFunction operator/ ( Function funcOne) const;
    
    
    SingleVarFunction operator+ (SingleVarFunction funcOne) const;
    SingleVarFunction operator- (SingleVarFunction funcOne) const;
    SingleVarFunction operator* (SingleVarFunction funcOne) const;
    SingleVarFunction operator/ (SingleVarFunction funcOne) const;

    SingleVarFunction operator+ (Dmath::Scalar num) const;

    /* Nests one function in an other, for example:
     * (f * g)(x) := f(g(x))
    */
    SingleVarFunction composition(SingleVarFunction fOfX, SingleVarFunction gOfX) const;
    SingleVarFunction compose(SingleVarFunction func) const;

    /*
        * This method, getFunctionVector, returns a vector filled with all function values
        * from a given start point (argument one) to an end point (argument two) in specified steps
        * (argument three).
        *
        * @param start The starting point for the function evaluations.
        * @param stopp The end point for the function evaluations.
        * @param stepps The step size between evaluations.
        * @return A vector containing the function values. Returns an empty vector if 
        *         the start point is greater than or equal to the stop point or if
        *         the step size is non-positive.
    */

    std::vector<double> getFunctionVector(Dmath::Parameters params);

    /*
        * This method, getDerivativeVector, computes the derivative of a mathematical function 
        * represented by a callable object stored in funcBase. The derivative is calculated using 
        * the central difference method, which approximates the derivative by evaluating the 
        * function at points slightly above and below a given x-value (using a small delta, dx).
        * 
        * Parameters:
        * - start: The starting point for the derivative calculation.
        * - stopp: The endpoint for the derivative calculation.
        * - stepps: The step size between successive x-values.
        *
        * Returns:
        * A vector containing the computed derivative values at each step from 'start' to 'stopp'.
        * If the input parameters are invalid (start >= stopp or stepps <= 0), an empty vector is returned.
    */

    std::vector<double> getDerivativeVector(Dmath::Parameters params);

    /*
        * This method calculates the approximate anti-derivative (integral) values of a mathematical function
        * over a specified range defined by 'start' and 'stopp' with specified step sizes 'stepps'.
        * 
        * @param start   The starting point of the integration range.
        * @param stopp   The endpoint of the integration range.
        * @param stepps  The step size for discretizing the range into intervals.
        * 
        * @return       A vector of double values representing the accumulated integral values at each step.
        * 
        * The method checks the validity of the input parameters and returns an empty vector if they are invalid.
        * It utilizes the trapezoidal rule for numerical integration, accumulating the area under the curve
        * of the function defined by the stored function pointer (funcBase).
        * Each integral value is calculated by evaluating the function at the current x value and
        * multiplying it by the differential element 'dx'.
    */

    std::vector<double> getSecondDerivative(Dmath::Parameters params);

    std::vector<double> getAntiDerivativeVector(Dmath::Parameters params);


    //returns the first and second derivative at a given point as a scalar value
    Dmath::Scalar getDerivativeAt(Dmath::Scalar x);
    Dmath::Scalar getSecondDerivativeAt(Dmath::Scalar x);

    //returns the first and second derivative as a function object 
    SingleVarFunction getDerivative();
    SingleVarFunction getSecondDerivative();

};

#pragma region DOUBLE

class SHARED_LIB DoubleVarFunction {
private:
    std::shared_ptr<FunctionBase> funcBase; // Smart pointer for the function
   
    double dx = 0.0000001;

private:
    bool checkParams(Dmath::Parameters params);

public: //Public construtors:

    // Default constructor
    DoubleVarFunction() = default; 

    // Callable-Konstruktor (Lambda, Functor, std::function, ...)
    template<typename FuncXY>
    DoubleVarFunction(FuncXY func)
        : funcBase(std::make_shared<FunctionWrapperXY<FuncXY>>(std::move(func))) {}

    // Copy-Konstruktor (tiefe Kopie)
    DoubleVarFunction(const DoubleVarFunction& other)
        : funcBase(other.funcBase ? other.funcBase->clone() : nullptr) {}

    // Move-Konstruktor
    DoubleVarFunction(DoubleVarFunction&&) noexcept = default;

public: //public operators

    // Operator to call the function with two arguments (x, y)
    Dmath::Scalar operator()(Dmath::Scalar x, Dmath::Scalar y) const;
    Dmath::Scalar operator()(Dmath::Vec2D vector) const;

    DoubleVarFunction& operator=(const DoubleVarFunction& other);//

    DoubleVarFunction operator+(DoubleVarFunction funcOne);
    DoubleVarFunction operator-(DoubleVarFunction funcOne);
    DoubleVarFunction operator*(DoubleVarFunction funcOne);
    DoubleVarFunction operator/(DoubleVarFunction funcOne);


 DoubleVarFunction& operator=(DoubleVarFunction&&) noexcept = default;

   template<typename Callable>
    DoubleVarFunction& operator=(Callable func) {
        funcBase = std::make_shared<FunctionWrapperXY<Callable>>(std::move(func));
        return *this;
    }


public: //public getters
    std::vector<double> getFunctionVector (Dmath::Parameters params);

    //Retuns a std::vector filled with parital derivatives
    std::vector<double> getPartialDerivteX(Dmath::Parameters params);
    std::vector<double> getPartialDerivteY(Dmath::Parameters params);

    //Retuns the parital derivative as a function object
    DoubleVarFunction getPartialX();
    DoubleVarFunction getPartialY();


    

    std::vector<double> getAntiDerivativeX(Dmath::Parameters params);
    std::vector<double> getAntiDerivativeY(Dmath::Parameters params);


public: //mathmatical operations

    //First derivative at a specific point
    Dmath::Scalar derivativeXAT(Dmath::Scalar x, Dmath::Scalar y);
    Dmath::Scalar derivativeYAT(Dmath::Scalar x, Dmath::Scalar y);

    //Second derivative at a specific point 
    Dmath::Scalar secondDerivativeXX(Dmath::Scalar x, Dmath::Scalar y);
    Dmath::Scalar secondDerivativeXY(Dmath::Scalar x, Dmath::Scalar y);
    Dmath::Scalar secondDerivativeYY(Dmath::Scalar x, Dmath::Scalar y);
    Dmath::Scalar secondDerivativeYX(Dmath::Scalar x, Dmath::Scalar y);

    //for f(g(x),h(x))
    DoubleVarFunction composition(Dmath::DoubleVarFunction mainFunc ,SingleVarFunction fOfX, SingleVarFunction gOfX);

public: //helper methods
    size_t numOfElements(Dmath::Parameters params);
};


#pragma endregion //double



#pragma region TRIPPLE

class SHARED_LIB TripleVarFunction{
private:
    std::shared_ptr<FunctionBase> funcBase;
     double dx = 0.0000001;


    bool checkParams(Dmath::Parameters params);
    size_t numberOfElements(Dmath::Parameters params);

public: // Public constructors:

    //default constructor
    TripleVarFunction() = default;


    /////////////////////////////////////////////////////////
    // Callable-Konstruktor (Lambda, Functor, std::function, ...)
    template<typename FuncXYZ>
    TripleVarFunction(FuncXYZ func)
        : funcBase(std::make_shared<FunctionWrapperXYZ<FuncXYZ>>(std::move(func))) {}
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
   TripleVarFunction(const TripleVarFunction& other)
        : funcBase(other.funcBase ? other.funcBase->clone() : nullptr) {}
///////////////////////////////////////////////////////

public: //public operators
    // Operator to call the function with three arguments (x, y, z)
    Dmath::Scalar operator()(double x, double y, double z);
    Dmath::Scalar operator()(Dmath::Vec3D vector);

    TripleVarFunction operator+(Dmath::TripleVarFunction funcOne);
    TripleVarFunction operator-(Dmath::TripleVarFunction funcOne);
    TripleVarFunction operator*(Dmath::TripleVarFunction funcOne);
    TripleVarFunction operator/(Dmath::TripleVarFunction funcOne);

    // Assignment operator for TripleVarFunction//////////////////
    TripleVarFunction& operator=(const TripleVarFunction& other);
    //////////////////////////////////////////////////////////////


    // Lambda-Zuweisung
    // Lambda / Callable-Zuweisung
    template<typename Callable>
    TripleVarFunction& operator=(Callable func) {
        funcBase = std::make_shared<FunctionWrapperXYZ<Callable>>(std::move(func));
        return *this;
    }

    // Move-Zuweisung
    TripleVarFunction& operator=(TripleVarFunction&&) noexcept = default;

public: //public mathmatical operations

    std::vector<double> getFunctionVector (Dmath::Parameters params);

    std::vector<double> getPartialDerivteX(Dmath::Parameters params);
    std::vector<double> getPartialDerivteY(Dmath::Parameters params);
    std::vector<double> getPartialDerivteZ(Dmath::Parameters params);


    std::vector<double> getAntiDerivativeX(Dmath::Parameters params);
    std::vector<double> getAntiDerivativeY(Dmath::Parameters params);
    std::vector<double> getAntiDerivativeZ(Dmath::Parameters params);

   // std::vector<Dmath::Vec3D> getGradient(double start, double stopp, double stepps);

   Dmath::Scalar derivativeXAt(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z);
   Dmath::Scalar derivativeYAt(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z);
   Dmath::Scalar derivativeZAt(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z);

};

#pragma endregion //Tripple

NAMESPACEEND

#endif //DMATH_FUNCTIONAL_HPP