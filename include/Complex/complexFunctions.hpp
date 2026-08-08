#pragma once 

#ifndef DMATH_COMPLEX_FUNCTIONS_HPP
#define DMATH_COMPLEX_FUNCTIONS_HPP

#include"complex.hpp"


NAMESPACESTART

//Predifined functions

//Complex logs
Dmath::Scalar logarithm(Dmath::Scalar logBase, Dmath::Scalar power);
Dmath::Complex complexLn(Dmath::Scalar power);
Dmath::Complex complexBaseLog(Dmath::Scalar logBase, Dmath::Scalar power);

//Exponents
Dmath::Complex complexExponent(Dmath::Scalar base, Dmath::Complex complexNum);

//Complex Trigonemetry

//basic trigfunctions
Dmath::Complex complexSine   (Dmath::Complex complexNum);
Dmath::Complex complexCosine (Dmath::Complex complexNum);
Dmath::Complex complexTangent(Dmath::Complex complexNum);


//the "other" tric functions

Dmath::Complex complexSecant(Dmath::Complex complexNum);
Dmath::Complex complexCosecant(Dmath::Complex complexNum);
Dmath::Complex complexCotangent(Dmath::Complex complexNum);

//Hyperbolic functions
Dmath::Complex complexHyperbolicSine(Dmath::Complex complexNum);


class ComplexFunctionBase{
    public:
    
        virtual ~ComplexFunctionBase() = default;
        virtual Dmath::Complex callComplex(Dmath::Complex com) = 0;
    
        virtual std::unique_ptr<ComplexFunctionBase> clone() = 0;
    };
    
    template<class CFunc>
    class ComplexFunctionWrapper : public Dmath::ComplexFunctionBase{
    private:
        CFunc complexFunc;
        public:
    
    
        std::unique_ptr<ComplexFunctionBase> clone()  override {
            return std::make_unique<ComplexFunctionWrapper<CFunc>>(complexFunc);
        }
    
        
        ComplexFunctionWrapper(CFunc function) : complexFunc(function){}
    
    
        Dmath::Complex callComplex(Dmath::Complex num) override {
            return complexFunc(num);
        }
    };
    
    
    class ComplexFunction{
        std::unique_ptr<ComplexFunctionBase> funcBase;
    
    
        public: 
        ComplexFunction& operator=(const ComplexFunction other){
            if (this != &other) {
                this->funcBase = other.funcBase ? other.funcBase->clone() : nullptr;
            }
            return *this;
        }
    
        template<typename Callable>
        ComplexFunction& operator=(Callable func) {
            this->funcBase = std::make_unique<ComplexFunctionWrapper<Callable>>(func);
            return *this;
        }
    
        ComplexFunction& operator=(ComplexFunction&& other) noexcept {
            if (this != &other) {
                this->funcBase = std::move(other.funcBase);
            }
            return *this;
        }
    
        template<typename Callable>
        ComplexFunction(Callable func) : funcBase(std::make_unique<ComplexFunctionWrapper<Callable>>(func)) {}
    
        ComplexFunction(const ComplexFunction& other)
        : funcBase(other.funcBase ? other.funcBase->clone() : nullptr) {}
    
        ComplexFunction() = default;
    
    
        Dmath::Complex operator()(Dmath::Complex com) {
            if (funcBase) {
                return funcBase->callComplex(com); // Delegate the call to the stored function
            }
            return Dmath::Complex(0,0); // Return a default value if no function is stored
        }
    
    };
    
NAMESPACEEND

#endif //DMATH_COMPLEX_FUNCTIONS_HPP