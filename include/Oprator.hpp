#pragma once


/* File experimental/Operator.hpp
 * 
 * Project Start:
 * 24. October 2025
 * 
 * Purpose: 
 * This file contains functions and classes for 
 * pre written Functional operators (mathFunctional.hpp)
 * Like Arclenth functionals
 * Sum operators 
 * diffrential and integral operators
 * 
 * Example the Arclenght integral
 * ∫ ds ->[a,b] = ∫ sqrt(1 + (f'(x)^2)
 * 
*/

#ifndef DMATH_OPERATOR_HPP
#define DMATH_OPERATOR_HPP

    #include"vectorfunction.hpp"
    #include"dFunctions.hpp"

    NAMESPACESTART //Namespace Dmath
      


    #pragma region IntegralOperators

    /* This function calculates the arclenght of a funtion using the Arclenght integral
     * ∫ ds ->[a,b] = ∫ sqrt(1 + (f'(x)^2)
     * Or in the case of a curve in parameter form:
     * k(t) = { x(t); y(t); z(t) }
     * ∫ ds ->[a,b] = ∫ sqrt((x'(t))² + (y'(t))² + (z'(t))² )
     */
    template<typename Func>
    Dmath::Scalar arcLenght(Dmath::Parameters param, Func func){
        if (!Dmath::checkParams(param)){
            std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
            return 0;
        }
  
        const Dmath::Natural a = static_cast<size_t>(param.one);
        const Dmath::Natural b = static_cast<size_t>(param.two);
        const Dmath::Scalar dx = param.three;

        Dmath::Scalar sum = 0;

        Dmath::Natural num = Dmath::numberOfElements(param);

        

        for(size_t i = 0; i < num; i++){
            Dmath::Scalar currentX = a + i * dx;
            if constexpr (std::is_same<Func, Dmath::SingleVectorFunction>::value){
                Dmath::SingleVarFunction xOfT = func.getXFunc();
                Dmath::SingleVarFunction yOfT = func.getYFunc();
                Dmath::SingleVarFunction zOfT = func.getZFunc();
                Dmath::Scalar currentResult = std::sqrt(
                    (xOfT.getDerivativeAt(currentX) * xOfT.getDerivativeAt(currentX)) + 
                    (yOfT.getDerivativeAt(currentX) * yOfT.getDerivativeAt(currentX)) +
                    (zOfT.getDerivativeAt(currentX) * zOfT.getDerivativeAt(currentX))
                    ) * dx;

                sum += currentResult;
                continue;
            }
            else if constexpr(std::is_same<Func, Dmath::SingleVarFunction>::value){
                Dmath::Scalar currentResult = std::sqrt(1 + (func.getDerivativeAt(currentX) * func.getDerivativeAt(currentX))) * dx;
                sum += currentResult;
            }
        }
        return sum;
    }

    /*
     * The integral between to points on a functiongraph calculates the area between
     * the funtion graph and the x Achsis.
     * numericly the integral is calculated by summing up infinitesimal surface elements
    */
    SHARED_LIB Dmath::Scalar IntegralOperator(Dmath::Parameters param, Dmath::SingleVarFunction func);


    // The loop integral of the second kind is defined as followed:
  //  ∫ V ds were V and the differential are given as vectors
  // expanded the Integral can be defined as:
  // ∫ V(K(t))  k'(t) dt 

    SHARED_LIB Dmath::Scalar loopIntegralSecondKind2D(Dmath::Parameters params, Dmath::SingleVectorFunction curve, Dmath::DoubleVectorFunction Field);

    template<typename Field>
    //Field Template to differentiate between vectorfield and scalarfields
    Dmath::Scalar LoopIntegral2D(Dmath::Parameters params, Field field, Dmath::SingleVectorFunction curve){

        //error checking

        if(!Dmath::checkParams(params)){ //Check for wrong parameters
            std::cerr << "Error Wrong Parameters Error code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
            return 0;
        }

        
        

        Dmath::Scalar result = 0; //The End result of the numeric integration
        Dmath::Natural num = Dmath::numberOfElements(params);

        for(size_t i = 0; i < num; i++){
            Dmath::Scalar currentIndex = params.one + i * params.three;

            //calculate the tangential vector
            Dmath::Vec3D tangentialVec = curve.getTangentialVectorAt(currentIndex);

            //Position vector
            Dmath::Vec3D posVec = curve(currentIndex);

            //Check for fist kind 2D loopintegral
            if constexpr(std::is_same<Field, Dmath::DoubleVarFunction>::value  ){
                Dmath::Scalar normVec = tangentialVec.getAbs();
                result += field(posVec.getX(), posVec.getY()) * normVec * params.three;
                continue;
            }

            //Check for second kind 2D loopintegral
            if constexpr(std::is_same<Field, Dmath::DoubleVectorFunction>::value){
                Dmath::Vec3D fieldPos = field(posVec.getX(), posVec.getY());
                
                result += (fieldPos * tangentialVec) * params.three;
                
                continue;
            }


        }
        return Dmath::roundTo(result,ROUNDING_VALUE);
    }

    SHARED_LIB Dmath::Scalar surfaceOfRotation(Dmath::Parameters params, Dmath::SingleVarFunction func);

    SHARED_LIB Dmath::Scalar volumeOfRotation(Dmath::Parameters params, Dmath::SingleVarFunction func);


    template<typename Field>
    Dmath::Scalar LoopIntegral3D(Dmath::Parameters params, Field fiels){}
    #pragma endregion //IntegralOperators

    #pragma region DifferentialOperators
    
    
 

 
    
    #pragma region SumOperators

    /*
     * This function calculates the sum form given boundaries i -> [a,b]
     * 
     * ∑( f(x) ) = f(a) + f(a + 1) + ... f(b)
     * 
     * scince Scalar functions and vector functions need to be handelt seperatly
     * there are different Sigma functions
     * 
     */
    SHARED_LIB Dmath::Scalar sumOverS(Dmath::Parameters param, Dmath::SingleVarFunction func);


    SHARED_LIB Dmath::Vec3D sumOverV(Dmath::Parameters param, Dmath::SingleVectorFunction func);

    #pragma endregion //SumOperators
    
        
    NAMESPACEEND





#endif //DMATH_OPERATOR_HPP