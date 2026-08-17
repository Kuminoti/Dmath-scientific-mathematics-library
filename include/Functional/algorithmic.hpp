#pragma once 

#ifndef DMATH_ALGORITHMIC_HPP
#define DMATH_ALGORITHMIC_HPP

#include"vectorfunction.hpp"
#include"Vector/point.hpp"



/* File: algorithmic.hpp
 * This file contains different types of algorithems based on Dmath objects
 * SingleVarFunctions
 * Vectors 
 * etc...
*/



NAMESPACESTART

#pragma region Scalar+function

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


#pragma endregion 


#pragma region Vector algorithms



Dmath::Vec3D getMaxVec(std::vector<Dmath::Vec3D> vectorPath){

    Dmath::Scalar maxV = vectorPath[0].getAbs();
    Dmath::Vec3D maxVec;

    Dmath::Natural num = vectorPath.size();

    for(size_t i = 1; i <num; i++){
       if(vectorPath[i].getAbs() > maxV){
        maxV = vectorPath[i].getAbs();
        maxVec = vectorPath[i];
       }
       continue;
    }

    return maxVec;

}


Dmath::Scalar getMaxX(std::vector<Dmath::Vec3D> vectorPath){

    Dmath::Scalar maxX = 0
    
    Dmath::Natural num = vectorPath.size();

    for(size_t i = 1; i <num; i++){
       if(vectorPath[i].getX() > maxX){
        maxX = vectorPath[i].getX();
       }
       continue;
    }

    return maxX;

}

Dmath::Scalar getMaxY(std::vector<Dmath::Vec3D> vectorPath){

    Dmath::Scalar maxY = 0
    
    Dmath::Natural num = vectorPath.size();

    for(size_t i = 1; i <num; i++){
       if(vectorPath[i].getY() > maxY){
        maxY = vectorPath[i].getY();
       }
       continue;
    }

    return maxY;

}

Dmath::Scalar getMaxZ(std::vector<Dmath::Vec3D> vectorPath){

    Dmath::Scalar maxZ = 0
    
    Dmath::Natural num = vectorPath.size();

    for(size_t i = 1; i <num; i++){
       if(vectorPath[i].getZ() > maxZ){
        maxZ = vectorPath[i].getZ();
       }
       continue;
    }

    return maxZ;

}


std::vector<Dmath::Point> convertCurve(Dmath::SingleVectorFunction func, Dmath::Parameters params){
    if(!Dmath::checkParams(params)){
        std::cerr << "Error wrong Parameters! Error-code: " << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
        return std::vector<Dmath::Point> ();
    }

    std::vector<Dmath::Point> points
    Dmath::Natural num = Dmath::numberOfElements(params);

    for(size_t i = 0; i < num; i++){
        Dmath::Scalar currentT = params.one + i * params.three;
        points.push_back(Dmath::vecToPoint(func(currentT)));
    }
    return points;
}

std::vector<Dmath::Vec3D> linkVectors(std::vector<Dmath::Vec3D> vecs){
    std::vector<Dmath::Vec3D> newVecs;

    Dmath::Natural num = vecs.size();

    if(num == 0){
        return newVecs;
    }

    //Erster Vektor bleibt unverändert
    Dmath::Vec3D currentVec = vecs[0];

    newVecs.push_back(currentVec);


    for(size_t i = 1; i < num; i++){

        Dmath::Vec3D newVec = vecs[i];

        //Ursprung = Spitze des vorherigen Vektors
        newVec.originX =
            currentVec.originX + currentVec.X;

        newVec.originY =
            currentVec.originY + currentVec.Y;

        newVec.originZ =
            currentVec.originZ + currentVec.Z;


        newVecs.push_back(newVec);

        currentVec = newVec;
    }


    return newVecs;
}




#pragma endregion

NAMESPACEEND

#endif //DMATH_ALGORITHMIC_HPP