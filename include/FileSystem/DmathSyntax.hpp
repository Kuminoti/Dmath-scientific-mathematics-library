#pragma once

#ifndef DMATH_SYNTAX_HPP
#define DMATH_SYNTAX_HPP


#include"DmathFile.hpp"
NAMESPACESTART

//Object definitions in Dmath: 
//
//Dmath::objDef : 1.Type, 2 name, 3.data
//Example 1.Vector2D, 2.v, 3.(1,1)
typedef Dmath::Trio<std::string,std::string,std::string> ObjDef;

             

ObjDef getTypeData(std::string inputData){
    Dmath::StringHelper strH;
    const std::string type = strH.extractFirstWord(inputData);
    const std::string name = strH.extractWords( inputData,type, "=");
    const std::string data = strH.extractFromTo(inputData, '=', ';');

    return ObjDef(type,name,data);

}


std::string fileVector2D(std::string vecName, Dmath::Vec2D vec){

    std::string fileVec =  vecName + " = (" +
    std::to_string(vec.getX()) + ", " + std::to_string(vec.getY());

    if( vec.getOriginX() != 0 || vec.getOriginY() != 0){
        fileVec += ", " + std::to_string(vec.getOriginX()) + 
                    ", " + std::to_string(vec.getOriginY());
    }
    fileVec +=");\n\t";

    return fileVec;
}

std::string fileVector3D(std::string vecName, Dmath::Vec3D vec){
    std::string fileVec =  vecName + " = (" +
    std::to_string(vec.getX()) + ", " + std::to_string(vec.getY()) + "," +
    std::to_string(vec.getZ());

    if( vec.getOriginX() != 0 || vec.getOriginY() != 0 || vec.getOriginZ() != 0){
        fileVec += ", " + std::to_string(vec.getOriginX()) + 
                    ", " + std::to_string(vec.getOriginY()) +
                    ", " + std::to_string(vec.getOriginZ());
    }
    fileVec +=");\n\t";

    return fileVec;
}
   

Dmath::Vec2D getFromFileVec(ObjDef data){

    Dmath::StringHelper strH;
    auto nums = strH.getNumbersInBrackets(data.three);
                

    if(nums.size() < 1 || nums.size() == 3 || nums.size() > 4){
        std::cerr << "Build Error: \nDmath::FreeMap<std::string> loadDmathFile(std::string filePath): \n" 
            << "Error while building Vec2D: expected 1, 2 or 4 arguments but got: " << nums.size()  << std::endl 
            << "Dmath::ERROR_CODE: " << Dmath::ERROR_CODE::OUT_OF_RANGE << std::endl;
        }

    Dmath::Vec2D vec(nums[0], nums[1]);
    if(nums.size() == 4){
        vec.setOriginX(nums[2]);
        vec.setOriginY(nums[3]);
    }

    return vec;
}


Dmath::Vec3D getFromFileVec3D(ObjDef data){
    Dmath::StringHelper strH;
    auto nums = strH.getNumbersInBrackets(data.three);


    if( nums.size() > 6){
        std::cerr << "Build Error: \nDmath::FreeMap<std::string> loadDmathFile(std::string filePath): \n" 
                  << "Error while building Vec3D: expected 1, 3 or 6 arguments but got: " << nums.size()  << std::endl 
                  << "Dmath::ERROR_CODE: " << Dmath::ERROR_CODE::OUT_OF_RANGE << std::endl;
    }

    Dmath::Vec3D vec(nums[0], nums[1], nums[2]);
    if(nums.size() == 6){
        vec.setOriginX(nums[3]);
        vec.setOriginY(nums[4]);
        vec.setOriginZ(nums[5]);
    }

    return vec;
}


NAMESPACEEND

#endif //DMATH_SYNTAX_HPP