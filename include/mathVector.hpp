#pragma once



#ifndef VECTORMATH_H
#define VECTORMATH_H //include guard

#pragma region FILE

/*
 * File: include/mathVector.hpp
 *
 * This File contains the classes for 2D and 3D Vectors and all importent mathmatical
 * and geometric operations
 * 
 */


#include "systems.hpp"          //Vec2D and Vec3D inherit form Coordinatesystem2D and ...3D

#ifdef SYSTEM_READY             //Checks if all the right coordinatesystem is selected

#include<iostream>              //For the << operator
#include"Matrix.hpp"            //For linear Transfomations
#include"systemGeometry.hpp"    //For geometric operations


NAMESPACESTART

#pragma region Vec2D
class Vec2D : public CoordinateSystem2D {                          //CoordinateSystem2D contains the actual coordinates for cartesian and polar systems
  private: //Private members
  Dmath::Scalar abs;                                               // The absolute value or lenght of a vector
  Dmath::Scalar distanceToZero;   
  Dmath::Scalar vectorRotation; 

    void calcAbs();                                                // Calculates the absolute value
    void ValidManipulation();

  public: // Basic operrator overloading:
    
    //Mathmatical operators
    Vec2D  operator*(const Dmath::Scalar scalarValue);                    //Multiplys x and y by scalarValue   
    Vec2D  operator/(const Dmath::Scalar scalarValue);                    //divides all components of the Vector with the scalar value and returns it
    Vec2D  operator+(const Vec2D& Mathvector);                            //Basic Vector addition
    Vec2D  operator-(const Vec2D& Mathvector);                            //Basic Vector subtractions
    Dmath::Scalar operator*(const Vec2D& Mathvector);                     //Calculates the dotproduct of two vectors
    Dmath::Vec2D  operator*( Dmath::Matrix<Dmath::Scalar> matrix);  //Linear transformation


    void operator+=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data);       // this x-value + Duo.one ; this y-value + Duo.two
    void operator-=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data);       // this x-value - Duo.one ; this y-value - Duo.two
    void operator*=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data);       // this x-value * Duo.one ; this y-value * Duo.two
    void operator/=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data);       // this x-value / Duo.one ; this y-value / Duo.two
    

    void operator+=(Dmath::sVec2f vec);                                 // this x-value + sVec.x; this y-value + sVec.y 
    void operator-=(Dmath::sVec2f vec);                                 // this x-value - sVec.x; this y-value - sVec.y
    void operator*=(Dmath::sVec2f vec);                                 // this x-value * sVec.x; this y-value * sVec.y
    void operator/=(Dmath::sVec2f vec);                                 // this x-value / sVec.x; this y-value / sVec.y

    void operator+=(Dmath::Scalar scalar);                              // this y-value + scalar; this y-value + scalar
    void operator-=(Dmath::Scalar scalar);                              // this y-value - scalar; this y-value - scalar
    void operator*=(Dmath::Scalar scalar);                              // this y-value * scalar; this y-value * scalar
    void operator/=(Dmath::Scalar scalar);                              // this y-value / scalar; this y-value / scalar


    void operator+=(Vec2D vec);                                         // this x-value + vec.X  ; this y-value + vec.x
    void operator-=(Vec2D vec);                                         // this x-value - vec.X  ; this y-value - vec.x
    void operator*=(Vec2D vec);                                         // this x-value * vec.X  ; this y-value * vec.x
    void operator/=(Vec2D vec);                                         // this x-value / vec.X  ; this y-value / vec.x

    void addXYEach(Dmath::Scalar xPlus, Dmath::Scalar yPlus);           //* X + xPlus     || Y + yPlus
    void divideXYBy(Dmath::Scalar xDivBy, Dmath::Scalar yDivBy);        //* X / xDivBy    || Y / yDivBy
    void multilpyXY(Dmath::Scalar xTimes, Dmath::Scalar yTimes);        //* X * xTimes    || Y * yTimes
    void subtractXY(Dmath::Scalar xMinus, Dmath::Scalar yMinus);        //* X - xMinus    || Y - yMinus


    void operator++();                                             //Adds 1 to the x and y coordinate
    void operator--();                                             //Adds 1 to the x and y coordinate

    void operator=(Dmath::sVec2f vec);
    void operator=(Dmath::Duo<double, double> duo);

    //Logic operators
    inline bool operator==(Vec2D& Mathvector);   // == checks if the x and y coordinates are the same
    inline bool operator!=(Vec2D& Mathvector);   // != checks if the x and y coordinates are diffrent
    inline bool operator>=(Vec2D& Mathvector);   // >= checks if the lenght of the vector is greater or equal
    inline bool operator<=(Vec2D& Mathvector);   // <= checks lenght ...
    inline bool operator<(Vec2D& Mathvector);    // lenght1 < lenght2 ... 
    inline bool operator>(Vec2D& Mathvector);    // lenght1 > lenght2

    
    bool isEqual(Dmath::Vec2D);                  //Checks if !ALL! values of two vectors are the same

  public: //Public Constructors
