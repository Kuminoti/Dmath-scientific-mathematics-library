#pragma once 

#ifndef DMATH_FUNCTION_OPERATORS_HPP
#define DMATH_FUNCTION_OPERATORS_HPP

#include"../Text/chars.hpp"
#include"vectorfunction.hpp"


NAMESPACESTART

#pragma region SingleVarOperators

Dmath::SingleVarFunction operator*(std::string op, Dmath::SingleVarFunction& func){
	Dmath::SingleVarFunction f([](Dmath::Scalar x){ return Dmath::NaN;}, "NaN");

    //Analytical operators

	if(op == Dmath::SpecialChars.getFromKey("nabla")      ||
       op == Dmath::SpecialCHars.getFromKey("derivative") ||
       op == Dmath::SpecialChars.getFromKey("partial")    ){

        //partial und nabla operators are simple derivatives in 1D
		f = func.getDerivative();
		f.setFuncData(
		"d/dx(" + func.getFunctionData() +
		")");
	}

	if(op == Dmath::SpecialChars.getFromKey("integral")){
		f = func.getAntiDerivative();

		f.setFuncData(
            Dmath::SpecialChars.getFromKey("integral") +
		    "(" + func.getFunctionData() + ")"
	    );

	}



    //numeric operators
    if(op == Dmath::SpecialChars.getFromKey("sqrt")){
        Dmath::SingleVarFunction g(
            [func](Dmath::Scalar) ->Dmath::Scalar {
                return std::sqrt(func(x));
            }
            ,Dmath::SpecialChars.getFromKey("sqrt") + "(" + func.getFunctionData() + ")" );

            f = g;
    }


    if(op == Dmath::SpecialChars.getFromKey("cbrt")){
        Dmath::SingleVarFunction g(
            [func](Dmath::Scalar) ->Dmath::Scalar {
                return std::cbrt(func(x));
            }
            ,Dmath::SpecialChars.getFromKey("cbrt") + "(" + func.getFunctionData() + ")" );

            f = g;
    }

    if(op == Dmath::SpecialChars.getFromKey("fourthRoot")){
        Dmath::SingleVarFunction g(
            [func](Dmath::Scalar) ->Dmath::Scalar {
                return std::pow(func(x), 1.0f/4.0f);
            }
            ,Dmath::SpecialChars.getFromKey("fourthRoot") + "(" + func.getFunctionData() + ")" );

            f = g;
    }
	
	return f;
}





#pragma endregion

NAMESPACEEND

#endif //DMATH_FUNCTION_OPERATORS_HPP