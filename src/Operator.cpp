#include"../include/Oprator.hpp"

Dmath::Scalar Dmath::IntegralOperator(Dmath::Parameters param, Dmath::SingleVarFunction func){
    if(!Dmath::checkParams(param)){
        std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return 0;
    }
    Dmath::Natural a = param.one;
    Dmath::Natural b = param.two;
    Dmath::Scalar dx = param.three;


    Dmath::Natural num = Dmath::numberOfElements(param);
    Dmath::Scalar  sum = 0;
    for(size_t i = 0; i < num; i++){
        Dmath::Scalar currentIteration = a + i * dx;
        Dmath::Scalar currentResult    = func(currentIteration) * dx;
        sum += currentResult; 
    }

    return sum;
} 


Dmath::Scalar Dmath::loopIntegralSecondKind2D(Dmath::Parameters params, Dmath::SingleVectorFunction curve, Dmath::DoubleVectorFunction field){
        if(!Dmath::checkParams(params)){
            std::cerr << "Error Wrong parameters! Error-code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
            return 0;
        }
        Dmath::Natural num = Dmath::numberOfElements(params);

        Dmath::Scalar result = 0;
        for(size_t i = 0; i < num; i++){
            Dmath::Scalar currentT = params.one + i * params.three;
            Dmath::Vec2D currentVec = curve.call2D(currentT);
            Dmath::Vec3D positionVector = field(currentVec); 
            //The X,y vectorfunction accepts parameters or vectors. => V(k->(t))

            Dmath::Vec3D derivedVector = curve.getTangentialVectorAt(currentT);

        result += positionVector.dotProduct(derivedVector) * params.three;

        }
        return result;
    }




    Dmath::Scalar Dmath::surfaceOfRotation(Dmath::Parameters params, Dmath::SingleVarFunction func){
        if(!Dmath::checkParams(params)){
            std::cerr << "Error Wrong Parameters Error code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
            return 0;
        }

        const Dmath::Natural a = static_cast<size_t>(params.one);
        const Dmath::Natural b = static_cast<size_t>(params.two);
        const Dmath::Scalar dx = params.three;

        Dmath::Scalar sum = 0;

        Dmath::Natural num = Dmath::numberOfElements(params);

        for(size_t i = 0; i < num; i++){
            Dmath::Scalar currentX = a + i * dx;

            Dmath::Scalar currentResult = 2 * PI * func(currentX) * std::sqrt(1 + (func.getDerivativeAt(currentX) * func.getDerivativeAt(currentX))) * dx;

            sum += currentResult;
        }

        return Dmath::roundTo(sum, ROUNDING_VALUE);
    }


    Dmath::Scalar Dmath::volumeOfRotation(Dmath::Parameters params, Dmath::SingleVarFunction func){
        if(!Dmath::checkParams(params)){
            std::cerr << "Error Wrong Parameters Error code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
            return 0;
        }

        const Dmath::Natural a = static_cast<size_t>(params.one);
        const Dmath::Natural b = static_cast<size_t>(params.two);
        const Dmath::Scalar dx = params.three;

        Dmath::Scalar sum = 0;

        Dmath::Natural num = Dmath::numberOfElements(params);

        for(size_t i = 0; i < num; i++){
            Dmath::Scalar currentX = a + i * dx;

            Dmath::Scalar currentResult = PI * (func(currentX) * func(currentX)) * dx;

            sum += currentResult;
        }

        return Dmath::roundTo(sum, ROUNDING_VALUE);
    }




Dmath::Scalar Dmath::sumOverS(Dmath::Parameters param, Dmath::SingleVarFunction func){
    if (!Dmath::checkParams(param)){
        std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return 0;
    }

    const Dmath::Natural a = static_cast<size_t>(param.one);
    const Dmath::Natural b = static_cast<size_t>(param.two);
    //const Dmath::Scalar dx = param.three;

    Dmath::Scalar sum = 0;

    for(size_t i = a; i <= b; i++){
        
        sum += func(i);
    }
    return sum;
}


Dmath::Vec3D Dmath::sumOverV(Dmath::Parameters param, Dmath::SingleVectorFunction func){
    if (!Dmath::checkParams(param)){
        std::cerr << "ERROR: Wrong parameters\nError code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return 0;
    }

    const Dmath::Natural a = static_cast<size_t>(param.one);
    const Dmath::Natural b = static_cast<size_t>(param.two);

    Dmath::Vec3D sum(0,0,0);

    for(size_t i = a; i <= b; i++){
        
        sum += func(i);
    }
    return sum;
}
