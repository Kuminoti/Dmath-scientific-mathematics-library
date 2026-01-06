#pragma once

#ifndef SYSTEMS_H
#define SYSTEMS_H

#include"macros.hpp"   //Contains macros and constants for this project
#include"dataTypes.hpp" //Contains library specific datatypes

/* 
 * This file is used to create a base and an abstraction for the other classes and systems.
 * The CoordinateSystem2D and CoordinateSystem3D classes will be inherited to the Vec2D and Vec3D

 * 
 * In this file you can choose the standard Coordinate system for you calculations and it contains important
 * mathmatical constants and data.
*/




#ifdef SYSTEM_READY

#pragma region MathHelper
// A helper class with some pre defined functions


#pragma endregion


#pragma region 2D-Coordinates
// Coordinatesystem2D is used as an abstraction for other classes like the 2 main Vector classes
class CoordinateSystem2D { 

  protected: // Protected members

    void* NULLVECX = 0; //NULL vector x
    void* NULLVECY = 0; //NULL vector y

    double X = 0;
    double Y = 0;
    double t = 0;     //A parameter t can be used to represent time or can be used for parametriccurves



    //For vectors wich doesnt start at zero
    double originX = 0;       //the "x-Start" of the vector, if the vector it self doesent start at zero  
    double originY = 0;       //the "x-Start" of the vector, if the vector it self doesent start at zero

    double aX;                //The absoulute xvalue, or the distence between 0 and the X value
    double aY;                //The absoulute yvalue, or the distence between 0 and the Y value

    double distanceToZero; 

    double radius = 0;        //Randius and angle for polar-coordinates 
    double phi = 0;           //Angle phi



  

    void polarToCartesian();
    void cartesianToPolar();

    void calcAbsXY();
    void calcDZ();                                          // Calculates the distance to zero

  public:
#ifdef CARTESIAN_IS_2D_STANDARD

    //sVec is a struct with only an x, and y (and z) member defined in include/datatypes.hpp
    CoordinateSystem2D(Dmath::sVec2f vec);
    CoordinateSystem2D(Dmath::sVec2i vec);

    CoordinateSystem2D() = default;
    CoordinateSystem2D(double XY);
    CoordinateSystem2D(double x, double y);
    CoordinateSystem2D(double x, double y, double t); //Need Implementation
    CoordinateSystem2D(double x, double y, double originX, double originY);
#endif

#ifdef POLAR_IS_STANDARD
    CoordinateSystem2D(double radius, double phi);
    CoordinateSystem2D(double radius, double phi, double originX, double originY);
#endif

  virtual ~CoordinateSystem2D() = default;



  public:

  void operator++();
   
    inline double getT()       const { return this->t;       }
    inline double getX()       const { return this->X;       }
    inline double getY()       const { return this->Y;       }
    inline double getAX()      const { return this->aX;      }
    inline double getAY()      const { return this->aY;      }   
    inline double getPhi()     const { return this->phi;     }
    inline double getRadius()  const { return this->radius;  }    
    inline double getOriginX() const { return this->originX; }
    inline double getOriginY() const { return this->originY; }

    inline void setT(double t) { this->t = t; }

    void setOriginX(double newOriginX);
    void setOriginY(double newOriginY);

    inline double getDistanceZero(){ return this->distanceToZero; } 

    


}; // CoordinateSystem2D

#pragma endregion


#pragma region 3D-Coordinates
class CoordinateSystem3D : public CoordinateSystem2D {
  protected: // protected data
    //For zero or nullvectors
    void* NULLVECX = 0;
    void* NULLVECY = 0;
    void* NULLVECZ = 0;

    double Z;
    double aZ;
    double theta;
    double height;
    double originZ;

  protected: // Protected methods;
    void cartesianToSphere();
    void cartesianToCylinder();

    void sphereToCatesian();
    void sphereToCylinder();

    void cylinderToCartesian();
    void cylinderToSphere();
    void calcDTZ();   //Calculates the  from an origin point to zero
    void calcAXYZ();  //Calculates the Absolude magnitude from zero to the end of a vector even for non zero vectors
    
  public: //Public constructors

#ifdef CARTESIAN_IS_3D_STANDARD

    CoordinateSystem3D(Dmath::sVec3f vec);
    CoordinateSystem3D(Dmath::sVec3i vec);

    CoordinateSystem3D(double XYZ);
    CoordinateSystem3D(double X, double Y, double Z);
    CoordinateSystem3D(double X, double Y, double Z, double originX, double originY, double originZ);
#endif

#ifdef SPHERE_IS_STANDARD
    CoordinateSystem3D(double radius, double phi, double theta);
    CoordinateSystem3D(double radius, double phi, double theta, double originX, double originY, double originZ);
#endif

#ifdef CYLINDER_IS_STANDARD
    CoordinateSystem3D(double radius, double phi, double height);
    CoordinateSystem3D(double radius, double phi, double hieght, double originX, double originY, double originZ);
#endif


    virtual ~CoordinateSystem3D() = default;



  public: // Public Methods

    //Basic inline getters
    inline double getTheta()   { return this->theta;   }
    inline double getHeight()  { return this->height;  }
    inline double getZ()       { return this->Z;       } 
    inline double getOriginZ() { return this->originZ; }

    void setOriginX(double Value);

    void setOriginY(double Value);

    void setOriginZ(double Value);

    double getRadiusSphere();
    double getRadiusCylinder();
    //Zerovector / NULL vector constructor

    CoordinateSystem3D() : CoordinateSystem2D(){
      this->NULLVECX = CNULL;
      this->NULLVECY = CNULL;
      this->NULLVECZ = CNULL;
    }


}; // CoordinateSystem3D


#endif // SYSTEM_IS_SET
#endif // SYSTEMS_H includeguard
