#include "../include/systems.hpp"
#include "../include/macros.hpp"
#ifdef SYSTEM_IS_SET




void CoordinateSystem2D::polarToCartesian() {
    this->X = radius * std::cos(this->phi);
    this->Y = radius * std::sin(this->phi);
}

void CoordinateSystem2D::cartesianToPolar() {
    this->radius = std::sqrt(this->X* this->X + this->Y*this->Y);
    this->phi = std::atan2(this->Y, this->X);
    
}



void CoordinateSystem2D::calcAbsXY() {
    if(this->originX != 0 || this->originY != 0){
        this->aX = this->X + this->originX;
        this->aY = this->Y + this->originY;
    }
}


void CoordinateSystem2D::setOriginX(double move){
  this->originX = move;
  this->calcAbsXY();
  this->calcDZ();
}

void CoordinateSystem2D::setOriginY(double move){
  this->originY = move;
  this->calcAbsXY();
  this->calcDZ();
}

void CoordinateSystem2D::operator++(){
    this->X += 1;
    this->Y += 1;
}


void CoordinateSystem3D::cartesianToSphere() {
    this->radius = PYTH3(this->X, this->Y, this->Z);
    this->phi =  std::atan2(this->Y, this->X);
    this->theta = std::acos((this->Z / radius));
}

void CoordinateSystem3D::cartesianToCylinder() {
    this->radius = PYTH(this->X, this->Y);
    this->phi = std::atan2(this->Y, this->X);
    this->height = this->Z;
}

void CoordinateSystem3D::sphereToCatesian() {
    this->X = this->radius * std::sin(this->theta) * std::cos(this->phi);
    this->Y = this->radius * std::sin(this->theta) * std::sin(this->phi);
    this->Z = this->radius * std::cos(this->theta);
}

void CoordinateSystem3D::sphereToCylinder() {
    Dmath::Scalar oradius = this->radius;
    this->radius = oradius * std::sin(this->theta);
    this->height = oradius * std::cos(this->theta);
}

void CoordinateSystem3D::cylinderToCartesian() {
    this->X = this->radius * std::cos(phi);
    this->Y = this->radius * std::sin(phi);
    this->Z = this->height;
}

void CoordinateSystem3D::cylinderToSphere() {
    this->radius = PYTH(this->radius, this->height);
    // this->phi = this->phi;
    this->theta = std::atan2( this->height,this->radius);
}

void CoordinateSystem3D::setOriginX(double Value){
  this->originX = Value;
  this->calcAXYZ();
  this->calcDTZ();
}

void CoordinateSystem3D::setOriginY(double Value){
  this->originY = Value;
  this->calcAXYZ();
  this->calcDTZ();
}

void CoordinateSystem3D::setOriginZ(double Value){
  this->originZ = Value;
  this->calcAXYZ();
  this->calcDTZ();
}

void CoordinateSystem3D::calcAXYZ(){
    if(this->originX != 0 || this->originY != 0 || this->originZ != 0){
        this->aX = this->originX + this->X;
        this->aY = this->originY + this->Y; 
        this->aZ = this->originZ + this->Z;
    }
}

void CoordinateSystem3D::calcDTZ(){
 if(this->originX == 0 && this->originY == 0 && this->originZ == 0){
    this->distanceToZero = 0;
    return;
  }
  double result = 0;
  this->calcAXYZ();
  //AYS absolute Y sqared ...
  double AXS = this->aX * this->aX;
  double AYS = this->aY * this->aY;
  double AZS = this->aZ * this->aZ;
  result = std::sqrt(AXS + AYS + AZS);
  this->distanceToZero = result;  
}

void CoordinateSystem2D::calcDZ(){
    float result = 0;
    if(this->originX != 0 || this->originY != 0){
        result = PYTH(this->aX,this->aY);
    }
    else { result = 0;}
  this->distanceToZero = result;
}

#ifdef CARTESIAN_IS_2D_STANDARD

CoordinateSystem2D::CoordinateSystem2D(Dmath::sVec2i vec){
    this->X = static_cast<double>(vec.X);
    this->Y = static_cast<double>(vec.Y);
    this->originX = 0;
    this->originY = 0;
    this->aX = 0;
    this->aY = 0;
}

