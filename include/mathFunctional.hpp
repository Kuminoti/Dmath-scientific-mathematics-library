#pragma once 

/* File: mathFunctional.hpp
 *
 * Project Start: 23. October 2025
 * 
 * Purpose: 
 * This file creates Classes to mimic the behavior of so called
 * functionals (NOT Functions).
 * 
 * Definition:
 * A functional is a mapping that assigns a value from a scalar to a 
 * function from a vector space.
 * 
 * example:
 *  ____________________________
 * |  Object  | Input  | Output |
 * |____________________________|
 * | function | Scalar | Scalar | -> f(x) = x² -> f(1) = 1*1 = 1
 * |____________________________|
 * |functional|function| Scalar | 
 * 
 * A functional is sometimes called 'function of functions'
 * and is an important mathmatical object in modern parts
 * of mathmatics like: Functional-Calculus/Analysis, Calculus of variations
 * 
*/ 


//example usage 
// Dmath::SingleVarFunction func = [](double x){
//     return x;
//   };
//   Dmath::SingleVectorFunction vFunc(func, func, func);

//  Dmath::Parameters stdparam(0,1,0.000001);


//   Dmath::Functional mainFunctional(Dmath::IntegralOperator, stdparam);

//   std::cout << mainFunctional(func) << std::endl;



#ifndef DMATH_MATH_FUNCTIONAL_HPP
#define DMATH_MATH_FUNCTIONAL_HPP


#include"dFunctions.hpp"   // To get Some helperfunctions
#include"Types/traits.hpp" //To get Specific typetraids for the code

#include"vectorfunction.hpp"
#include"Oprator.hpp"

NAMESPACESTART //Namespace Dmath

enum Function_type{
    SINGLE,
    DOUBLE_,
    TRIPLE,
    COMPLEX,
    VEC_SINGLE,
    VEC_DOUBLE,
    VEC_TRIPLE, 
    UNKNOWEN
};




template<typename OP>
class Functional{

private: //Private members
    

    OP functionalOperator;
    Dmath::Parameters params;
    //functionType is an Enum wich takes on a specific value dependend of the given funktion
    Function_type functionType = UNKNOWEN;

public: 

    Functional(OP operators, Dmath::Parameters params){
        this->functionalOperator = operators;
        this->params = params;
        using funcTraid = Dmath::function_traits<OP>;

        if(std::is_same<typename funcTraid::Arg2, Dmath::SingleVarFunction>::value){
            this->functionType = SINGLE;
        }
        else if(std::is_same<typename funcTraid::Arg2, Dmath::DoubleVarFunction>::value){
            this->functionType = DOUBLE_;
        }
        else if(std::is_same<typename funcTraid::Arg2, Dmath::TripleVarFunction>::value){
            this->functionType = TRIPLE;
        }
        else if(std::is_same<typename funcTraid::Arg2, Dmath::SingleVectorFunction>::value){
            this->functionType = VEC_SINGLE;
        }
        else if(std::is_same<typename funcTraid::Arg2, Dmath::DoubleVectorFunction>::value){
            this->functionType = VEC_DOUBLE;
        }
        else if(std::is_same<typename funcTraid::Arg2, Dmath::TripleVectorFunction>::value){
            this->functionType = VEC_TRIPLE;
        }
        else{ this->functionType = UNKNOWEN; }

    }

 template<typename Func,
    typename = std::enable_if_t<
        std::is_same_v<Func, Dmath::SingleVarFunction> ||
        std::is_same_v<Func, Dmath::DoubleVarFunction> ||
        std::is_same_v<Func, Dmath::TripleVarFunction> 
        
        >>
    Dmath::Scalar operator()(Func func){

        /* For example the operator is an arclenght-integral and the
         * function is a continuous and differentiable.
         * the parameters contains the integration limits and
         * the "size" of the diffrential dx (step size)
        */ 
        return this->functionalOperator(this->params, func);
    }

    template<typename Func,
    typename = std::enable_if_t<std::is_same_v<Func, Dmath::SingleVectorFunction>
        >>
    Dmath::Vec3D operator()(Func func){

        /* For example the operator is an arclenght-integral and the
         * function is a continuous and differentiable.
         * the parameters contains the integration limits and
         * the "size" of the diffrential dx (step size)
        */ 
        return this->functionalOperator(this->params, func);
    }



    void setFunctionalOperator(OP funcOP){
        using funcTraid = Dmath::function_traits<OP>;
        if(!std::is_same<typename funcTraid::Arg1 , Dmath::Parameters>::value ||
           !std::is_same<typename  funcTraid::Arg2 , Dmath::SingleVarFunction>::value){
            std::cerr << "ERROR HEEEEEEEEEELP" << std::endl;
        }

        this->functionalOperator = funcOP;
    }

    void setParams(Dmath::Parameters param){
        this->params = param;
    }

};

 
NAMESPACEEND // }

#endif // DMATH_MATH_FUNCTIONAL_HPP