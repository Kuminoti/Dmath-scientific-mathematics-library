#include "../include/vectorfunction.hpp"
#pragma region single

Dmath::SingleVectorFunction::SingleVectorFunction(
    const Dmath::SingleVarFunction& x,
    const Dmath::SingleVarFunction& y
)
    : xOfT(x),
      yOfT(y),
      zOfT([](double){ return 0.0; })
{}

Dmath::SingleVectorFunction::SingleVectorFunction(
    const Dmath::SingleVarFunction& x,
    const Dmath::SingleVarFunction& y,
    const Dmath::SingleVarFunction& z
)
    : xOfT(x),
      yOfT(y),
      zOfT(z)
{}

Dmath::Vec2D Dmath::SingleVectorFunction::call2D(Dmath::Scalar t){
    return Dmath::Vec2D(xOfT(t), yOfT(t));
}

Dmath::Vec3D Dmath::SingleVectorFunction::operator ()(Dmath::Scalar t){
    const Dmath::Scalar currentX = this->xOfT(t);
    const Dmath::Scalar currentY = this->yOfT(t);
    const Dmath::Scalar currentZ = this->zOfT(t);
    
    return Dmath::Vec3D(currentX, currentY, currentZ);
}


Dmath::SingleVectorFunction Dmath::SingleVectorFunction::operator+(Dmath::SingleVectorFunction funcTwo){
    Dmath::SingleVarFunction newX = this->getXFunc() + funcTwo.getXFunc();
    Dmath::SingleVarFunction newY = this->getYFunc() + funcTwo.getYFunc();
    Dmath::SingleVarFunction newZ = this->getZFunc() + funcTwo.getZFunc();

    Dmath::SingleVectorFunction newFunc(newX,newY,newZ);
    return newFunc;
}

Dmath::SingleVectorFunction Dmath::SingleVectorFunction::operator-(Dmath::SingleVectorFunction funcTwo){
    Dmath::SingleVarFunction newX = this->getXFunc() - funcTwo.getXFunc();
    Dmath::SingleVarFunction newY = this->getYFunc() - funcTwo.getYFunc();
    Dmath::SingleVarFunction newZ = this->getZFunc() - funcTwo.getZFunc();

    Dmath::SingleVectorFunction newFunc(newX,newY,newZ);
    return newFunc;
}

Dmath::SingleVarFunction Dmath::SingleVectorFunction::operator*(Dmath::SingleVectorFunction funcTwo){


    //Copying all functions to avoid bugs caused by missing refrences

    Dmath::SingleVarFunction xTwo = funcTwo.getXFunc();
    Dmath::SingleVarFunction yTwo = funcTwo.getYFunc();
    Dmath::SingleVarFunction zTwo = funcTwo.getZFunc();

    Dmath::SingleVarFunction xFunc = this->getXFunc();
    Dmath::SingleVarFunction yFunc = this->getYFunc();
    Dmath::SingleVarFunction zFunc = this->getZFunc();

    Dmath::SingleVarFunction XX = xFunc * xTwo;
    Dmath::SingleVarFunction YY = yFunc * yTwo;
    Dmath::SingleVarFunction ZZ = zFunc * zFunc;
    
    Dmath::SingleVarFunction scalarFunc = XX + YY + ZZ;
    
    return Dmath::SingleVarFunction(scalarFunc);
}

//operator for crossproducts
Dmath::SingleVectorFunction Dmath::SingleVectorFunction::crossProduct(Dmath::SingleVectorFunction func){

    //Copying all functions to avoid bugs caused by missing refrences

    Dmath::SingleVarFunction thisX = this->getXFunc();
    Dmath::SingleVarFunction thisY = this->getYFunc();
    Dmath::SingleVarFunction thisZ = this->getZFunc();

    Dmath::SingleVarFunction funcX = func.getXFunc();
    Dmath::SingleVarFunction funcY = func.getYFunc();
    Dmath::SingleVarFunction funcZ = func.getZFunc();

    // Berechnung der Komponenten des Kreuzprodukts
    Dmath::SingleVarFunction crossX = thisY * funcZ - thisZ * funcY;
    Dmath::SingleVarFunction crossY = thisZ * funcX - thisX * funcZ;
    Dmath::SingleVarFunction crossZ = thisX * funcY - thisY * funcX;

    // Rückgabe einer neuen Vektorfunktion mit den berechneten Komponenten
    return Dmath::SingleVectorFunction(crossX, crossY, crossZ);
}

Dmath::Vec3D Dmath::SingleVectorFunction::getTangentialVectorAt(Dmath::Scalar t){
    const Dmath::Scalar dx = this->xOfT.getDerivativeAt(t);
    const Dmath::Scalar dy = this->yOfT.getDerivativeAt(t);
    const Dmath::Scalar dz = this->zOfT.getDerivativeAt(t);

    return Dmath::Vec3D(dx,dy,dz);
}

#pragma endregion