CoordinateSystem2D::CoordinateSystem2D(Dmath::sVec2f vec){
    this->X = static_cast<double>(vec.X);
    this->Y = static_cast<double>(vec.Y);
    this->originX = 0;
    this->originY = 0;
    this->aX = 0;
    this->aY = 0;
}

CoordinateSystem2D::CoordinateSystem2D(double XY){
    this->X = XY;
    this->Y = XY;
    this->originX = 0;
    this->originY = 0;
    this->aX = 0;
    this->aY = 0;
    
}

CoordinateSystem2D::CoordinateSystem2D(double x, double y) {
    this->X = x;
    this->Y = y;
    this->t = 0;
    this->originX = 0;
    this->originY = 0;
}

CoordinateSystem2D::CoordinateSystem2D(double x, double y, double t) {
    this->X = x;
    this->Y = y;
    this->t = t;
    this->originX = 0;
    this->originY = 0;

}

CoordinateSystem2D::CoordinateSystem2D(double x, double y, double originX,
                                       double originY) {
    this->X = x;
    this->Y = y;
    this->t = 0;
    this->originX = originX;
    this->originY = originY;
    this->calcAbsXY();
    this->calcDZ();
}

#endif

#ifdef POLAR_IS_STANDARD
CoordinateSystem2D::CoordinateSystem2D(double radius, double phi, double originX,
                                       double originY) {
    this->radius = radius;
    this->phi = phi;
    this->t = 0;
    this->originX = originX;
    this->originY = originY;
    this->calcAbsXY();
    }


CoordinateSystem2D::CoordinateSystem2D(double radius, double phi) {
    this->radius = radius;
    this->phi = phi;
    this->originX = 0;
    this->originY = 0;
}
#endif

#ifdef CARTESIAN_IS_3D_STANDARD

CoordinateSystem3D::CoordinateSystem3D(Dmath::sVec3f vec){
    this->X = static_cast<double>(vec.X);
    this->Y = static_cast<double>(vec.Y);
    this->Z = static_cast<double>(vec.Z);
    this->aX = 0;
    this->aY = 0;
    this->aZ = 0;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}



CoordinateSystem3D::CoordinateSystem3D(Dmath::sVec3i vec){
    this->X = static_cast<double>(vec.X);
    this->Y = static_cast<double>(vec.Y);
    this->Z = static_cast<double>(vec.Z);
    this->aX = 0;
    this->aY = 0;
    this->aZ = 0;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(double XYZ) : CoordinateSystem2D(XYZ)  {
    this->X = XYZ;
    this->Y = XYZ;
    this->Z = XYZ;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(double X, double Y, double Z)
    : CoordinateSystem2D(X, Y) {
    this->Z = Z;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}

CoordinateSystem3D::CoordinateSystem3D(double X, double Y, double Z, double originX, double originY, double originZ)
    : CoordinateSystem2D(X, Y, originX, originY) {
    this->Z = Z;
    this->originZ = originZ;
}
#endif

#ifdef SPHERE_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double theta)
    : CoordinateSystem2D(radius, phi) {
    this->theta = theta;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double theta,
                                       double originX, double originY,double originZ)
    : CoordinateSystem2D(radius, phi, originX, originY) {
    this->theta = theta;
    this->originZ = originZ;
}
#endif

#ifdef CYLINDER_IS_STANDARD
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double height)
    : CoordinateSystem2D(radius, phi) {
    this->height = height;
    this->originX = 0;
    this->originY = 0;
    this->originZ = 0;
}
CoordinateSystem3D::CoordinateSystem3D(double radius, double phi, double height,
                                       double originX, double originY, double originZ)
    : CoordinateSystem2D(radius, phi, originX, originY) {
    this->height = height;
    this->originZ = originZ;
}
#endif



#endif




double CoordinateSystem3D::getRadiusSphere() {
    return PYTH3(this->X, this->Y, this->Z);
}
double CoordinateSystem3D::getRadiusCylinder() {
    return PYTH(this->X, this->Y);
}