#ifdef CARTESIAN_IS_2D_STANDARD
    Vec2D() = default;                                                        //Default constructor (duh...)
    Vec2D(Dmath::Scalar XY);                                                  // creates a Vector with the same x and y value
    Vec2D(Dmath::Scalar X, Dmath::Scalar Y);                                  // basic x and y vector
    Vec2D(Dmath::Scalar X, Dmath::Scalar Y, Dmath::Scalar originX, Dmath::Scalar originY);  // crates a vector with a specific non zero startpoint
#endif // CARTESIAN_IS_2D_STANDARD

#ifdef POLAR_IS_STANDARD
    Vec2D(double radius, double phi);                           // Creates a Vector in a polar coordinatesystem
#endif // POLAR_IS_STANDARD

   virtual ~Vec2D() = default;

  public: //getters and setters

    /* Setters:
     *
     * If data is set/changed it will automaticly change the values for other
     * coordinate types as well.
     * 
     * And calculate the absolute value, or length, of the vector
     */

     Dmath::Scalar getRotationAngle();                           // Gets the rotation angle for rotated vectors
     Dmath::Scalar getAbs();                                     // Calculates the absolutvalue
     Dmath::Scalar getLenght();                                  // Calculates the length of a vector

    
    void setX(const Dmath::Scalar value);                        // Basic x setter
    void setY(const Dmath::Scalar value);                        // Basic y setter
    void setPhi(const Dmath::Scalar value);                      // Setter for the angle in a polar system
    void setAll(const Dmath::Scalar value);                      // Sets ALL values to...
    void setRadius(const Dmath::Scalar radius);                  // Setter for the radius in a polar system
    


  public: //Mathmatical operations
    Dmath::Scalar wedgeProduct(Vec2D MathVector);
    Dmath::Scalar dotProduct(Vec2D Mathvector);                  // Calculates Scalar product
    Dmath::Scalar calcAngle(Vec2D Mathvector);                   // Calculates the angle between 2 vectors
    Dmath::Scalar distance(Vec2D Mathvector);                    // Calculates the distance between vectors
    void normalize();                                            // Divides the vectors components though its length

    // You can use methods instead of overloaded operators
    Vec2D add(Vec2D Mathvector);                                 // Adding 2 vectors
    Vec2D subtract(Vec2D Mathvector);                            // Subtract 2 vectors
    Vec2D rotateVector(Dmath::Scalar radians);                   // Rotates a vector dependent op the angle
    

   

  public: //Geometric operations                 
    Dmath::Scalar polarSystemArea();                             // Calculates the circle of a polar system
    Dmath::Scalar polarSystemCircumfrance();                     // Calculates the circumfrance of a polar system
    Dmath::Scalar rectangleArea(Vec2D MathVector);               // Calculates the area of a rectangle
    Dmath::Scalar rectangleCircumfrance(Vec2D MathVector);       // Calculates the circumfrance of the rectangle

  public: //vector manipulation
   
 
    void addToX(Dmath::Scalar add); // X + add
    void addToY(Dmath::Scalar add); // Y + add


    

    void addToThis(Dmath::Scalar add);                                  //* X + add       ||  Y + add
    void substractThis(Dmath::Scalar subtract);                  //* X - subtract  ||  Y - subtract
    void multipyThisBy(Dmath::Scalar factor);                    //* X * factor    ||  Y * factor
    void divideThisBy(Dmath::Scalar quotient);

    void subtractFromX(Dmath::Scalar subtract);                  //* X - subtract  ||  
    void subtractFromY(Dmath::Scalar subtract);                  //* Y - subtract  ||
    
    void multiplyXBy(Dmath::Scalar factor);                      //* X * factor    ||
    void multiplyYBy(Dmath::Scalar factor);                      //* Y * factor    ||
     
    void divideXBy(Dmath::Scalar divBy);                         //* X / divBy     ||
    void divideYBy(Dmath::Scalar divBy);                         //* Y / divBy     ||



    void linearTransformation(Dmath::Matrix<Dmath::Scalar> matrix);

    void moveVectorX(Dmath::Scalar move);                               // Moves the vector in a specific x-direction
    void moveVectorY(Dmath::Scalar move);                               // Moves the vector in a specific y-direction
    void moveVector(Dmath::Scalar moveX, Dmath::Scalar moveY);          // Moves the vector in a specific x and y direction 
    void rotateThisVector(Dmath::Scalar value);

 

    // spezial Vectors
    static Vec2D polarVector(Dmath::Scalar radius, Dmath::Scalar angle); // Creates a Vector in a polar system
    static Vec2D zeroVector();                             // Creates a vector with lenght 0
};


