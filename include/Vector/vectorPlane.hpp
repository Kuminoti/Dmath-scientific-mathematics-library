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

    Dmath::Vec3D operator()(Dmath::Scalar U, Dmath::Scalar V) const {
        
        auto f = this->getParametric();

        return f(U,V);
    }


    Dmath::DoubleVectorFunction getParametric() const {

        Dmath::DoubleVarFunction xOfUV = [this](Dmath::Scalar U, Dmath::Scalar V) ->Dmath::Scalar {
            return originVec.getX() + U * directionVec.getX() + V * dirVecTwo.getX();
        };
        Dmath::DoubleVarFunction yOfUV = [this](Dmath::Scalar U, Dmath::Scalar V) ->Dmath::Scalar {
            return originVec.getY() + U * directionVec.getY() + V * dirVecTwo.getY();
        };
        Dmath::DoubleVarFunction zOfUV = [this](Dmath::Scalar U, Dmath::Scalar V) ->Dmath::Scalar {
            return originVec.getZ() + U * directionVec.getZ() + V * dirVecTwo.getZ();
        };


        return Dmath::DoubleVectorFunction(xOfUV,yOfUV,zOfUV);


    }

};

NAMESPACEEND

#endif //DMATH_VECTOR_PLANE_HPP