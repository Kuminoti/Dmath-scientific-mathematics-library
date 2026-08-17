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

    VectorLine(Dmath::Vec3D dirVec){
        setOriginVec(dirVec);
        setDirVec(dirVec);
    }
    VectorLine(Dmath::Vec3D originVec, Dmath::Vec3D dirVec){
        
        this->originVec = originVec;
        this->directionVec = dirVec;
    }

  public: //public operators

    Dmath::Vec3D operator()(Dmath::Scalar t) const {
        
        Dmath::Scalar x = this->originVec.getX() + t * this->directionVec.getX();
        Dmath::Scalar y = this->originVec.getY() + t * this->directionVec.getY();
        Dmath::Scalar z = this->originVec.getZ() + t * this->directionVec.getZ();
        
        Dmath::Vec3D line(x,y,z,
            this->originVec.getX(),
            this->originVec.getY(),
            this->originVec.getZ());

        return line;
    }

  public: //getters
    Dmath::Vec3D getOriginVec(){ return this->originVec; }
    Dmath::Vec3D getDirectionVec(){ return this->directionVec; }


    Dmath::Vec3D intersection(const VectorLine& other){
    const auto& p1 = originVec;
    const auto& d1 = directionVec;

    const auto& p2 = other.originVec;
    const auto& d2 = other.directionVec;

    constexpr Dmath::Scalar eps = 1e-9;

    auto det = [](Dmath::Scalar a,
                  Dmath::Scalar b,
                  Dmath::Scalar c,
                  Dmath::Scalar d)
    {
        return a*d - b*c;
    };

    // Determinante des x/y-Systems
    Dmath::Scalar D =
        det(d1.getX(), -d2.getX(),
            d1.getY(), -d2.getY());

    // Falls x/y ungeeignet, benutze x/z
    if(std::abs(D) < eps)
    {
        D =
        det(d1.getX(), -d2.getX(),
            d1.getZ(), -d2.getZ());
    }

    // Falls immer noch 0 -> Richtungen parallel
    if(std::abs(D) < eps)
    {
        // Verbindungsvektor
        Dmath::Vec3D v(
            p2.getX()-p1.getX(),
            p2.getY()-p1.getY(),
            p2.getZ()-p1.getZ());

        // Kreuzprodukt prüfen
        Dmath::Vec3D c = v.vecProduct(d1);

        if(std::abs(c.getX()) < eps &&
           std::abs(c.getY()) < eps &&
           std::abs(c.getZ()) < eps)
        {
            // identisch
            return Dmath::Vec3D(Dmath::INF,
                                Dmath::INF,
                                Dmath::INF);
        }

        // parallel
        return Dmath::Vec3D(Dmath::NaN,
                            Dmath::NaN,
                            Dmath::NaN);
    }

    // Löse mit x/y
    Dmath::Scalar rhs1 = p2.getX() - p1.getX();
    Dmath::Scalar rhs2 = p2.getY() - p1.getY();

    Dmath::Scalar t =
        det(rhs1, -d2.getX(),
            rhs2, -d2.getY()) / D;

    Dmath::Scalar s =
        det(d1.getX(), rhs1,
            d1.getY(), rhs2) / D;

    Dmath::Vec3D P1 = (*this)(t);
    Dmath::Vec3D P2 = other(s);

    if(std::abs(P1.getX()-P2.getX()) > eps ||
       std::abs(P1.getY()-P2.getY()) > eps ||
       std::abs(P1.getZ()-P2.getZ()) > eps)
    {
        // windschief
        return Dmath::Vec3D(Dmath::NaN,
                            Dmath::NaN,
                            Dmath::NaN);
    }

    return P1;
}


  public: //Dmath::Getters

    Dmath::SingleVectorFunction getParametric(){
        /* Convert the sinmple equation of a line:
         * g : x-> = oV-> + t* vd->
         * to a purely parametric form
         * v->(t) = [x(t)= ..., y(t)=..., z(t)= ...]
        */

        Dmath::SingleVarFunction xoft = [this](Dmath::Scalar t) ->Dmath::Scalar {
            return (t*directionVec.getX() + originVec.getX());
        };
        Dmath::SingleVarFunction yoft = [this](Dmath::Scalar t) ->Dmath::Scalar {
            return (t*directionVec.getY() + originVec.getY());
        };
        Dmath::SingleVarFunction zoft = [this](Dmath::Scalar t) ->Dmath::Scalar {
            return (t*directionVec.getZ() + originVec.getZ());
        };

        return Dmath::SingleVectorFunction(xoft,yoft,zoft);

    }

    Dmath::Matrix<Dmath::Scalar> getSystemOfEquations(VectorLine& other){
        /* Creates a system of linear eqations in form of a matrix:
         * 1 + 2t = 3 + 4s 
         *=> [1 2 3 4]
        */
        Dmath::Matrix<Dmath::Scalar> mainMatrix(4);
        mainMatrix.setAll(0);

        mainMatrix.setElement(1,1,originVec.getX());
        mainMatrix.setElement(1,2,directionVec.getX());

        mainMatrix.setElement(1,3,other.getOriginVec().getX());
        mainMatrix.setElement(1,4,other.getDirectionVec().getX());



        mainMatrix.setElement(2,1,originVec.getY());
        mainMatrix.setElement(2,2,directionVec.getY());

        mainMatrix.setElement(2,3,other.getOriginVec().getY());
        mainMatrix.setElement(2,4,other.getDirectionVec().getY());


        mainMatrix.setElement(3,1,originVec.getZ());
        mainMatrix.setElement(3,2,directionVec.getZ());

        mainMatrix.setElement(3,3,other.getOriginVec().getZ());
        mainMatrix.setElement(3,4,other.getDirectionVec().getZ());

        return mainMatrix;
    }

  private: //Private helper functions

    void setOriginVec(Dmath::Vec3D Vec){
        this->originVec.setX(Vec.getOriginX());
        this->originVec.setY(Vec.getOriginY());
        this->originVec.setZ(Vec.getOriginZ());
    }
    void setDirVec(Dmath::Vec3D Vec){
        this->directionVec.setX(Vec.getX());
        this->directionVec.setY(Vec.getY());
        this->directionVec.setZ(Vec.getZ());
    }



};





NAMESPACEEND

#endif //DMATH_VECTOR_LINE_HPP