std::ostream& operator<<(std::ostream& os, Vec2D num);


#pragma endregion


//######################################################################################################

#ifdef SYSTEMGEOMETRY_HPP //aus systemGeometry.hpp

//Most of the methods in the Vec3D class ar simular to the methods in the Vec2D class
#pragma region Vec3D 

class SystemGeometry;


class Vec3D : public CoordinateSystem3D {
  private: //Private members

    double abs;

  private: //Private Methods
    void calcAbs();
    

  public: // Numeric operator overloading and numeric operarions

    void addToX(double add); // X + add
    void addToY(double add); // Y + add
    void addToZ(double add); // Z + add

    void addXYZEach (double xPlus, double yPlus,   double zPlus);        //* X + xPlus     || Y + yPlus
    void divideXYZBy(double xDivBy, double yDivBy, double zPlus);        //* X / xDivBy    || Y / yDivBy
    void multilpyXYZ(double xTimes, double yTimes, double zPlus);        //* X * xTimes    || Y * yTimes
    void subtractXYZ(double xMinus, double yMinus, double zPlus);        //* X - xMinus    || Y - yMinus
    

    Vec3D operator+(Vec3D& Mathvector);          //Vector addition
    Vec3D operator-(Vec3D& Mathvector);          //Vectors subraction
    Vec3D operator/(double scalarValue);         //Divides the coordinates by a given value
    double operator*(Vec3D& Mathvector);         //Scalarproduct

    void operator+=(Vec3D mathvector);
    void operator-=(Vec3D mathvector);
    void operator*=(Vec3D mathvector);
    void operator/=(Vec3D mathvector);

    void operator+=(Dmath::sVec3f vec);
    void operator-=(Dmath::sVec3f vec);
    void operator*=(Dmath::sVec3f vec);
    void operator/=(Dmath::sVec3f vec);

    void operator+=(double scalar);
    void operator-=(double scalar);
    void operator*=(double scalar);
    void operator/=(double scalar);

    void operator+=(Dmath::Trio<double,double,double> trio);
    void operator-=(Dmath::Trio<double,double,double> trio);
    void operator*=(Dmath::Trio<double,double,double> trio);
    void operator/=(Dmath::Trio<double,double,double> trio);


  public: //Public logic operators

