#pragma once

#ifndef DMATH_POINT_HPP
#define DMATH_POINT_HPP

#include"mathVector.hpp"


/* A Dmath::Point basicly holds vector data in string format
 * and the class is responseble for converting vectors into strings and back
 * This class is used to make converting vector-data simpler for example file handling 
 * This class does not support mathmatical operations
*/


NAMESPACESTART


typedef Dmath::sVec3<std::string> Point;


Point vecToPoint(Dmath::Vec3D vec){
    std::string X_ = std::to_string(vec.getX());
    std::string Y_ = std::to_string(vec.getY());
    std::string Z_ = std::to_string(vec.getZ());

    return Dmath::Point(X_,Y_,Z_);
}

Dmath::Vec3D pointToVec(Dmath::Point p){
    Dmath::Scalar _X = std::stod(p.X);
    Dmath::Scalar _Y = std::stod(p.Y);
    Dmath::Scalar _Z = std::stod(p.Z);

    return Dmath::Vec3D(_X,_Y,_Z);
}



NAMESPACEEND


#endif //DMATH_POINT_HPP