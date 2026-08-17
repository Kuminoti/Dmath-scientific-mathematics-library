#include"../include/Vector/mathVector.hpp"
#include "../include/Vector/systemGeometry.hpp"


using namespace Dmath;
// Helper functions:

// Calculate cosine of the angle between two vectors
double cosAngle(double dotProduct, double absProduct) {
  double result = 0;
  if (absProduct == 0) {
#ifdef WORKING
    std::cerr << "Vector abs is Zero" << std::endl;
#endif //Working
    result = 0;
  } else {
    result = dotProduct / absProduct;
  }
  return result;
}

double angleFromCos(double cosTheta) {
  double result = 0;
  if (cosTheta > 1 || cosTheta < -1) {
#ifdef WORKING
    std::cerr << "Error: cos(theta) wrong value" << std::endl;
#endif
    result = 0;
  } else {

#ifdef STANDARD_ANGLE_UNIT_DEG
    result = std::acos(cosTheta) * 180 / PI;
#endif

#ifdef STANDARD_ANGLE_UNIT_RAD
    result = std::acos(cosTheta);
#endif
  }
  return result;
}


//Operator overloading

#pragma region 2D-OPERATORS


//Division by a scalar divides all components of the vector by a given Value
Vec2D Vec2D::operator/( const Dmath::Scalar scalarValue){ 
  if(scalarValue == 0){
    // Division by 0 is undefined
    return Dmath::Vec2D::zeroVector();
  }
  double valueX = this->X / scalarValue;
  double valueY = this->Y / scalarValue;
  return Vec2D(valueX, valueY);
}


//Basic vector addition
Vec2D Vec2D::operator+(const Vec2D &Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;

  return Vec2D(resultX, resultY);
}


//Basic vector subtraction
Vec2D Vec2D::operator-(const Vec2D &Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;

  return Vec2D(resultX, resultY);
}


Vec2D Vec2D::operator*(const Dmath::Scalar scalarValue){
  Vec2D newVec(this->X * scalarValue, this->Y *scalarValue);
  return newVec;
}


//Multiplikation of two vectos via the operator will return the dotproduct of the vectors
Dmath::Scalar Vec2D::operator*(const Vec2D &Mathvector) {
  return this->dotProduct(Mathvector);
}

Dmath::Vec2D Vec2D::operator*( Dmath::Matrix<Dmath::Scalar> matrix) {

    // Check if matrix is 2x2
    if(matrix.isSquared() == false || matrix.getElementsRow() != 2 || matrix.getElementsColumn() != 2) {
        std::cerr << "Error: Vec2D * Matrix requires a 2x2 matrix. Error code: " << Dmath::ERROR_CODE::UNDEFINED <<std::endl;
        return *this; // return unchanged vector
    }

    Dmath::Scalar x = this->getX();
    Dmath::Scalar y = this->getY();

    // Matrix elements:
    // [ a b ]  [x] = [ax + by]
    // [ c d ]  [y]   [cx + dy]
    Dmath::Scalar a = matrix.getElement(1,1);
    Dmath::Scalar b = matrix.getElement(1,2);
    Dmath::Scalar c = matrix.getElement(2,1);
    Dmath::Scalar d = matrix.getElement(2,2);

    Dmath::Scalar newX = x * a + y * b;
    Dmath::Scalar newY = x * c + y * d;

    return Dmath::Vec2D(newX, newY);
}

//Adds one to every component
void Vec2D::operator++(){
  this->X += 1;
  this->Y += 1;
  this->ValidManipulation();
}

//subtracts one to every component
void Vec2D::operator--(){
  this->X -= 1;
  this->Y -= 1;
  this->ValidManipulation();
}

void Vec2D::operator=(Dmath::sVec2f vec){
  this->X = vec.X;
  this->Y = vec.Y;
  this->ValidManipulation();

}

void Vec2D::operator=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> duo){
  this->X = duo.one;
  this->Y = duo.two;
  this->ValidManipulation();
}

/* Mathmatical operations with Dmath::Duo's:
 * The first element of the duo (.one) is used to calculate 
 * the new X value of the vector.
 * 
 * The second element is used to calculate the new Y of the vector 
 */


void Vec2D::operator+=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data){
  this->X += data.one;
  this->Y += data.two;
  this->ValidManipulation();
}


void Vec2D::operator-=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data){
  this->X -= data.one;
  this->Y -= data.two;
  this->ValidManipulation();
}

void Vec2D::operator*=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data){
  this->X *= data.one;
  this->Y *= data.two;
  this->ValidManipulation();
}

