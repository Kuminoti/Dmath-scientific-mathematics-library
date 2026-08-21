#pragma once

#ifndef DMATH_VECTOR_LINE_HPP
#define DMATH_VECTOR_LINE_HPP

#include"../Functional/vectorfunction.hpp"

NAMESPACESTART

class VectorLine{
  protected: //Private members 

    Dmath::Vec3D originVec;
    Dmath::Vec3D directionVec;

  public: //Public constructors
    VectorLine() = default;

    VectorLine(Dmath::Vec3D dirVec);

    VectorLine(Dmath::Vec3D originVec, Dmath::Vec3D dirVec);

  public: //public operators

    Dmath::Vec3D operator()(Dmath::Scalar t) const ;

  public: //getters
    Dmath::Vec3D getOriginVec(){ return this->originVec; }
    Dmath::Vec3D getDirectionVec(){ return this->directionVec; }


    Dmath::Vec3D intersection(const VectorLine& other);


  public: //Dmath::Getters

    Dmath::SingleVectorFunction getParametric();
        /* Convert the sinmple equation of a line:
         * g : x-> = oV-> + t* vd->
         * to a purely parametric form
         * v->(t) = [x(t)= ..., y(t)=..., z(t)= ...]
        */

        

    Dmath::Matrix<Dmath::Scalar> getSystemOfEquations(VectorLine& other);
        /* Creates a system of linear eqations in form of a matrix:
         * 1 + 2t = 3 + 4s 
         *=> [1 2 3 4]
        */
    

  private: //Private helper functions

    void setOriginVec(Dmath::Vec3D Vec);
    void setDirVec(Dmath::Vec3D Vec);



};





NAMESPACEEND

#endif //DMATH_VECTOR_LINE_HPP