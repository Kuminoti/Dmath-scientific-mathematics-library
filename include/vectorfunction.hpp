#pragma once

#ifndef DMATH_VECTORFUNCTION_HPP
#define DMATH_VECTORFUNCTION_HPP

#include"mathFunction.hpp"

NAMESPACESTART

/*File: vectorFunction.hpp
 * 
 *Description:
 * This file contains classes for describing vectorially represented functions, e.g.:
 * for representing parameterizations of curves or surfaces
 * => k(t) = [ x(t); y(t); z(t) ]
 * 
 * The class SingleVectorFunction supports  two dimensional aswell as 3d function
 * The representation of the indivitual functional komponents works with the  help of the Datatypes: 
 *      - Dmath::SingleVarFunction  
 *      - Dmath::DoubleVarFunction
 *        File: mathFunction.hpp 
 * 
* These are self-written function objects similar to the std::function object from the
* C++ STL, with the difference that they are optimized for describing mathematical
* functions and therefore have additional functionality.
*/

#pragma region Single

class SHARED_LIB SingleVectorFunction{

private: //Private Members

    Dmath::SingleVarFunction xOfT;
    Dmath::SingleVarFunction yOfT;
    Dmath::SingleVarFunction zOfT; 

public: //Public constructors

    //default constructor
    SingleVectorFunction() = default;

    //constructor for a 2D vectorFunction
    SingleVectorFunction(const Dmath::SingleVarFunction& xOfT,const Dmath::SingleVarFunction& yOfT);

    //constructor for a 3D vectorFunction
    SingleVectorFunction(const Dmath::SingleVarFunction& xOfT,const Dmath::SingleVarFunction& yOfT, const Dmath::SingleVarFunction& zOfT);
   
    Dmath::Vec2D call2D(Dmath::Scalar t);
    
    Dmath::Vec3D operator ()(Dmath::Scalar t);

    SingleVectorFunction operator+(SingleVectorFunction funcTwo);
    SingleVectorFunction operator-(SingleVectorFunction funcTwo);

    //Operator for scalar multiplikation
    Dmath::SingleVarFunction operator*(SingleVectorFunction funcTwo);

    //operator for crossproducts
    SingleVectorFunction crossProduct(SingleVectorFunction funcTwo);
    //Getters:

    Dmath::SingleVarFunction getXFunc(){ return this->xOfT;    }
    Dmath::SingleVarFunction getYFunc(){ return this->yOfT;    }
    Dmath::SingleVarFunction getZFunc(){ return this->zOfT;    }


    //Call the functions
    inline Dmath::Scalar callX(Dmath::Scalar t){ return xOfT(t); }
    inline Dmath::Scalar callY(Dmath::Scalar t){ return yOfT(t); }
    inline Dmath::Scalar callZ(Dmath::Scalar t){ return zOfT(t); }

    
    Dmath::Vec3D getTangentialVectorAt(Dmath::Scalar t);
};

#pragma endregion //single 

#pragma region Double
class SHARED_LIB DoubleVectorFunction{
private:
    Dmath::DoubleVarFunction xOfUV;
    Dmath::DoubleVarFunction yOfUV;
    Dmath::DoubleVarFunction zOfUV;

public:

    DoubleVectorFunction() = default;

    

    DoubleVectorFunction(Dmath::DoubleVarFunction xOfUV, Dmath::DoubleVarFunction yOfUV, Dmath::DoubleVarFunction zOfUV);

    Dmath::Vec3D operator ()(Dmath::Scalar U, Dmath::Scalar V);
    Dmath::Vec3D operator ()(Dmath::Vec2D vec);

    inline Dmath::Scalar callX(Dmath::Scalar u, Dmath::Scalar v){ return xOfUV(u,v); }
    inline Dmath::Scalar callY(Dmath::Scalar u, Dmath::Scalar v){ return yOfUV(u,v); }
    inline Dmath::Scalar callZ(Dmath::Scalar u, Dmath::Scalar v){ return zOfUV(u,v); }

    Dmath::DoubleVarFunction operator*(DoubleVectorFunction func);


    Dmath::DoubleVectorFunction operator+(DoubleVectorFunction funcTwo);

    Dmath::DoubleVectorFunction crossPruduct(DoubleVectorFunction funcTwo);

    Dmath::DoubleVarFunction getXFunc(){ return this->xOfUV;  }
    Dmath::DoubleVarFunction getYFunc(){ return this->yOfUV;  }
    Dmath::DoubleVarFunction getZFunc(){ return this->zOfUV;  }

   
    //Returns the numeric partial derivative at a specific point as a vector-object

    Dmath::Vec3D getPartialUAt(Dmath::Scalar u, Dmath::Scalar v);
    Dmath::Vec3D getPartialVAt(Dmath::Scalar u, Dmath::Scalar v);

    Dmath::Vec3D normVectorAt (Dmath::Scalar u, Dmath::Scalar v);

    /*returns the numeric partial derivatives with respect to U or V as a vectorfunction object
     *  
     *       F:=  [x(u,v),
     *             y(u,v),
     *             z(u,v)]
     *
     * => dF/du = [dx(u,v)/du,
     *             dy(u,v)/du,
     *             dz(u,v)/du]
     * 
     *    dF/dv = [dx(u,v)/dv,
     *             dy(u,v)/dv
     *             dz(u,v)/dv]
     */
    Dmath::DoubleVectorFunction partialU();
    Dmath::DoubleVectorFunction partialV();
    
};


#pragma endregion



#pragma region Triple

class SHARED_LIB TripleVectorFunction{
  private:
    Dmath::TripleVarFunction xOfUVW;
    Dmath::TripleVarFunction yOfUVW;
    Dmath::TripleVarFunction zOfUVW;

  public:

    TripleVectorFunction(Dmath::TripleVarFunction xOfUVW, Dmath::TripleVarFunction yOfUVW, Dmath::TripleVarFunction zOfUVW);
    Dmath::Vec3D operator()(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

    //Tangential vektoren
    Dmath::Vec3D getPartialUAt(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Vec3D getPartialVAt(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Vec3D getPartialWAt(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

    Dmath::Scalar callX(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callY(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callZ(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

    //Patielle ableitungen aller funktionen
    Dmath::Scalar callXPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callYPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);
    Dmath::Scalar callZPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w);

};

NAMESPACEEND
#endif