void Vec2D::operator/=(Dmath::Duo<Dmath::Scalar, Dmath::Scalar> data){
	if(data.one == 0 || data.two == 0){
		std::cerr << "Error Division by Zero! Error-code: " << Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl;
		return;
	}
  this->X /= data.one;
  this->Y /= data.two;
  this->ValidManipulation();
}



//almost the same as the Duo example
void Vec2D::operator+=(Dmath::sVec2f vec){
  this->X += vec.X;
  this->Y += vec.Y;
  this->ValidManipulation();
}

void Vec2D::operator-=(Dmath::sVec2f vec){
  this->X -= vec.X;
  this->Y -= vec.Y;
  this->ValidManipulation();
}

void Vec2D::operator*=(Dmath::sVec2f vec){
  this->X *= vec.X;
  this->Y *= vec.Y;
  this->ValidManipulation();
}


//Be carefull not to divide by 0
void Vec2D::operator/=(Dmath::sVec2f vec){
  if(vec.X == 0  || vec.Y == 0){
    std::cerr << "error division by zero " << __FILE__ << __LINE__ <<std::endl;
    return;
  }
  this->X /= vec.X;
  this->Y /= vec.Y;
  this->ValidManipulation();
}

void Vec2D::operator+=(Vec2D vec){
  this->X += vec.X;
  this->Y += vec.Y;
  this->ValidManipulation();
}

void Vec2D::operator-=(Vec2D vec){
  this->X -= vec.X;
  this->Y -= vec.Y;
  this->ValidManipulation();
}

void Vec2D::operator*=(Vec2D vec){
  this->X *= vec.X;
  this->Y *= vec.Y;
  this->ValidManipulation();
}

void Vec2D::operator/=(Vec2D vec){
	if(vec.getX()==0 || vec.getY()==0){
		std::cerr <<"Error division By Zero!" << Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl;
		return;
	}
  this->X /= vec.X;
  this->Y /= vec.Y;
  this->ValidManipulation();
}




void Vec2D::operator+=(Dmath::Scalar scalar){
  this->X += scalar;
  this->Y += scalar;
  this->ValidManipulation();
}

void Vec2D::operator-=(Dmath::Scalar scalar){
  this->X -= scalar;
  this->Y -= scalar;
  this->ValidManipulation();
}

void Vec2D::operator*=(Dmath::Scalar scalar){
  this->X *= scalar;
  this->Y *= scalar;
  this->ValidManipulation();
}

void Vec2D::operator/=(Dmath::Scalar scalar){
	if(scalar == 0){
		std::cerr << "Error division By zero!"<< Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl;
		return;
	}
  this->X /= scalar;
  this->Y /= scalar;
  this->ValidManipulation();
}

bool Vec2D::operator==(Vec2D& Mathvector) {
  return (this->getX() == Mathvector.getX()) && (this->getY() == Mathvector.getY());
}

bool Vec2D::operator!=(Vec2D& Mathvector){
  if(this->getX() != Mathvector.getX() || this->getY() != Mathvector.getY()){
    return true;
  }
  return false;
}


bool Vec2D::operator>=(Vec2D& Mathvector){
  if(this->getAbs() >= Mathvector.getAbs()){
    return true;
  }
  return false;
}

bool Vec2D::operator<=(Vec2D& Mathvector){
  if(this->getAbs() <= Mathvector.getAbs()){
    return true;
  }
  return false;
}

bool Vec2D::operator<(Vec2D& Mathvector){
  if(this->getAbs() < Mathvector.getAbs() ){
    return true;
  }
  return false;
}

bool Vec2D::operator>(Vec2D& Mathvector){
  if(this->getAbs() > Mathvector.getAbs() ){
    return true;
  }
  return false;
}

#pragma endregion



#pragma region Vec2D



Dmath::Scalar Vec2D::distance(Vec2D Mathvector){
  //Calculates the euclidian distace with the Pythagorean theorem
  double dx = std::abs(Mathvector.aX - this->aX);
  double dy = std::abs(Mathvector.aY - this->aY);
  double result =  std::sqrt(dx * dx + dy * dy);
  return result;
}

Dmath::Scalar Vec2D::calcAngle(Vec2D Mathvector) {
  double product = this->dotProduct(Mathvector);
  double absProduct = this->getAbs() * Mathvector.getAbs();
  double cosTheta = cosAngle(product, absProduct);
  return angleFromCos(cosTheta);
}



Dmath::Scalar Vec2D::polarSystemArea() {
  double Area = PI * (this->radius * this->radius);
  return Area;
}

Dmath::Scalar Vec2D::polarSystemCircumfrance() {
  double Area = TWOPI * this->radius;
  return Area;
}

void Vec2D::setX(Dmath::Scalar value) {
  this->X = value;
  this->cartesianToPolar();
  this->calcAbs();
}

