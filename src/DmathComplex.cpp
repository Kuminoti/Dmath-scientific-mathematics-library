#include"../include/Complex/complexFunctions.hpp"


#pragma region Class basics

Dmath::Complex::Complex(){
    this->real = 0;
    this->img  = 0;

    this->absolute   = 0;
    this->phaseAngle = 0;
}

Dmath::Complex::Complex(double real, double img){
    this->real = real;
    this->img  = img;
    this->update();
    
}

Dmath::Complex::Complex(double real, Dmath::ImaginaryNumber img){
    this->real = real;
    this->img  = img.i;
    this->update();
}

void Dmath::Complex::update(){
    this->absolute   = Dmath::pyth2(real,img);
    this->phaseAngle = std::atan2(img, real);
}

void Dmath::Complex::addImaginary(double img){
    this->img+=img;
    this->update();
}

void Dmath::Complex::addReal(double real){
    this->real+=real;
    this->update();
}

void Dmath::Complex::setNumber(double real, double img){
    this->real = real;
    this->img  = img;
    this->update();
}


void Dmath::Complex::setImaginaryPart(double img){
    this->img = img;
    this->update();
}

void Dmath::Complex::setRealPart(double real){
    this->real = real;
    this->update();
}

void Dmath::Complex::conjugate(){
    this->img = -this->img;
    this->update();
}

#pragma endregion

void Dmath::Complex::operator=(Dmath::Complex num){
    this->img  = num.getImaginaryPart();
    this->real = num.getRealPart();

    this->update();
}


#pragma region Logic Operators

bool Dmath::Complex::operator==(Dmath::Complex num){
    if(this->img == num.getImaginaryPart() && this->real == num.getRealPart()){
        return true;
    }
    return false;
}

bool Dmath::Complex::operator!=(Dmath::Complex num){
    if(this->img != num.getImaginaryPart() || this->real != num.getRealPart()){
        return true;
    }
    return false;
}

bool Dmath::Complex::operator!=(Dmath::Scalar num){
    return this->absolute != num;
}

bool Dmath::Complex::operator==(Dmath::Scalar num){
    return this->absolute == num;
}

bool Dmath::Complex::operator<(Dmath::Complex num){
    return this->absolute < num.getAbsolute();
}

bool Dmath::Complex::operator>(Dmath::Complex num){
    return this->absolute > num.getAbsolute();
}

bool Dmath::Complex::operator>=(Dmath::Complex num){
    return this->absolute >= num.getAbsolute();
}

bool Dmath::Complex::operator<=(Dmath::Complex num){
    return this->absolute <= num.getAbsolute();
}




bool Dmath::Complex::operator<(Dmath::Scalar num){
    return this->absolute < num;
}

bool Dmath::Complex::operator>(Dmath::Scalar num){
    return this->absolute > num;
}

bool Dmath::Complex::operator>=(Dmath::Scalar num){
    return this->absolute >= num;
}

bool Dmath::Complex::operator<=(Dmath::Scalar num){
    return this->absolute <= num;
}

#pragma endregion //Logic operators



#pragma region Mathmatical operators

Dmath::Complex Dmath::Complex::operator+(Dmath::Complex num){
    double newReal = this->real + num.getRealPart();
    double newImg  = this->img  + num.getImaginaryPart(); 
    return Complex(newReal, newImg);
}

Dmath::Complex Dmath::Complex::operator-(Dmath::Complex num){
    double newReal = this->real - num.getRealPart();
    double newImg  = this->img  - num.getImaginaryPart(); 
    return Complex(newReal, newImg);
}

Dmath::Complex Dmath::Complex::operator*(Complex num) {
    double newReal = (real * num.real) - (img * num.img);
    double newImag = (real * num.img) + (img * num.real);
    return Complex(newReal, newImag);
}

Dmath::Complex Dmath::Complex::operator/(Complex num) {
    double denominator = (num.real * num.real) + (num.img * num.img);
    
    if (denominator == 0) {
        throw std::runtime_error("Division durch Null ist nicht definiert.");
    }

    double newReal = ((real * num.real) + (img * num.img)) / denominator;
    double newImag = ((img * num.real) - (real * num.img)) / denominator;
    
    return Complex(newReal, newImag);
}


Dmath::Complex Dmath::Complex::operator/(Dmath::Scalar num){
    Dmath::Scalar real = this->real/num;
    Dmath::Scalar imga = this->img /num;

    return Dmath::Complex(real,imga);
}


Dmath::Complex& Dmath::Complex::operator+=(const Complex& num) {
    real += num.real;
    img += num.img;
    update();
    return *this;
}


Dmath::Complex& Dmath::Complex::operator-=(const Complex& num) {
    real -= num.real;
    img -= num.img;
    update();
    return *this;
}

std::ostream& Dmath::operator<<(std::ostream& os, Dmath::Complex num) {
    std::string str_real = std::to_string( num.getRealPart() );
    std::string str_img  = std::to_string( num.getImaginaryPart() );


    std::string str_complex = str_real + " + " + str_img + " *i ";
    os <<  str_complex;
    return os;
}

Dmath::Complex Dmath::Complex::exp() {
    
    double expReal = std::exp(real);

    
    double cosImg = std::cos(img);
    double sinImg = std::sin(img);

    
    Dmath::Complex result(expReal * cosImg, expReal * sinImg);

    
    return result;
}





Dmath::Vec2D Dmath::Complex::getVector(){
    Dmath::Scalar vecX = this->real;
    Dmath::Scalar vecY = this->img;

    Dmath::Vec2D complexVector(vecX,vecY);
    return complexVector;
}

CoordinateSystem2D Dmath::Complex::polarForm(){
    return CoordinateSystem2D(this->real, this->img);
}

double Dmath::Complex::getRealPart()     { return this->real;     }
double Dmath::Complex::getImaginaryPart(){ return this->img;      }
double Dmath::Complex::getAbsolute()     { return this->absolute; }



#pragma region Complex Funcs



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

#pragma endregion