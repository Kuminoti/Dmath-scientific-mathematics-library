#include"../include/Complex/complexFunctions.hpp"

Dmath::Scalar Dmath::logarithm(Dmath::Scalar logBase, Dmath::Scalar power) {
    if (power == 1) return 0;
    if (logBase == power) return 1;
    if (logBase <= 0 || power <= 0) return -1; 

    Dmath::Scalar low = 0;
    Dmath::Scalar high = power; 
    Dmath::Scalar mid;
    const Dmath::Scalar epsilon = 1e-6; 

    while (high - low > epsilon) { 
        mid = (low + high) / 2.0;  
        Dmath::Scalar currentResult = std::pow(logBase, mid); 

        if (std::abs(currentResult - power) < epsilon) {
            return mid; 
        }
        if (currentResult < power) {
            low = mid;  
        } else {
            high = mid; 
        }
    }
    return mid;  
}




Dmath::Complex Dmath::complexLn(Dmath::Scalar power){

    if (power == 0) {
        throw std::domain_error("Ln(0) is not defined");
    }

    if(power > 0 ){
        Dmath::Scalar real = std::log(power);
        return Dmath::Complex(real,0);
    }

    Dmath::Scalar real = std::log(std::abs(power));
    Dmath::Scalar img  = PI;

    return Dmath::Complex(real, img);

}


Dmath::Complex Dmath::complexBaseLog(Dmath::Scalar logBase, Dmath::Scalar power) {
    if (power == 0) {
        throw std::domain_error("Log(0) is not defined");
    }

    if (logBase == 0) {
        throw std::domain_error("Log Base 0 is not defined");
    }

    if (power > 0 && logBase > 0) {
        Dmath::Scalar real = std::log(power) / std::log(logBase);
        return Dmath::Complex(real, 0);
    }

    Dmath::Complex componentOne;
    Dmath::Complex componentTwo;

    Dmath::Scalar realPartPower = std::log(std::abs(power));
    Dmath::Scalar imagPartPower = (power < 0) ? PI : 0;
    componentOne.setNumber(realPartPower, imagPartPower);

    Dmath::Scalar realPartBase = std::log(std::abs(logBase));
    Dmath::Scalar imagPartBase = (logBase < 0) ? PI : 0;
    componentTwo.setNumber(realPartBase, imagPartBase);

    
    Dmath::Complex result = componentOne / componentTwo;
    return result;
}




Dmath::Complex Dmath::complexExponent(Dmath::Scalar base, Dmath::Complex complexNum) {
    Dmath::Scalar logBaseReal;
    Dmath::Scalar logBaseImag = 0;

    if (base > 0) {
        logBaseReal = std::log(base);  
    } else if (base < 0) {
        logBaseReal = std::log(std::abs(base));  
        logBaseImag = PI;  
    } else {
        throw std::domain_error("Log Base 0 is nott defined");
    }

    Dmath::Scalar realPart = logBaseReal * complexNum.getRealPart() - logBaseImag * complexNum.getImaginaryPart();
    Dmath::Scalar imaginaryPart = logBaseReal * complexNum.getImaginaryPart() + logBaseImag * complexNum.getRealPart();

    Dmath::Complex result = Dmath::Complex(realPart, imaginaryPart).exp();

    return result;
}






Dmath::Complex Dmath::complexSine(Dmath::Complex complexNum){

    const Dmath::Scalar givenReal = complexNum.getRealPart(); //To avoid lage function calls
    const Dmath::Scalar givenImg  = complexNum.getImaginaryPart();


    Dmath::Scalar summandOne = std::sin(givenReal) * Dmath::cosh(givenImg);
    Dmath::Scalar summandTwo = std::cos(givenReal) * Dmath::sinh(givenImg);
   
     
    Dmath::Complex result(summandOne, summandTwo);
    return result;
}


Dmath::Complex Dmath::complexCosine(Dmath::Complex complexNum){

    const Dmath::Scalar givenReal = complexNum.getRealPart(); //To avoid lage function calls
    const Dmath::Scalar givenImg  = complexNum.getImaginaryPart();


    Dmath::Scalar summandOne = std::cos(givenReal) * Dmath::cosh(givenImg);
    Dmath::Scalar summandTwo = std::sin(givenReal) * Dmath::sinh(givenImg);

     
    Dmath::Complex result(summandOne, summandTwo);
    return result;
}

Dmath::Complex Dmath::complexTangent(Dmath::Complex complexNum){
    Dmath::Complex complexS = Dmath::complexSine  (complexNum);
    Dmath::Complex complexC = Dmath::complexCosine(complexNum);

    Dmath::Complex result = complexS/complexC;
    return result;
}



Dmath::Complex Dmath::complexCotangent(Dmath::Complex complexNum){
    Dmath::Complex complexS = Dmath::complexSine  (complexNum);
    Dmath::Complex complexC = Dmath::complexCosine(complexNum);

    Dmath::Complex result = complexC/complexS;
    return result;
}

Dmath::Complex Dmath::complexSecant(Dmath::Complex complexNum) {
    Dmath::Complex complexC = Dmath::complexCosine(complexNum);

    // Sekans ist der Kehrwert des Kosinus
    Dmath::Complex result = Dmath::Complex(1.0, 0.0) / complexC;
    return result;
}

Dmath::Complex Dmath::complexCosecant(Dmath::Complex complexNum) {
    Dmath::Complex complexS = Dmath::complexSine(complexNum);

    // Kosekans ist der Kehrwert des Sinus
    Dmath::Complex result = Dmath::Complex(1.0, 0.0) / complexS;
    return result;
}



Dmath::Complex Dmath::complexHyperbolicSine(Dmath::Complex complexNum){

    Dmath::Complex componentOne = Dmath::complexExponent(EULER,complexNum);


    const Dmath::Complex NegativeComplex(-complexNum.getRealPart(),-complexNum.getImaginaryPart());

    Dmath::Complex componentTwo = Dmath::complexExponent(EULER,NegativeComplex);

    Dmath::Complex result = (componentOne - componentTwo)/2;

    return result;

}