void Vec2D::setY(Dmath::Scalar value) {
  this->Y = value;
  this->cartesianToPolar();
  this->calcAbs();
}

void Vec2D::setPhi(Dmath::Scalar value) {
  this->phi = value;
  this->polarToCartesian();
  this->calcAbs();
}

void Vec2D::setAll(Dmath::Scalar value){
  this->X = value;
  this->Y = value;
  this->calcAbs();
  this->cartesianToPolar();
}

void Vec2D::setRadius(Dmath::Scalar value) {
  this->radius = value;
  this->polarToCartesian();
  this->calcAbs();
}

void Vec2D::addToThis(Dmath::Scalar add){
  this->X += add;
  this->Y += add;
  this->ValidManipulation();
}

void Vec2D::substractThis(Dmath::Scalar subtract){
  this->X -= subtract;
  this->Y -= subtract; 
  this->ValidManipulation();
  
}

void Dmath::Vec2D::multipyThisBy(Dmath::Scalar factor){
  this->X *= factor;
  this->Y *= factor;
  this->ValidManipulation();
  this->cartesianToPolar();
}

void Dmath::Vec2D::divideThisBy(Dmath::Scalar quotient){
  if(quotient == 0){
    std::cerr << "Error Division By Zero! Idiot" << std::endl;
  }
  this->X /= quotient;
  this->Y /= quotient;
  this->ValidManipulation();
  
}


void Vec2D::addToX(Dmath::Scalar add){
  this->X+=add;
  this->ValidManipulation();

}

void Vec2D::addToY(Dmath::Scalar add){
  this->Y+=add;
  this->ValidManipulation();
}

void Vec2D::subtractFromX(Dmath::Scalar subtract){
  this->X-=subtract;
  this->ValidManipulation();
}

void Vec2D::subtractFromY(Dmath::Scalar subtract){
  this->Y-=subtract;
  this->ValidManipulation();
}

void Vec2D::multiplyXBy(Dmath::Scalar factor){
  this->X *= factor;
  this->ValidManipulation();
}

void Vec2D::multiplyYBy(Dmath::Scalar factor){
  this->Y *= factor;
  this->ValidManipulation();
}

void Vec2D::divideXBy(Dmath::Scalar divBy){
	if(divBy == 0){
		std::cerr << "Error division By Zero" << Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl;
		return;
	}
  this->X /= divBy;
  this->ValidManipulation();
}

void Vec2D::divideYBy(Dmath::Scalar divBy){
	if(divBy == 0){
		std::cerr << "Error division By Zero" << Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl;
		return;
	}
  this->Y /= divBy;
  this->ValidManipulation();
}

void Vec2D::addXYEach(Dmath::Scalar xPlus, Dmath::Scalar yPlus){
  this->X += xPlus;
  this->Y += yPlus;
  this->ValidManipulation();
}

void Vec2D::multilpyXY(Dmath::Scalar xTimes, Dmath::Scalar yTimes){
  this->X *= xTimes;
  this->Y *= yTimes;
  this->ValidManipulation();
}

void Vec2D::subtractXY(Dmath::Scalar xMinus, Dmath::Scalar yMinus){
  this->X -= xMinus;
  this->Y -= yMinus;
  this->ValidManipulation();
}


void Vec2D::divideXYBy(Dmath::Scalar xDiv, Dmath::Scalar yDiv){
  if(xDiv == 0 || yDiv == 0 ){
    std::cerr << "error division by zero" << __FILE__ << __LINE__ <<std::endl;
    return;
  }

  this->X /= xDiv;
  this->Y /= yDiv;
  this->ValidManipulation();
}


bool Dmath::Vec2D::isEqual(Dmath::Vec2D vec){
  bool result = false;
  //Declaring a bunch of constants to make if conditions clearer to read
  const double vecX = vec.getX();
  const double vecY = vec.getY();

  const double vecOx = vec.getOriginX();
  const double vecOy = vec.getOriginY();

  if(this->X == vecX &&  this->getY() == vecY &&
     this->originX == vecOx   &&  this->originY == vecOy){
    result = true;
  }
  return result;
}


void Vec2D::moveVectorX(Dmath::Scalar move){
  this->originX += move;
  this->calcAbsXY();
  this->calcDZ();
}