#pragma region Double 
Dmath::Vec3D Dmath::DoubleVectorFunction::operator ()(Dmath::Scalar U, Dmath::Scalar V){
    const Dmath::Scalar currentX = this->xOfUV(U,V);
    const Dmath::Scalar currentY = this->yOfUV(U,V);
    const Dmath::Scalar currentZ = this->zOfUV(U,V);

    return Dmath::Vec3D(currentX,currentY, currentZ);
}

Dmath::Vec3D Dmath::DoubleVectorFunction::operator ()(Dmath::Vec2D vec){
    Dmath::Scalar U = vec.getX();
    Dmath::Scalar V = vec.getY();
    const Dmath::Scalar currentX = this->xOfUV(U,V);
    const Dmath::Scalar currentY = this->yOfUV(U,V);
    const Dmath::Scalar currentZ = this->zOfUV(U,V);

    return Dmath::Vec3D(currentX,currentY,currentZ);

}


Dmath::DoubleVectorFunction::DoubleVectorFunction(const Dmath::DoubleVarFunction& xOfUV, const Dmath::DoubleVarFunction& yOfUV, const Dmath::DoubleVarFunction& zOfUV)
      :xOfUV(xOfUV), yOfUV(yOfUV), zOfUV(zOfUV) {}
      
Dmath::DoubleVectorFunction Dmath::DoubleVectorFunction::operator+(Dmath::DoubleVectorFunction funcTwo){
    Dmath::DoubleVarFunction thisX = this->getXFunc();
    Dmath::DoubleVarFunction thisY = this->getYFunc();
    Dmath::DoubleVarFunction thisZ = this->getZFunc();

    Dmath::DoubleVarFunction funcX = funcTwo.getXFunc();
    Dmath::DoubleVarFunction funcY = funcTwo.getYFunc();
    Dmath::DoubleVarFunction funcZ = funcTwo.getZFunc();

    //Calculation of the components of the scalarproduct
    Dmath::DoubleVarFunction sumX = thisX + funcX;
    Dmath::DoubleVarFunction sumY = thisY + funcY;   
    Dmath::DoubleVarFunction sumZ = thisZ + funcZ;

    //Return a new function
    return DoubleVectorFunction(sumX, sumY, sumZ);
}


Dmath::DoubleVectorFunction Dmath::DoubleVectorFunction::crossPruduct(Dmath::DoubleVectorFunction funcTwo){
    //Copy the functions to avoid bugs caused by missing refrences

    Dmath::DoubleVarFunction thisX = this->getXFunc();
    Dmath::DoubleVarFunction thisY = this->getYFunc();
    Dmath::DoubleVarFunction thisZ = this->getZFunc();

    Dmath::DoubleVarFunction funcX = funcTwo.getXFunc();
    Dmath::DoubleVarFunction funcY = funcTwo.getYFunc();
    Dmath::DoubleVarFunction funcZ = funcTwo.getZFunc();

    //Calculation of the components of the scalarproduct
    Dmath::DoubleVarFunction crossX = thisY * funcZ - thisZ * funcY;
    Dmath::DoubleVarFunction crossY = thisZ * funcX - thisX * funcZ;
    Dmath::DoubleVarFunction crossZ = thisX * funcY - thisY * funcX;

    //Return a new function
    return DoubleVectorFunction(crossX, crossY, crossZ);
}

Dmath::DoubleVarFunction Dmath::DoubleVectorFunction::operator*( DoubleVectorFunction other) {
    // Scalar product operator

    // Kopien der Einzelkomponenten (X, Y, Z)
     auto thisX = this->getXFunc();
     auto thisY = this->getYFunc();
     auto thisZ = this->getZFunc();

     auto otherX = other.getXFunc();
     auto otherY = other.getYFunc();
     auto otherZ = other.getZFunc();

    // Lambda für das Skalarprodukt erstellen
    auto scalarProductLambda = [thisX, thisY, thisZ, otherX, otherY, otherZ](double x, double y) -> double {
        double valX = thisX(x, y) * otherX(x, y);
        double valY = thisY(x, y) * otherY(x, y);
        double valZ = thisZ(x, y) * otherZ(x, y);
        return valX + valY + valZ;
    };

    // Neues DoubleVarFunction-Objekt aus dem Lambda erzeugen
    return Dmath::DoubleVarFunction(scalarProductLambda);
}


Dmath::Vec3D Dmath::DoubleVectorFunction::getPartialUAt(Dmath::Scalar u, Dmath::Scalar v){
    const Dmath::Scalar du_x = (this->xOfUV(u + 0.0001, v) - this->xOfUV(u - 0.0001, v)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUV(u + 0.0001, v) - this->yOfUV(u - 0.0001, v)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUV(u + 0.0001, v) - this->zOfUV(u - 0.0001, v)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x,du_y,du_z);
}


