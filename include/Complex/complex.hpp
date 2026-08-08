#pragma once

#ifndef DMATH_COMPLEX_HPP
#define DMATH_COMPLEX_HPP

#include"../Vector/mathVector.hpp" //To convert the data from the complex plane to a vector in cartesian coordinates
#include"../Utils/dFunctions.hpp" //Helper function

/* File include/Complex.hpp 
 * This File contains a class for Complex Numbers und fitting mathmaticals operations
 *
 * Z = aX + ib => ∀( a,b ) ∈ R; i ∈ Q ; i² = -1
*/




NAMESPACESTART //Dmath:: - namespace


struct ImaginaryNumber{
    Dmath::Scalar i;

    // Konstruktor
    ImaginaryNumber(Dmath::Scalar bi) : i(bi) {}

    // Addition
    ImaginaryNumber operator+(ImaginaryNumber i_two) const {
        return ImaginaryNumber(this->i + i_two.i);
    }

    // Subtraktion
    ImaginaryNumber operator-(ImaginaryNumber i_two) const {
        return ImaginaryNumber(this->i - i_two.i);
    }

    // Multiplikation
    ImaginaryNumber operator*(Dmath::Scalar scalar) const {
        return ImaginaryNumber(this->i * scalar);
    }

    // Division
    ImaginaryNumber operator/(Dmath::Scalar scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return ImaginaryNumber(this->i / scalar);
    }

    // Vergleichsoperatoren
    bool operator==(ImaginaryNumber i_two) const {
        return this->i == i_two.i;
    }

    bool operator!=(ImaginaryNumber i_two) const {
        return this->i != i_two.i;
    }

    // Ausgabeoperator
    friend std::ostream& operator<<(std::ostream& os, const ImaginaryNumber& num) {
        os << num.i << "i";
        return os;
    }

} ;
class Complex{

private:
    //real and ImaginaryNumber parts
    double real;
    double img;

    
    double absolute; //The "distance" from the coordinate origin
    double phaseAngle = 0;

    //Calculates the angle and abs after a manipulations
    void update();

public:

    Complex();                          //default Constructor
    Complex(double real, double img);
    Complex(double real, ImaginaryNumber img);   


    //getters
    double getRealPart();
    double getImaginaryPart();
    double getAbsolute();


    //Adders

    //Adds img to the ImaginaryNumber part : x + (iy + iimg)
    void addImaginary(double img);
    void addReal(double real);

    void setNumber(double real, double img);

    //Setters for the real and ImaginaryNumber part
    void setImaginaryPart(double img);
    void setRealPart(double real);


    void conjugate();


    void operator=(Complex num);

    //Logic operators
    bool operator==(Complex num);
    bool operator!=(Complex num);

    bool operator==(Dmath::Scalar num);
    bool operator!=(Dmath::Scalar num);
    

    bool operator< (Complex num);
    bool operator> (Complex num);
    bool operator<=(Complex num);
    bool operator>=(Complex num);


    bool operator< (Dmath::Scalar num);
    bool operator> (Dmath::Scalar num);
    bool operator<=(Dmath::Scalar num);
    bool operator>=(Dmath::Scalar num);

    //Mathmatical operators
    Complex operator+(Complex num);
    Complex operator-(Complex num);

    Complex operator*(Complex num);
    Complex operator/(Complex num);
    Complex operator/(Dmath::Scalar num);

    Complex& operator+=(const Complex& num);
    Complex& operator-=(const Complex& num);

    

    Complex exp(); //e^this

    //Returns a vector in Cartesian coordinats with the real and ImaginaryNumber parts on the complex plane as x and y coordinates
    Dmath::Vec2D getVector();

    CoordinateSystem2D polarForm();

};

std::ostream& operator<<(std::ostream& os, Dmath::Complex num);

NAMESPACEEND

#endif