#pragma once

#ifndef DMATH_VECTOR_PLANE_HPP
#define DMATH_VECTOR_PLANE_HPP

#include"vectorLine.hpp"

NAMESPACESTART

class VectorPlane : public Dmath::VectorLine {

  private:
    Dmath::Vec3D dirVecTwo;

  public:

    VectorPlane(Dmath::Vec3D originVec, Dmath::Vec3D directionVec, Dmath::Vec3D dirVecTwo) : VectorLine(originVec,directionVec) {
        this->dirVecTwo = dirVecTwo;
    }

    Dmath::Vec3D operator()(Dmath::Scalar U, Dmath::Scalar V) const ;


    Dmath::DoubleVectorFunction getParametric() const ;

};

NAMESPACEEND

#endif //DMATH_VECTOR_PLANE_HPP