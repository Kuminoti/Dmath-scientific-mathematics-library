#pragma once

#ifndef DMATH_TRIANGLE_HPP
#define DMATH_TRIANGLE_HPP

#include"mathVector.hpp"


NAMESPACESTART

struct Triangle{

Dmath::Vec3D OPA; //Ortsvector Punkt A  
Dmath::Vec3D OPB;
Dmath::Vec3D OPC;

Dmath::Vec3D Normal;

Triangle(Dmath::Vec3D OPA, Dmath::Vec3D OPB,Dmath::Vec3D OPC) :
         OPA(OPA), OPB(OPB), OPC(OPC) {

    auto VAB = OPB - OPA;
    auto VAC = OPC - OPA;
    Normal = VAB.vecProduct(VAC);  // N-> = VAC-> X VAC->

    }  
    friend std::ostream& operator<<(std::ostream& os, const Triangle& Tri);
};

std::ostream& operator<<(std::ostream& os, const Triangle& Tri){
    os << Tri.OPA << '\n' << Tri.OPA << '\n' << Tri.OPA << "\n" << "Normal: " << Tri.Normal << "\n";
    return os;
}


std::vector<Triangle> approximateTris(Dmath::DoubleVectorFunction& func, Dmath::Parameters paramsU, Dmath::Parameters paramsV){

    std::vector<Triangle> tris;
    if(!Dmath::checkParams(paramsU) || !Dmath::checkParams(paramsV)){
        std::cerr << "Error approximateTris(...) parameter error\n Error-code: " 
                  << Dmath::ERROR_CODE::WRONG_PARAMETER << std::endl;
                  tris.clear();
                  return tris;
    }

    Dmath::Natural numU = Dmath::numberOfElements(paramsU);
	Dmath::Natural numV = Dmath::numberOfElements(paramsV);


    for (size_t i = 0; i + 1 < numU; ++i) {
    	auto u0 = Dmath::currentElement(paramsU.one, paramsU.three, i);
    	auto u1 = Dmath::currentElement(paramsU.two, paramsU.three, i + 1);

		for (size_t j = 0; j + 1 < numV; ++j) {
			auto v0 = Dmath::currentElement(paramsV.one, paramsV.three, j);
			auto v1 = Dmath::currentElement(paramsV.two, paramsV.three, j + 1);

			auto A = func(u0, v0);
			auto B = func(u1, v0);
			auto C = func(u0, v1);
			auto D = func(u1, v1);

        	tris.emplace_back(A, B, C);
        	tris.emplace_back(B, D, C);
    	}
	}
    return tris;
}



std::string stringifySTL(Triangle& tri){

    auto normalStr = Dmath::vecToPoint(tri.Normal);

    auto vertexA   = Dmath::vecToPoint(tri.OPA);
    auto vertexB   = Dmath::vecToPoint(tri.OPB);
    auto vertexC   = Dmath::vecToPoint(tri.OPC);

    std::string Msg = "\tfacet normal " +  normalStr.X +" "+ normalStr.Y + " " + normalStr.Z + "\n";
    Msg += "\t\touter loop\n";
    Msg += "\t\t\tvertex "+ vertexA.X +" "+ vertexA.Y + " " + vertexA.Z + "\n";
    Msg += "\t\t\tvertex "+ vertexB.X +" "+ vertexB.Y + " " + vertexB.Z + "\n";
    Msg += "\t\t\tvertex "+ vertexC.X +" "+ vertexC.Y + " " + vertexC.Z + "\n";
    Msg += "\t\tendloop\n";
    Msg += "\tendfacet \n";
   


    return Msg;
};



NAMESPACEEND
#endif //DMATH_TRIANGLE_HPP