#include"../include/Vector/systemGeometry.hpp"


double Dmath::SystemGeometry::sphereSystemVolume(Dmath::Vec3D mainVector) {
  // formula: 4/3 π * r³
  double fourThreePi = (4 / 3) * PI;
  double radiusCubed = (mainVector.getRadius() * mainVector.getRadius() * mainVector.getRadius());
  double result = fourThreePi * radiusCubed;
  return result;
}

double Dmath::SystemGeometry::sphereSystemSurface(Dmath::Vec3D mainVector) {
  // formula: 4π * radius²
  double result = FOUR_PI * mainVector.getRadius() * mainVector.getRadius();
  return result;
}

double Dmath::SystemGeometry::cylinderSystemVolume(Dmath::Vec3D mathVector) {
  // formula B * h
  double baseSide = PI * (mathVector.getRadius() * mathVector.getRadius());
  return baseSide * mathVector.getHeight();
}

double Dmath::SystemGeometry::cylinderSystemSurface(Dmath::Vec3D mainVector) {
  // formula: Baseside * LateralSurface
  double baseSide = PI * (mainVector.getRadius() * mainVector.getRadius());
  double LateralSurface = mainVector.systemGeometry->cylinderSystemLateralSurface(mainVector);
  return 2 * baseSide * LateralSurface;
}

double Dmath::SystemGeometry::cylinderSystemLateralSurface(Dmath::Vec3D mainVector) {
  // formula: 2π * r * h
  double result = TWOPI * mainVector.getRadius() * mainVector.getHeight();
  return result;
}


double Dmath::SystemGeometry::cuboidVolume(Dmath::Vec3D mainVector, Dmath::Vec3D MathVector,Dmath::Vec3D MathVectorTwo) {
  // formula: A*B*C or in this case: |vector1| * |vector2| * |vector3|
  ;

  double A = mainVector.getAbs();
  double B = MathVector.getAbs();
  double C = MathVectorTwo.getAbs();

  double result = A * B * C;
  
  return result;
}

double Dmath::SystemGeometry::cuboidSurface(Dmath::Vec3D mainVector, Dmath::Vec3D MathVector, Dmath::Vec3D MathVectorTwo) {
  double productOne = mainVector.dotProduct(MathVector);
  double productTwo = mainVector.dotProduct(MathVectorTwo);
  double productThree = MathVector.dotProduct(MathVectorTwo);
  double result = 2 * (productOne + productTwo + productThree);
  return result;
}