Dmath::Vec3D Dmath::DoubleVectorFunction::getPartialVAt(Dmath::Scalar u, Dmath::Scalar v){
    const Dmath::Scalar du_x = (this->xOfUV(u, v + 0.0001) - this->xOfUV(u, v - 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUV(u, v + 0.0001) - this->yOfUV(u, v - 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUV(u, v + 0.0001) - this->zOfUV(u, v - 0.0001)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x,du_y,du_z);
}

Dmath::Vec3D Dmath::DoubleVectorFunction::normVectorAt(Dmath::Scalar u, Dmath::Scalar v){
    Dmath::Vec3D du = this->getPartialUAt(u,v);
    Dmath::Vec3D dv = this->getPartialVAt(u,v);

    Dmath::Vec3D normVec = du.vecProduct(dv);

    return normVec;
}

Dmath::DoubleVectorFunction Dmath::DoubleVectorFunction::partialU(){
    
    Dmath::DoubleVarFunction ddx = this->getXFunc().getPartialX();
    Dmath::DoubleVarFunction ddy = this->getYFunc().getPartialX();
    Dmath::DoubleVarFunction ddz = this->getZFunc().getPartialX();

    return DoubleVectorFunction(ddx,ddy,ddz);
}


Dmath::DoubleVectorFunction Dmath::DoubleVectorFunction::partialV(){
    Dmath::DoubleVarFunction ddx = this->getXFunc().getPartialY();
    Dmath::DoubleVarFunction ddy = this->getYFunc().getPartialY();
    Dmath::DoubleVarFunction ddz = this->getZFunc().getPartialY();

    return DoubleVectorFunction(ddx,ddy,ddz);
}

#pragma endregion

#pragma region Triple

Dmath::TripleVectorFunction::TripleVectorFunction(Dmath::TripleVarFunction xOfUVW, Dmath::TripleVarFunction yOfUVW, Dmath::TripleVarFunction zOfUVW){
    this->xOfUVW = xOfUVW;
    this->yOfUVW = yOfUVW;
    this->zOfUVW = zOfUVW;
}

Dmath::Vec3D Dmath::TripleVectorFunction::operator()(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar currentX = this->xOfUVW(u,v,w);
    const Dmath::Scalar currentY = this->yOfUVW(u,v,w);
    const Dmath::Scalar currentz = this->zOfUVW(u,v,w);

    return Dmath::Vec3D(currentX, currentY, currentz);
}


Dmath::Vec3D Dmath::TripleVectorFunction::getPartialUAt(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar du_x = (this->xOfUVW(u + 0.0001, v, w) - this->xOfUVW(u - 0.0001, v, w)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUVW(u + 0.0001, v, w) - this->yOfUVW(u - 0.0001, v, w)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUVW(u + 0.0001, v, w) - this->zOfUVW(u - 0.0001, v, w)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x, du_y,du_z);
}

Dmath::Vec3D Dmath::TripleVectorFunction::getPartialVAt(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar du_x = (this->xOfUVW(u, v + 0.0001, w) - this->xOfUVW(u, v - 0.0001, w)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUVW(u, v + 0.0001, w) - this->yOfUVW(u, v - 0.0001, w)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUVW(u, v + 0.0001, w) - this->zOfUVW(u, v - 0.0001, w)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x, du_y,du_z);
}

Dmath::Vec3D Dmath::TripleVectorFunction::getPartialWAt(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar du_x = (this->xOfUVW(u, v, w + 0.0001) - this->xOfUVW(u, v, w - 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_y = (this->yOfUVW(u, v, w + 0.0001) - this->yOfUVW(u, v, w + 0.0001)) / (2 * 0.0001);
    const Dmath::Scalar du_z = (this->zOfUVW(u, v, w + 0.0001) - this->zOfUVW(u, v, w + 0.0001)) / (2 * 0.0001);

    return Dmath::Vec3D(du_x, du_y,du_z);
}

Dmath::Scalar Dmath::TripleVectorFunction::callX(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    return this->xOfUVW(u,v,w);
}

Dmath::Scalar Dmath::TripleVectorFunction::callY(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    return this->yOfUVW(u,v,w);
}

Dmath::Scalar Dmath::TripleVectorFunction::callZ(Dmath::Scalar u,Dmath::Scalar v, Dmath::Scalar w){
    return this->zOfUVW(u,v,w);
}

Dmath::Scalar Dmath::TripleVectorFunction::callXPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar dx = this->callX(u + 0.0001, v, w) - this->callX(u - 0.0001, v, w) / (2 * 0.0001);
    return dx;
}


Dmath::Scalar Dmath::TripleVectorFunction::callYPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar dx = this->callX(u + 0.0001, v, w) - this->callX(u - 0.0001, v, w) / (2 * 0.0001);
    return dx;
}


Dmath::Scalar Dmath::TripleVectorFunction::callZPartial(Dmath::Scalar u, Dmath::Scalar v, Dmath::Scalar w){
    const Dmath::Scalar dx = this->callZ(u + 0.0001, v, w) - this->callZ(u - 0.0001, v, w) / (2 * 0.0001);
    return dx;
}
#pragma endregion