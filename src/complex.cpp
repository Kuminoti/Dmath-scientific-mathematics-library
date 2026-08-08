#include"../include/Complex/complex.hpp"


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



#pragma region Extern functions


#pragma endregion //Extern functions