void Vec2D::linearTransformation(Dmath::Matrix<Dmath::Scalar> matrix){
  // Check if matrix is 2x2
  if(matrix.isSquared() == false || matrix.getElementsRow() != 2 || matrix.getElementsColumn() != 2) {
    std::cerr << "Error: Vec2D * Matrix requires a 2x2 matrix. Error code: " << Dmath::ERROR_CODE::UNDEFINED <<std::endl;
    return; // return 
  }
  // Matrix elements:
  // [ a b ]  [x]  [ax + by]
  // [ c d ]  [y]  [cx + dy]
  Dmath::Scalar a = matrix.getElement(1, 1);
  Dmath::Scalar b = matrix.getElement(1, 2);
  Dmath::Scalar c = matrix.getElement(2, 1);
  Dmath::Scalar d = matrix.getElement(2, 2);

  Dmath::Scalar x = this->X;
  Dmath::Scalar y = this->Y;

  this->X = x * a + y * b;
  this->Y = x * c + y * d;
  this->ValidManipulation();
}

void Vec2D::moveVectorY(Dmath::Scalar move){
  this->originY += move;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::moveVector(Dmath::Scalar moveX, Dmath::Scalar moveY){
  this->originX += moveX;
  this->originY += moveY;
  this->calcAbsXY();
  this->calcDZ();
}

void Vec2D::calcAbs() {
  double result = PYTH(this->X,this->Y);
  this->abs = result;
}


void Vec2D::ValidManipulation( ){
  
  if(this->originX != 0 || this->originY != 0){
    this->calcAbsXY();
    this->calcDZ();
  }
  this->calcAbs();
#ifdef CARTESIAN_IS_2D_STANDARD
  this->cartesianToPolar();
#endif

#ifdef POLAR_IS_STANDARD
  this->polarToCartesian();
#endif
}

void Vec2D::normalize(){
  if(this->abs == 0){
    // Division by zero is undefined
    return;
  }
  this->X = this->X / this->abs;
  this->Y = this->Y / this->abs;
  this->ValidManipulation();
}


Dmath::Scalar Vec2D::wedgeProduct(Vec2D MathVector){
  return (this->X * MathVector.getY() - this->Y * MathVector.getX());

}

Dmath::Scalar Vec2D::dotProduct(Vec2D Mathvector) {
  double result = this->X * Mathvector.X + this->Y * Mathvector.Y;
  return result;
}

Vec2D Vec2D::add(Vec2D Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;
  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::subtract(Vec2D Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;
  return Vec2D(resultX, resultY);
}

Vec2D Vec2D::polarVector(Dmath::Scalar radius, Dmath::Scalar angle) {
  double xValue = radius * std::cos(angle);
  double yValue = radius * std::sin(angle);
  return Vec2D(xValue, yValue);
}

Dmath::Scalar Vec2D::rectangleArea(Vec2D MathVector) {
  double Area = this->getAbs() * MathVector.getAbs();
  return Area;
}

Dmath::Scalar Vec2D::rectangleCircumfrance(Vec2D MathVector) {
  double Circumfrance = 2 * this->getAbs() + 2 * MathVector.getAbs();
  return Circumfrance;
}

double Vec2D::getAbs()               { return this->abs;      }
double Vec2D::getLenght()            { return this->getAbs(); }
double Vec2D::getRotationAngle()     { return this->vectorRotation; }


#pragma endregion //Vec2D/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region Vec3D








  #pragma region Vec3D_Numeric_Operations

void Vec3D::operator+=(Vec3D mathvector){
  this->X += mathvector.getX();
  this->Y += mathvector.getY();
  this->Z += mathvector.getZ();
  this->cartesianToCylinder();
  this->cartesianToSphere();
  this->calcAbs();
}

void Vec3D::operator-=(Vec3D mathvector){
  this->X -= mathvector.getX();
  this->Y -= mathvector.getY();
  this->Z -= mathvector.getZ();
  this->cartesianToCylinder();
  this->cartesianToSphere();
  this->calcAbs();
}

void Vec3D::operator*=(Vec3D mathvector){
  this->X *= mathvector.getX();
  this->Y *= mathvector.getY();
  this->Z *= mathvector.getZ();
  this->cartesianToCylinder();
  this->cartesianToSphere();
  this->calcAbs();
}

void Vec3D::operator/=(Vec3D mathvector){

	if(mathvector.getX() == 0 ||
       mathvector.getY() == 0 ||
	   mathvector.getZ() == 0 )
	{
		std::cerr << "Error division By zero!" << std::endl;
		return;
	}

  this->X /= mathvector.getX();
  this->Y /= mathvector.getY();
  this->Z /= mathvector.getZ();
  this->cartesianToCylinder();
  this->cartesianToSphere();
  this->calcAbs();
}





void Vec3D::operator+=(Dmath::sVec3f vec){
  this->X += vec.X;
  this->Y += vec.Y;
  this->Z += vec.Z;
  this->cartesianToCylinder();
  this->cartesianToSphere();
  this->calcAbs();
}

void Vec3D::operator-=(Dmath::sVec3f vec){
  this->X -= vec.X;
  this->Y -= vec.Y;
  this->Z -= vec.Z;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::operator*=(Dmath::sVec3f vec){
  this->X *= vec.X;
  this->Y *= vec.Y;
  this->Z *= vec.Z;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::operator/=(Dmath::sVec3f vec){
	if(vec.X == 0 || vec.Y == 0 ||  vec.Z == 0 ){
		std::cerr << "Error division By zero!" << std::endl;
		return;
	}
  this->X /= vec.X;
  this->Y /= vec.Y;
  this->Z /= vec.Z;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}




void Vec3D::operator+=(double scalar){
  this->X += scalar;
  this->Y += scalar;
  this->Z += scalar;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::operator-=(double scalar){
  this->X -= scalar;
  this->Y -= scalar;
  this->Z -= scalar;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}
void Vec3D::operator*=(double scalar){
  this->X *= scalar;
  this->Y *= scalar;
  this->Z *= scalar;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}
void Vec3D::operator/=(double scalar){
	if(scalar == 0){
		std::cerr << "Error division by Zero! \nError-code" << Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl; 
		return ;
	}
  this->X /= scalar;
  this->Y /= scalar;
  this->Z /= scalar;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}




void Vec3D::operator+=(Dmath::Trio<double,double,double> trio){
  this->X += trio.one;
  this->Y += trio.two;
  this->Z += trio.three;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::operator-=(Dmath::Trio<double,double,double> trio){
  this->X -= trio.one;
  this->Y -= trio.two;
  this->Z -= trio.three;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}



void Vec3D::operator*=(Dmath::Trio<double,double,double> trio){
  this->X *= trio.one;
  this->Y *= trio.two;
  this->Z *= trio.three;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}



void Vec3D::operator/=(Dmath::Trio<double,double,double> trio){
	if(trio.one == 0 || trio.two == 0 || trio.three == 0){
		std::cerr << "Error division by Zero! \nError-code" << Dmath::ERROR_CODE::DIVISION_BY_ZERO << std::endl; 
		return;
	}
  this->X /= trio.one;
  this->Y /= trio.two;
  this->Z /= trio.three;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

Vec3D Vec3D::add(Vec3D Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;
  double resultZ = this->Z + Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}
 

Vec3D Vec3D::subtract(Vec3D Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;
  double resultZ = this->Z - Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

double Vec3D::operator*(Vec3D &Mathvector) {
  return this->dotProduct(Mathvector);
}

//[a0 ,b0, c0] [x] a0X + b0Y + 
//[a1 ,b1, c1] [y]
//[a2 ,b2, c2] [z]

Dmath::Vec3D Dmath::Vec3D::operator*(Dmath::Matrix<Dmath::Scalar> transformation)
{
    Dmath::Scalar newX =
        transformation.getElement(1,1) * this->X +
        transformation.getElement(1,2) * this->Y +
        transformation.getElement(1,3) * this->Z;

    Dmath::Scalar newY =
        transformation.getElement(2,1) * this->X +
        transformation.getElement(2,2) * this->Y +
        transformation.getElement(2,3) * this->Z;

    Dmath::Scalar newZ =
        transformation.getElement(3,1) * this->X +
        transformation.getElement(3,2) * this->Y +
        transformation.getElement(3,3) * this->Z;

    return Dmath::Vec3D(newX, newY, newZ);
}



void Vec3D::addToX(double add){
  this->X += add;
  this->calcAbs();

}

void Vec3D::addToY(double add){
  this->Y += add;
  this->calcAbs();
}
void Vec3D::addToZ(double add){
  this->Z += add;
  this->calcAbs();
}


void Dmath::Vec3D::addXYZEach(Dmath::Scalar xPlus, Dmath::Scalar yPlus, Dmath::Scalar zPlus){
  this->X += xPlus;
  this->Y += yPlus;
  this->Z += zPlus;
  this->calcAbs();
}

void Dmath::Vec3D::subtractXYZ(Dmath::Scalar xMinus, Dmath::Scalar yMinus, Dmath::Scalar zMinus){
  this->X -= xMinus;
  this->Y -= yMinus;
  this->Z -= zMinus;
  this->calcAbs();
}

void Dmath::Vec3D::multilpyXYZ(Dmath::Scalar xTimes, Dmath::Scalar yTimes, Dmath::Scalar zTimes){
  this->X *= xTimes;
  this->Y *= yTimes;
  this->Z *= zTimes;
  this->calcAbs();
}

void Dmath::Vec3D::divideXYZBy(Dmath::Scalar xDivBy, Dmath::Scalar yDivBy, Dmath::Scalar zDivBy){
  if(xDivBy == 0 || yDivBy == 0 || zDivBy == 0){
    std::cerr << "Error Division by Zero! Error-code: " <<
              Dmath::ERROR_CODE::DIVISION_BY_ZERO 		<< std::endl;
    return;
  }
  this->X /= xDivBy;
  this->Y /= yDivBy;
  this->Z /= zDivBy;
  this->calcAbs();
}


Vec3D Vec3D::operator+(Vec3D &Mathvector) {
  double resultX = this->X + Mathvector.X;
  double resultY = this->Y + Mathvector.Y;
  double resultZ = this->Z + Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

Vec3D Vec3D::operator-(Vec3D &Mathvector) {
  double resultX = this->X - Mathvector.X;
  double resultY = this->Y - Mathvector.Y;
  double resultZ = this->Z - Mathvector.Z;
  return Vec3D(resultX, resultY, resultZ);
}

Vec3D Vec3D::operator/(double scalarValue){
  if(scalarValue == 0){
    // Division by zero is undefined
    return Dmath::Vec3D::zeroVector();
  }
  double newX = this->X / scalarValue;
  double newY = this->Y / scalarValue;
  double newZ = this->Z / scalarValue;
  return Vec3D(newX, newY, newZ);
}

  void Vec3D::operator++(){
  this->X +=1;
  this->Y +=1;
  this->Z +=1;
  this->calcAbs();
}

void Vec3D::operator--(){
  this->X -=1;
  this->Y -=1;
  this->Z -=1;
  this->calcAbs();
}

#pragma endregion // Vec3D_Numeric_Operations





#pragma region 3D_Logic_Operators

bool Dmath::Vec3D::isEqual(Dmath::Vec3D vec) {
  return (this->X == vec.getX() && this->Y == vec.getY() &&
          this->Z == vec.getZ() && this->originX == vec.getOriginX() &&
          this->originY == vec.getOriginY() && this->originZ == vec.getOriginZ());
}

void Vec3D::operator=(Dmath::sVec3f vec){
  this->X = vec.X;
  this->Y = vec.Y;
  this->Z = vec.Z;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}



void Vec3D::operator=(Dmath::Trio<double,double,double> trio){
  this->X = trio.one;
  this->Y = trio.two;
  this->Z = trio.three;
  this->calcAbs();
  this->cartesianToSphere();
  this->cartesianToCylinder();
}

void Vec3D::operator=(Dmath::Vec3D vec){
  this->originX = vec.getOriginX();
  this->originY = vec.getOriginY();
  this->originZ = vec.getOriginZ();

  this->X = vec.getX();
  this->Y = vec.getY();
  this->Z = vec.getZ();

  this->calcDTZ();
  this->calcAbs();

  this->cartesianToCylinder();
  this->cartesianToSphere();
}



bool Vec3D::operator==(Vec3D& Mathvector) {
  return (this->getX() == Mathvector.getX()) && (this->getY() == Mathvector.getY()
          && this->getZ() == Mathvector.getZ() );
}

bool Vec3D::operator!=(Vec3D& Mathvector){
  if(this->getX() != Mathvector.getX() || this->getY() != Mathvector.getY() || this->getZ() != Mathvector.getZ()){
    return true;
  }
  return false;
}


bool Vec3D::operator>=(Vec3D& Mathvector){
  if(this->getAbs() >= Mathvector.getAbs()){
    return true;
  }
  return false;
}

bool Vec3D::operator<=(Vec3D& Mathvector){
  if(this->getAbs() <= Mathvector.getAbs()){
    return true;
  }
  return false;
}

bool Vec3D::operator<(Vec3D& Mathvector){
  if(this->getAbs() < Mathvector.getAbs() ){
    return true;
  }
  return false;
}

bool Vec3D::operator>(Vec3D& Mathvector){
  if(this->getAbs() > Mathvector.getAbs() ){
    return true;
  }
  return false;
}

#pragma endregion //3D_Logic_Operators




double Vec3D::dotProduct(Vec3D Mathvector) {
  double result =
      this->X * Mathvector.X + this->Y * Mathvector.Y + this->Z * Mathvector.Z;
  return result;
}


Vec3D Vec3D::vecProduct(Vec3D Mathvector) {
  double resultX = this->Y * Mathvector.Z - this->Z * Mathvector.Y;
  double resultY = this->Z * Mathvector.X - this->X * Mathvector.Z;
  double resultZ = this->X * Mathvector.Y - this->Y * Mathvector.X;
  return Vec3D(resultX, resultY, resultZ);
}







Vec3D Vec3D::sphereVector(double radius, double angleOne, double angleTwo) {
  double Xvalue = radius * std::sin(angleTwo) * std::cos(angleOne);
  double Yvalue = radius * std::sin(angleTwo) * std::sin(angleOne);
  double Zvalue = radius * std::cos(angleTwo);
  return Vec3D(Xvalue, Yvalue, Zvalue);
}

Vec3D Vec3D::cylinderVector(double radius, double angle, double height) {
  double Xvalue = radius * std::cos(angle);
  double Yvalue = radius * std::sin(angle);
  double Zvalue = height;
  return Vec3D(Xvalue, Yvalue, Zvalue);
}


Vec3D Vec3D::zeroVector() { 
  return Vec3D(0); 
  }


double Vec3D::getCylinderRadius(){
    double  result = PYTH(this->X, this->Y);
    return result;
}

double Vec3D::getSphereRadius(){
    double  result = PYTH3(this->X,this->Y,this->Z);
    return result;
}


  #pragma region 3DVector_Movement


void Vec3D::moveVectorZ(double moveZ){
  this->originZ += moveZ;
  this->calcAXYZ();
  this->calcDTZ();
}

void Vec3D::moveVectorY(double moveY){
  this->originY += moveY;
  this->calcAXYZ();
  this->calcDTZ();
}

void Vec3D::moveVectorX(double moveX){
  this->originX += moveX;
  this->calcAXYZ();
  this->calcDTZ();
}

void Dmath::Vec3D::moveVector(double moveX, double moveY, double moveZ){
  this->originX += moveX;
  this->originY += moveY;
  this->originZ += moveZ;

  this->calcAXYZ();
  this->calcDTZ();
}

#pragma endregion //3DVector_Movement


  #pragma region Geometric_Operations

  void Vec3D::calcAbs() {
  double result = PYTH3(this->X,this->Y,this->Z);
  this->abs = result;
}

double Vec3D::calcAngle(Vec3D Mathvector) {
  double product = this->dotProduct(Mathvector);
  double absProduct = this->getAbs() * Mathvector.getAbs();
  double cosTheta = cosAngle(product, absProduct);
  return angleFromCos(cosTheta);
}

void Vec3D::normalize(){
  if(this->abs == 0){
    // Division by zero is undefined
    return;
  }
  this->X = this->X/this->abs;
  this->Y = this->Y/this->abs;
  this->Z = this->Z/this->abs;
}


void Vec2D::rotateThisVector(Dmath::Scalar value){
  Dmath::Scalar xX = this->getX();
  Dmath::Scalar yY = this->getY();
  this->X = xX * std::cos(value) - yY * std::sin(value);
  this->Y = xX * std::sin(value) + yY * std::cos(value);
  this->vectorRotation = value;
}

Dmath::Vec3D Vec3D::rotateVector(double Phi, double Theta) {
    double r = this->radius;
    double theta = this->theta;
    double phi = this->phi;

    double newTheta = theta + Theta;
    double newPhi = phi + Phi;

    double newX = (r * std::sin(newTheta) * std::cos(newPhi));
    double newY = (r * std::sin(newTheta) * std::sin(newPhi));
    double newZ = (r * std::cos(newTheta))* RAD_TO_DEG;

    return Dmath::Vec3D(newX, newY, newZ);
}






void Vec3D::rotateThisVector(double Phi, double Theta){
    double r = this->radius;
    double theta = this->theta;
    double phi = this->phi;

    double newTheta = theta + Theta;
    double newPhi = phi + Phi;

    this->X = (r * std::sin(newTheta) * std::cos(newPhi));
    this->Y = (r * std::sin(newTheta) * std::sin(newPhi));
    this->Z = r * std::cos(newTheta);
}

 



Vec2D Vec2D::rotateVector(Dmath::Scalar angle) {
  double newX = this->getX() * std::cos(angle) - this->getY() * std::sin(angle);
  double newY = this->getX() * std::sin(angle) + this->getY() * std::cos(angle);
  newX = newX * RAD_TO_DEG;
  newY = newY * RAD_TO_DEG;
  return Vec2D(newX, newY);
}



  #pragma endregion //Geometric_Operations


  #pragma region Vec3D_Setter

void Vec3D::setX(double X){
  this->X = X;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}


void Vec3D::setY(double Y){
  this->Y = Y; 
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();

}

void Vec3D::setZ(double Z){
  this->Z = Z;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::setHeight(double height){
  this->height = height; 
  this->cylinderToCartesian();
  this->cylinderToSphere();
}

void Vec3D::setPhi(double phi){
  this->phi = phi; 
  this->sphereToCatesian();
  this->sphereToCylinder();
}



void Vec3D::setTheta(double theta)   { 
  this->theta = theta;
  this->sphereToCatesian();
  this->sphereToCylinder();

}




void Vec3D::setAllCatesian(Dmath::Scalar value){
  this->X = value;
  this->Y = value;
  this->Z = value;
  this->calcAbs();
  this->cartesianToCylinder();
  this->cartesianToSphere();
}

void Vec3D::setAllSphere(Dmath::Scalar value){
  this->radius = value;
  this->phi    = value;
  this->theta  = value;

  this->calcAbs();
  this->sphereToCatesian();
  this->sphereToCylinder();
}

void Vec3D::setAllCylinder(Dmath::Scalar value){
  this->radius = value;
  this->phi    = value;
  this->height = value;

  this->calcAbs();
  this->cylinderToCartesian();
  this->cylinderToSphere();
}



  
#pragma endregion













// Vec3D Vec3D::linearTranformation(Dmath::Matrix<double> mainMatrix){
//   Dmath::Vec3D newVec = mainMatrix.vectorProduct2D(this);
//   return newVec;
// }

// void Vec3D::transformLinear(Dmath::Matrix<double> mainMatrix){
  

//   Dmath::Vec3D currentVec = mainMatrix.vectorProduct3D(this);
//   this->X = currentVec.getX();
//   this->Y = currentVec.getY();
//   this->Z = currentVec.getZ();
// }


#pragma endregion // Vec3D


#pragma region Macro_code:

//Macro dependent code:

#ifdef SYSTEM_READY

#ifdef POLAR_IS_STANDARD
Vec2D::Vec2D(double radius, double phi) : CoordinateSystem2D(radius, phi) {
  this->calcAbs();
  this->polarToCartesian();
  this->aX = this->X;
  this->aY = this->Y;
}

#endif

#ifdef SPHERE_IS_STANDARD
Vec3D::Vec3D(double radius, double phi, double theta)
    : CoordinateSystem3D(radius, phi, theta) {

  this->calcAbs();
  this->sphereToCatesian();
  this->sphereToCylinder();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif

#ifdef CYLINDER_IS_STANDARD
Vec3D::Vec3D(double radius, double phi, double height)
    : CoordinateSystem3D(radius, phi, height) {

  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif



#ifdef CARTESIAN_IS_3D_STANDARD



Vec3D::Vec3D(double XYZ) : CoordinateSystem3D(XYZ) {
  
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();  
  this->aX = 0;
  this->aY = 0;
  this->aZ = 0;
}

Vec3D::Vec3D(double X, double Y, double Z, double originX, double originY, double originZ)
    : CoordinateSystem3D(X, Y, Z, originX, originY, originZ) {
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();
  this->calcAXYZ();
  this->calcDTZ();
}

Vec3D::Vec3D(double X, double Y, double Z) : CoordinateSystem3D(X, Y, Z) {
  this->cartesianToSphere();
  this->cartesianToCylinder();
  this->calcAbs();
  this->aX = this->X;
  this->aY = this->Y;
  this->aZ = this->Z;
}
#endif

#ifdef CARTESIAN_IS_2D_STANDARD

Vec2D::Vec2D(Dmath::Scalar XY) : CoordinateSystem2D(XY){
  this->aX = XY;
  this->aY = XY;
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D::Vec2D(Dmath::Scalar X, Dmath::Scalar Y) : CoordinateSystem2D(X, Y) {
  this->aX = X;
  this->aY = Y;
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D::Vec2D(Dmath::Scalar X, Dmath::Scalar Y, Dmath::Scalar originX, Dmath::Scalar originY) 
    : CoordinateSystem2D(X, Y, originX, originY) {
  this->calcAbsXY();
  this->calcDZ();
  this->calcAbs();
  this->cartesianToPolar();
}

Vec2D Vec2D::zeroVector() { return Vec2D(0, 0); }

#endif






std::ostream& Dmath::operator<<(std::ostream& os, Dmath::Vec3D num){
  std::string baseString = "X: " + std::to_string(num.getX()) + " Y: " + std::to_string(num.getY()) + " Z: " + std::to_string(num.getZ());
  if(num.getOriginX() != 0 || num.getOriginY() != 0 ||  num.getOriginZ() != 0){
    baseString += " Origin-X: " + std::to_string(num.getOriginX()) + " Origin-Y: " + std::to_string(num.getOriginY()) + " Origin-Z: " + std::to_string(num.getOriginZ());
  }
  os << baseString + "\n";

  return os;
}

std::ostream& Dmath::operator<<(std::ostream& os, Dmath::Vec2D num){
  std::string baseString = "X: " + std::to_string(num.getX()) + " Y: " + std::to_string(num.getY());
  if(num.getOriginX() != 0 || num.getOriginY() != 0){
    baseString += " Origin-X: " + std::to_string(num.getOriginX()) + " Origin-Y: " + std::to_string(num.getOriginY());
  }
  os << baseString + "\n";

  return os;
}
#endif

#pragma endregion