    void operator=(Dmath::sVec3f vec);
    void operator=(Dmath::Trio<double,double,double> trio);
    void operator=(Dmath::Vec3D vec);

    inline bool operator==(Vec3D& Mathvector);   // == checks if the x and y coordinates are the same
    inline bool operator!=(Vec3D& Mathvector);   // != checks if the x and y coordinates are diffrent
    inline bool operator>=(Vec3D& Mathvector);   // >= checks if the lenght of the vector is greater or equal
    inline bool operator<=(Vec3D& Mathvector);   // <= checks lenght ...
    inline bool operator<(Vec3D& Mathvector);    // lenght1 < lenght2 ... 
    inline bool operator>(Vec3D& Mathvector);    // lenght1 > lenght2 ...

    void operator++();
    void operator--();

  Dmath::SystemGeometry *systemGeometry;

  public: // Public Constructors

   Vec3D() = default; //default constructor

#ifdef CARTESIAN_IS_3D_STANDARD
    Vec3D(double XYZ);
    Vec3D(double X, double Y, double Z);
    Vec3D(double X, double Y, double Z, double originX, double originY, double originZ );
#endif

#ifdef SPHERE_IS_STANDARD
    Vec3D(double radius, double phi, double theta);
#endif

#ifdef CYLINDER_IS_STANDARD
    Vec3D(double radius, double phi, double height);
#endif


  public: //Getters and Setters
    void setX(double X);            //Basic public setters
    void setY(double Y);
    void setZ(double Z);

    //Set all values in the coordinate systems based on a given scalar
   
    void setAllCatesian(Dmath::Scalar value);     //For example to set all values to 0
    void setAllSphere  (Dmath::Scalar value);     //Sets angle 1,2 and the radius to a specific value
    void setAllCylinder(Dmath::Scalar value);     //Sets the angle, height and radius to a specific angle

    void setPhi(double phi);                      // For spheresystems (radius, angle Phi, angle Theta)
    void setHeight(double phi);                   // For cylinder systems (radius, angle, height);
    void setTheta(double phi);                    // For spheresystems (radius, angle Phi, angle Theta);

    void normalize();                             // Divides the vectors components though its length 

    double getSphereRadius();                     //Getters for other systems
    double getCylinderRadius();

    inline double getAZ() { return this->aZ;  }   //Getter for aX and aY
    inline double getAbs(){ return this->abs; }

    //The moveVector() method will move the vectors in the x,y and Z directions
    void moveVector(double moveX, double moveY, double moveZ);
    void moveVectorX(double moveX);                               // Moves the vector in a specific x-direction
    void moveVectorY(double moveY);                               // Moves the vector in a specific y-direction
    void moveVectorZ(double moveZ);                               // Moves the vector in a specific y-direction


    void rotateThisVector(double phi, double Theta);

    // The rotateVector method will return a new Vector based on the original and the given rotation
    Vec3D rotateVector(double radiansPhi, double radiansTheta);  //Gives back a rotated vector based of this vectors coordinats


    // Calculations that return a scalar value
    double dotProduct(Vec3D Mathvector);                         //Simpel dot or scalarproduct between two vectors
    double calcAngle(Vec3D Mathvector);                          //calculates the angle between vectors


    // Calculations that return a vector
    Vec3D vecProduct(Vec3D Mathvector);                          //The vector product of two vectors
    Vec3D add(Vec3D Mathvector);                                 //Vector addition
    Vec3D subtract(Vec3D Mathvector);                            //Vector subtraction

    bool isEqual(Dmath::Vec3D);

    
  public: //public static methods

    static Vec3D zeroVector();                                   // Returns a Vector with lenght 0

    static Vec3D sphereVector(double radius, double angleOne, double angleTwo); //gives a vector in a sphere  system
    static Vec3D cylinderVector(double radius, double angle, double height);    //gives a vector in a cylinder system

};


std::ostream& operator<<(std::ostream& os, Vec3D num);
#endif

#pragma endregion
#endif // SYSTEM_IS_SET
NAMESPACEEND
#endif // VECTORMATH_H

#pragma endregion