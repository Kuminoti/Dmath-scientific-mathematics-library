#pragma once

#ifndef DMATH_VARIABLE_HPP
#define DMATH_VARIABLE_HPP

#include"mathFunction.hpp"

NAMESPACESTART

/* File: Functional/Variable.hpp
 * Date: 15.08.26
 * Autor: D. Kuminoti
 * 
 * Use: Diese Klasse enthält den Datentypen: Dmath::Variable
 * Der als Hilfsdatentyp zur symbolischen konstruktion eines reellen funktionsobjektes verwendet wird
 * Über operatoren und hilfs funktionen werden sowohl funktionsobjekte geschaffen, so wie auch
 * Informationen über die funktionen gespeichert, um analytische operatoren symbolisch berechenen zu können
 *  
*/


class Variable{

  private: //private members

    std::string stringFunc; //string vector for storing information 



  public: //constructors

    Variable() : stringFunc("X") {}


  private: //private member functions

    Dmath::SingleVarFunction makeFunction(const Variable& var){
        return SingleVarFunction(
            [](Dmath::Scalar x) -> Dmath::Scalar {
                return x;
            }
        );
    }



    Dmath::SingleVarFunction makeFunction(const SingleVarFunction& func){
        return func;
    }


    template<typename T>
    Dmath::SingleVarFunction makeFunction(T value){
        if(!Dmath::is_numeric<T>::value){
            std::cerr << "Error: Wrong data type!\n" + 
            " makeFunction(T value): => T requires numeric type!\n" +
            "Error code: " << Dmath::ERROR_CODE::WRONG_TYPE << std::endl;

            return Dmath::SingleVarFunction([](Dmath::Scalar x){return Dmath::NaN;});
        }
        return Dmath::SingleVarFunction(
            [value](Dmath::Scalar) -> Dmath::Scalar {
                return static_cast<Dmath::Scalar>(value);
            }
        );
    }

  public: //operators



  template<typename dmath>
Dmath::SingleVarFunction operator+(dmath func){
    std::string funcInfo;

    if constexpr (Dmath::is_numeric<dmath>::value) {
        Dmath::Scalar c = static_cast<Dmath::Scalar>(func);
        funcInfo = "X + " + std::to_string(c);
        Dmath::Function g = [c]() -> Dmath::Scalar {
            return c;
        };
        this->stringFunc = funcInfo;
        auto lhs = makeFunction(*this);
        return lhs + g;
    }
    else if constexpr (
        std::is_same<dmath, Dmath::SingleVarFunction>::value) {

        funcInfo = "X + f(x)";

    }
    else if constexpr (
        std::is_same<dmath, Variable>::value) {

        funcInfo = "X + " + func.getFuncInfo();
    }

    this->stringFunc = funcInfo;

    // Beide Seiten auf SingleVarFunction abbilden
    auto lhs = makeFunction(*this);
    auto rhs = makeFunction(func);

    return lhs + rhs;
}

  template<typename dmath>
    Dmath::SingleVarFunction operator-(dmath func){
        std::string funcInfo = "";

        //create the functionString

        if constexpr(Dmath::is_numeric<dmath>::value){
            //Functionstring after adding a real number
            funcInfo += "X - " + std::to_string(func);
        }
        else if constexpr (std::is_same<dmath, Dmath::SingleVarFunction>::value){
            //Functionstring after adding an unkowen function
            funcInfo += "X - f(x)";
        }
        else if constexpr (std::is_same<dmath,Variable>::value){
            //Functionstring after adding an other Variable
            funcInfo += "X - " + func.getFuncInfo();
        }

        this->stringFunc = funcInfo;
        //Create the Function
        return Dmath::SingleVarFunction([func](Dmath::Scalar x){return x - func;});
    }


  template<typename dmath>
    Dmath::SingleVarFunction operator*(dmath func){
        std::string funcInfo = "";

        //create the functionString

        if constexpr(Dmath::is_numeric<dmath>::value){
            //Functionstring after adding a real number
            funcInfo += "X * " + std::to_string(func);
        }
        else if constexpr (std::is_same<dmath, Dmath::SingleVarFunction>::value){
            //Functionstring after adding an unkowen function
            funcInfo += "X * f(x)";
        }
        else if constexpr (std::is_same<dmath,Variable>::value){
            //Functionstring after adding an other Variable
            funcInfo += "X * " + func.getFuncInfo();
        }

        this->stringFunc = funcInfo;
        //Create the Function
        return Dmath::SingleVarFunction([func](Dmath::Scalar x){return x * func;});
    }

    template<typename dmath>
    Dmath::SingleVarFunction operator/(dmath func){
        std::string funcInfo = "";

        //create the functionString

        if constexpr(Dmath::is_numeric<dmath>::value){
            //Check for division by zero:
            if(func == 0){
                std::cerr << "Error while constructing SingleVarFunction from Variable\n Cause: Division By Zero\n Error-Code: " << Dmath::ERROR_CODE::DIVISION_BY_ZERO<<std::endl;
                return Dmath::SingleVarFunction([](Dmath::Scalar x)->Dmath::Scalar {Dmath::INF;});
            }

            //Functionstring after adding a real number
            funcInfo += "X / " + std::to_string(func);
        }
        else if constexpr (std::is_same<dmath, Dmath::SingleVarFunction>::value){
            //Functionstring after adding an unkowen function
            funcInfo += "X / " + func.getFunctionData(); //Division by zero is checked in the SingleVarFunction class
        }
        else if constexpr (std::is_same<dmath,Variable>::value){
            //Functionstring after adding an other Variable
            funcInfo += "X / " + func.getFuncInfo();
        }


        this->stringFunc = funcInfo;
        //Create the Function
        return Dmath::SingleVarFunction([func](Dmath::Scalar x){return x / func;});
    }

    
  public: //getters and setters
    inline std::string getFuncInfo(){
        return this->stringFunc;
    }
    void addInfo(std::string info){
        this->stringFunc += info;
    }

};



NAMESPACEEND

#endif //DMATH_VARIABLE_HPP