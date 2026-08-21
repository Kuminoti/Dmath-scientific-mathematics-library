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


Point vecToPoint(Dmath::Vec3D vec);

Dmath::Vec3D pointToVec(Dmath::Point p);



NAMESPACEEND


#endif //DMATH_POINT_HPP