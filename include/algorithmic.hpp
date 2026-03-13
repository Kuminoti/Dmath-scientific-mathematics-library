#pragma once 

#ifndef DMATH_ALGORITHMIC_HPP
#define DMATH_ALGORITHMIC_HPP

#include"vectorfunction.hpp"

NAMESPACESTART


//Manipulates every element in a vector by refference using single variable functions 
void dfor_each(std::vector<Dmath::Scalar>& data, Dmath::SingleVarFunction func){
    for(auto& v : data){
        v = func(v);
    }
}


std::vector<Dmath::Scalar> map(const std::vector<Dmath::Scalar>& data, Dmath::SingleVarFunction func){
    std::vector<Dmath::Scalar> result;
    result.reserve(data.size());
    for(auto v : data){
        result.push_back(func(v));
    }
    return result;
}

//Creates a map |f(x)/x| 
Dmath::MapD<Dmath::Scalar,Dmath::Scalar> ValueTable(Dmath::SingleVarFunction func, Dmath::Parameters params){
    Dmath::MapD<Dmath::Scalar,Dmath::Scalar> mainMap;
    if(!checkParams(params)){
        std::cerr << "Error Invalid parameters! Error-code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
    }
    Dmath::Natural num = Dmath::numberOfElements(params);
    const Dmath::Scalar stepp = params.three;
    const Dmath::Scalar start = params.one;
    for(size_t i = 0; i < num; i++){
        Dmath::Scalar currentX = start + stepp * 1;
        mainMap.insert(currentX,func(currentX));
    }
    return mainMap;
}


NAMESPACEEND

#endif //DMATH_ALGORITHMIC_HPP