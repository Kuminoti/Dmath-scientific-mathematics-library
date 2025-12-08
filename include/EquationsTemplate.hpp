#pragma once 

#ifndef DMATH_EUQATION_HPP
#define DMATH_EUQATION_HPP

#include"mathFunction.hpp"
#include"dataTypes.hpp"
#include"complexFunctions.hpp"
#include"vectorfunction.hpp"


NAMESPACESTART

/* this file contains a builder pattern for specific equations
 * like: quadratic equations, linear equations, etc.
*/

#pragma region MathFunctionBuilders

//Linear equation builder
// This function returns a lambda that represents a linear equation of the form y = ax + b
Dmath::SingleVarFunction linerarEquation(Dmath::Scalar a, Dmath::Scalar b) {
    return [a, b](double x) -> double {
        return a * x + b;
    };
}

//Quadratic equation builder
Dmath::SingleVarFunction quadraticEquation(Dmath::Scalar a, Dmath::Scalar b, Dmath::Scalar c) {
    return [a, b, c](double x) -> double {
        return a * std::pow((x+b), 2)  + c;
    };
}

//cubic equation builder
// y = ax³ + bx² + cx + d
Dmath::SingleVarFunction cubicEquation(Dmath::Scalar a, Dmath::Scalar b, Dmath::Scalar c, Dmath::Scalar d) {
    return [a, b, c, d](double x) -> double {
        return a * x * x * x + b * x * x + c * x + d;
    };
}

//Exponential equation builder
// y = a * b^x
Dmath::SingleVarFunction exponentialEquation(Dmath::Scalar a, Dmath::Scalar b) {
    return [a, b](double x) -> double {
        return a * std::pow(b, x);
    };
}

//Logarithmic equation builder
// y = a * log_b(x)
Dmath::SingleVarFunction logarithmicEquation(Dmath::Scalar a, Dmath::Scalar b) {
    return [a, b](double x) -> double {
        Dmath::Scalar logValue = a * Dmath::logarithm(b,x);
        if (logValue == 0) {
            throw std::invalid_argument("Logarithm of zero is undefined.");
            return 0;
        }
        return logValue;
    };
}



//jacobiDeterminantSpherecoordinates
// This function returns a lambda that calculates the Jacobian determinant for spherical coordinates
Dmath::DoubleVarFunction jacobiDeterminantSphere(){
    return [](double r, double theta) ->double {
        // Jacobian determinant for spherical coordinates: r^2 * sin(theta)
        return r * r * std::sin(theta);
    };
}

// Jacobi determinant for cylindrical coordinates
Dmath::DoubleVarFunction jacobiDeterminantCylindrical() {
    return [](double r, double theta) -> double {
        // Jacobian determinant for cylindrical coordinates: r
        return r;
    };
}

#pragma endregion //MathFunctionBuilders


#pragma region VectorFunctionBuilders

Dmath::SingleVectorFunction circleEquation(Dmath::Scalar radius) {
    return Dmath::SingleVectorFunction(
        [radius](double t) -> double { return radius * std::cos(t); }, // x(t)
        [radius](double t) -> double { return radius * std::sin(t); }  // y(t)
    );
}


Dmath::SingleVectorFunction unitCircle() {
    return Dmath::SingleVectorFunction(
        [](double t) -> double { return std::cos(t); }, // x(t)
        [](double t) -> double { return std::sin(t); }  // y(t)
    );
}

Dmath::SingleVectorFunction elipseEquation(Dmath::Scalar a, Dmath::Scalar b) {
    return Dmath::SingleVectorFunction(
        [a](double t) -> double { return a * std::cos(t); }, // x(t)
        [b](double t) -> double { return b * std::sin(t); }  // y(t)
    );
}


Dmath::SingleVectorFunction helixEquation(Dmath::Scalar radius, Dmath::Scalar height) {
    return Dmath::SingleVectorFunction(
        [radius](double t) -> double { return radius * std::cos(t); }, // x(t)
        [radius](double t) -> double { return radius * std::sin(t); }, // y(t)
        [height](double t) -> double { return height * t; }            // z(t)
    );
}
// x(t) = a * cosh(t/a)
// y(t) = t 
Dmath::SingleVectorFunction ropeCurve(Dmath::Scalar a){
    return Dmath::SingleVectorFunction(
        [a](double t) -> double { return a * std::cosh(t / a); }, // x(t)
        [](double t) -> double { return t; }                      // y(t)
    );
}


//Wurfparabel
Dmath::SingleVectorFunction parabolicTrajectory(Dmath::Scalar v, Dmath::Scalar angle, double height){
    Dmath::SingleVarFunction xOfT = [v,angle,height](double t){
        return v * std::cos(angle) * t; // x(t)
    };
    Dmath::SingleVarFunction yOfT = [v,angle,height](double t){
        return   height + v * std::sin(angle) * t - 0.5* 9.81 * t   * t ; // y(t)
    };
    return Dmath::SingleVectorFunction(xOfT, yOfT);
}

Dmath::DoubleVectorFunction sphereEquation(Dmath::Scalar radius) {
    return Dmath::DoubleVectorFunction(
        [radius](double u, double v) -> double { return radius * std::sin(u) * std::cos(v); }, // x(u, v)
        [radius](double u, double v) -> double { return radius * std::sin(u) * std::sin(v); }, // y(u, v)
        [radius](double u, double v) -> double { return radius * std::cos(u); }                // z(u, v)
    );
}


#pragma endregion //VectorFunctionBuilders

NAMESPACEEND

#endif //DMATH_EUQATION_HPP