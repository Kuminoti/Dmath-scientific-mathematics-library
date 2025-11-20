#include"../include/mathFunction.hpp"


#pragma region SingleVar

bool Dmath::SingleVarFunction::checkParams(Dmath::Parameters params){

        if(params.one >= params.two || params.three == 0){
            return 0;
        }

    return true;
}



Dmath::SingleVarFunction&  Dmath::SingleVarFunction::operator=(SingleVarFunction& other) {
    if (this != &other) {
        this->funcBase = other.funcBase ? other.funcBase->clone() : nullptr;
    }
    return *this;
}

Dmath::SingleVarFunction& Dmath::SingleVarFunction::operator=(SingleVarFunction&& other) noexcept {
    if (this != &other) {
        this->funcBase = std::move(other.funcBase);
    }
    return *this;
}


size_t Dmath::SingleVarFunction::numOfElements(Dmath::Parameters param){


    double result = 0;

    result = static_cast<size_t>((param.two - param.one)/param.three);
    
    return result;
}


Dmath::SingleVarFunction  Dmath::SingleVarFunction::operator+ ( Function funcOne){
    Dmath::SingleVarFunction lhs = *this;
    Dmath::Function rhs = funcOne;

    auto addFunc = [lhs, rhs](double x) mutable -> double {
        return lhs(x) + rhs();
    };


    Dmath::SingleVarFunction func(addFunc);
    return func;
}



Dmath::SingleVarFunction  Dmath::SingleVarFunction::operator- ( Function funcOne){
    Dmath::SingleVarFunction lhs = *this;
    Dmath::Function rhs = funcOne;

    auto difFunc = [lhs, rhs](double x) mutable -> double {
        return lhs(x) - rhs();
    };


    Dmath::SingleVarFunction func(difFunc);
    return func;
}



Dmath::SingleVarFunction  Dmath::SingleVarFunction::operator* ( Function funcOne){
    Dmath::SingleVarFunction lhs = *this;
    Dmath::Function rhs = funcOne;

    auto mulFunc = [lhs, rhs](double x) mutable -> double {
        return lhs(x) * rhs();
    };


    Dmath::SingleVarFunction func(mulFunc);
    return func;
}

Dmath::SingleVarFunction  Dmath::SingleVarFunction::operator/ ( Function funcOne){
    Dmath::SingleVarFunction lhs = *this;
    Dmath::Function rhs = funcOne;

    if(funcOne() == 0){
        throw std::runtime_error("Error: Division by zero in multiplication with function.");
    }

    auto divFunc = [lhs, rhs](double x) mutable -> double {
        return lhs(x) / rhs();
    };


    Dmath::SingleVarFunction func(divFunc);
    return func;
}

//For function compsition f(g(x))


Dmath::SingleVarFunction Dmath::SingleVarFunction::operator+(Dmath::SingleVarFunction funcOne){
    Dmath::SingleVarFunction lhs = *this;
    Dmath::SingleVarFunction rhs = funcOne;

    auto addFunc = [lhs, rhs](double x) mutable -> double {
        return lhs(x) + rhs(x);
    };

    Dmath::SingleVarFunction func(addFunc);
    return func;
}


Dmath::SingleVarFunction Dmath::SingleVarFunction::operator-(Dmath::SingleVarFunction funcOne){
        
    auto sub = [this,funcOne](double x) mutable ->double {
        return ( this->funcBase->Callx(x) - funcOne(x));
    };

    SingleVarFunction func = sub;
    return func;
}


Dmath::SingleVarFunction Dmath::SingleVarFunction::operator*(Dmath::SingleVarFunction funcOne) {
    Dmath::SingleVarFunction lhs = *this;
    Dmath::SingleVarFunction rhs = funcOne;

    auto mul = [lhs, rhs](double x) {
        return lhs(x) * rhs(x);
    };

    return SingleVarFunction(mul);
}



Dmath::SingleVarFunction Dmath::SingleVarFunction::operator/(Dmath::SingleVarFunction funcOne){
        
    auto div = [this,funcOne](double x) mutable ->double {
        return ( this->funcBase->Callx(x) / funcOne(x));
    };

    Dmath::SingleVarFunction func = div;
    return func;
}

Dmath::SingleVarFunction Dmath::SingleVarFunction::composition(Dmath::SingleVarFunction fOfX, Dmath::SingleVarFunction gOfX){

    auto comp = [fOfX, gOfX](double x) mutable ->double {

        double innerResult = gOfX(x);
        double outerResult = fOfX(innerResult);

        return outerResult;
    };

    Dmath::SingleVarFunction func = comp;

    return func;
}

Dmath::SingleVarFunction Dmath::SingleVarFunction::compose(Dmath::SingleVarFunction func){
    auto mainFunc = *this;
     auto comp = [func, mainFunc](double x) mutable ->double {
        return mainFunc(func(x));
    };
    return comp;
}

double Dmath::SingleVarFunction::operator()(double x)  const{
    if (funcBase) {
        return funcBase->Callx(x); // Delegate the call to the stored function
    }
    return 0.0; // Return a default value if no function is stored
}



Dmath::SingleVarFunction Dmath::SingleVarFunction::operator+(Dmath::Scalar num){
    auto add = [this, num](double x) mutable ->double { 
        return (this->funcBase->Callx(x) + num);
    };

    Dmath::SingleVarFunction func = add;
    return func;
}


std::vector<double>  Dmath::SingleVarFunction::getFunctionVector(double start, double stopp, double stepps){
    //Error checking: 

    if(start >= stopp || stepps == 0){
        return std::vector<double>(0);
    }

    Dmath::Parameters params(start,stopp,stepps);
    const size_t num = this->numOfElements(params);
 
    std::vector<double> mainVec;

    for(size_t i = 0; i < num; i++){
        double currentResult = funcBase->Callx((start + i*stepps));
        mainVec.push_back(currentResult);
    }
    return mainVec;
}


std::vector<double> Dmath::SingleVarFunction::getDerivativeVector(double start, double stopp, double stepps){

    //It,s simpler to use a struct in stet of all args inside the class 
    Dmath::Parameters params(start,stopp,stepps);
    
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }

    //Number of elements
    const size_t num = this->numOfElements(params);
    
    std::vector<double> mainVector;

    for(size_t i = 0; i < num; i++){

        double x = start + i * stepps; // Current x value
        double plusDX  = this->funcBase->Callx(x + dx); // f(x + dx)
        double minusDX = this->funcBase->Callx(x - dx); // f(x - dx)
        double result  = (plusDX - minusDX) / (2 * dx); // Central difference method

        mainVector.push_back(result); // Store the result

    }
    return mainVector;
}

std::vector<double> Dmath::SingleVarFunction::getSecondDerivative(double start, double stopp, double stepps){
    const Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = this->numOfElements(params);
    std::vector<double> mainVector;
    for(size_t i = 0; i < num; i++){
        const double x = start + i * stepps;
        const double TwofOfX = 2 * this->funcBase->Callx(x);
        const double plusDX  = this->funcBase->Callx(x+this->dx);
        const double minusDX = this->funcBase->Callx(x-this->dx);

        const double currentResult = (plusDX - TwofOfX + minusDX)/(dx*dx);
        mainVector.push_back(currentResult);

    }
    return mainVector;
}


std::vector<double> Dmath::SingleVarFunction::getAntiDerivativeVector(double start, double stopp, double stepps) {
    Dmath::Parameters param(start, stopp, stepps);
    if (!this->checkParams(param)) {
        return std::vector<double>(0);
    }

    // Number of intervals
    size_t num = this->numOfElements(param);
    std::vector<double> mainVec;
    double integral = this->funcBase->Callx(start);
    mainVec.push_back(integral);
    // Numerical integration over the interval
    for (size_t i = 0; i < num; i++) {
        double currentX = start + i * stepps;
        double nextX = currentX + stepps;

        // Trapezoidal rule: Average of function values at currentX and nextX
        double avgValue = 0.5 * (this->funcBase->Callx(currentX) + this->funcBase->Callx(nextX));
        
        integral += avgValue * stepps;   // Step size * average value
        mainVec.push_back(integral);     // Store the integrated value
    }

    return mainVec;
}

Dmath::Scalar Dmath::SingleVarFunction::getDerivativeAt(Dmath::Scalar x) {
    return ((this->funcBase->Callx(x + 0.000001) - this->funcBase->Callx(x)) / 0.000001);
}


Dmath::Scalar Dmath::SingleVarFunction::getSecondDerivativeAt(Dmath::Scalar x){
    
    const Dmath::Scalar TwofOfX = 2 * this->funcBase->Callx(x);
    const Dmath::Scalar plusDX  = this->funcBase->Callx(x+this->dx);
    const Dmath::Scalar minusDX = this->funcBase->Callx(x-this->dx);

    const Dmath::Scalar currentResult = (plusDX - TwofOfX + minusDX)/(dx*dx);

    return currentResult;
}



Dmath::SingleVarFunction Dmath::SingleVarFunction::getDerivative(){
    return Dmath::SingleVarFunction([=](double x) {
            double plusDX  = funcBase->Callx(x + dx);
            double minusDX = funcBase->Callx(x - dx);
            return (plusDX - minusDX) / (2 * dx);
        });

}

Dmath::SingleVarFunction Dmath::SingleVarFunction::getSecondDerivative(){
    return Dmath::SingleVarFunction([=](double x){
        const Dmath::Scalar TwofOfX = 2 * this->funcBase->Callx(x);
        const Dmath::Scalar plusDX  = this->funcBase->Callx(x+this->dx);
        const Dmath::Scalar minusDX = this->funcBase->Callx(x-this->dx);

        const Dmath::Scalar currentResult = (plusDX - TwofOfX + minusDX)/(dx*dx);
        return currentResult;
    });
}

#pragma endregion 

#pragma region DoubleVar


bool Dmath::DoubleVarFunction::checkParams(Dmath::Parameters params){

    if(params.one >= params.two || params.three == 0){
        return false;
    }
    return true;
}

Dmath::Scalar Dmath::DoubleVarFunction::operator()(Dmath::Scalar x, Dmath::Scalar y) const {
    if (funcBase) {
        return funcBase->CallXY(x, y); // Delegate call to stored function
    }
    return 0.0; // Default value
}


Dmath::Scalar Dmath::DoubleVarFunction::operator()(Dmath::Vec2D vector) const{
    if (funcBase) {
        return funcBase->CallXY(vector.getX(), vector.getY()); // Delegate call to stored function
    }
    return 0.0; // Default value
}


Dmath::DoubleVarFunction& Dmath::DoubleVarFunction::operator=(DoubleVarFunction&& other) noexcept {
    if (this != &other) {
        this->funcBase = std::move(other.funcBase);
    }
    return *this;
}

Dmath::DoubleVarFunction& Dmath::DoubleVarFunction::operator=(const DoubleVarFunction& other) {
    if (this != &other) {
        this->funcBase = other.funcBase ? other.funcBase->clone() : nullptr;
    }
    return *this;
}


Dmath::DoubleVarFunction Dmath::DoubleVarFunction::operator+(Dmath::DoubleVarFunction funcOne){
    auto add = [this,funcOne](double x, double y) mutable ->double {
        return (this->funcBase->CallXY(x,y) + funcOne(x,y));
    };

    Dmath::DoubleVarFunction func = add;
    return func;
}

Dmath::DoubleVarFunction Dmath::DoubleVarFunction::operator-(Dmath::DoubleVarFunction funcOne){
    auto sub = [this,funcOne](double x, double y) mutable ->double {
        return (this->funcBase->CallXY(x,y) - funcOne(x,y));
    };

    Dmath::DoubleVarFunction func = sub;
    return func;
}

Dmath::DoubleVarFunction Dmath::DoubleVarFunction::operator*(DoubleVarFunction funcOne){
    auto mul = [this, fB = std::move(funcOne)](double x, double y) -> double {
        return this->funcBase->CallXY(x, y) * fB(x, y);
    };

    return Dmath::DoubleVarFunction(std::move(mul));
}

Dmath::DoubleVarFunction Dmath::DoubleVarFunction::operator/(Dmath::DoubleVarFunction funcOne){
    auto div = [this,funcOne](double x, double y) mutable ->double {
        return (this->funcBase->CallXY(x,y) / funcOne(x,y));
    };

    Dmath::DoubleVarFunction func = div;
    return func;
}
//(f(g(x),h(x)))
Dmath::DoubleVarFunction Dmath::DoubleVarFunction::composition( Dmath::DoubleVarFunction mainFunc, Dmath::SingleVarFunction funcOne, Dmath::SingleVarFunction funcTwo){

    auto comp = [mainFunc,funcOne,funcTwo](double x, double y) mutable ->double {
        double innerResultX = funcOne(x);
        double innerResultY = funcTwo(y);

        double outerResult = mainFunc(x,y);

        return outerResult;
    };

    return Dmath::DoubleVarFunction(comp);
}


std::vector<double> Dmath::DoubleVarFunction::getFunctionVector(double start, double stopp, double stepps){
    Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
        const size_t num = static_cast<size_t>((stopp-start)/stepps);

        std::vector<double> mainVec;
        for(size_t x = 0; x < num; x++){
            double currentX = (start + x * stepps);
            for(size_t y = 0; y < num; y++){
                double currentY = (start + y * stepps);

                double currentData = this->funcBase->CallXY(currentX,currentY);

                mainVec.push_back(currentData);
            }
        }

        return mainVec;
    }


std::vector<double> Dmath::DoubleVarFunction::getPartialDerivteX(double start, double stopp, double stepps){
    Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = static_cast<size_t>((stopp-start)/stepps);

    std::vector<double> mainVec;

    for(size_t i = 0; i < num; i++){
        double currentX = (start + i * stepps);
        for(size_t j = 0; j < num ; j++){
            double currentY = start+j*stepps;
            double dxPlus   = this->funcBase->CallXY(currentX + dx, currentY);
            double dxMinus  = this->funcBase->CallXY(currentX - dx, currentY);
            double result   = ((dxPlus - dxMinus)/(2*dx));
            mainVec.push_back(result); 
        }
        
    } 
    return mainVec;
}

Dmath::DoubleVarFunction Dmath::DoubleVarFunction::getPartialY() {
        auto basePtr = funcBase.get();
        Dmath::Scalar dy = this->dx; //to make the notation consistent
        return DoubleVarFunction([basePtr,this,dy](double x, double y) {
            double plusDY  = basePtr->CallXY(x, y + dy);
            double minusDY = basePtr->CallXY(x, y - dy);
            return (plusDY - minusDY) / (2 * dy);
        });
    }

Dmath::DoubleVarFunction Dmath::DoubleVarFunction::getPartialX(){

    auto basePtr = funcBase.get();

    return DoubleVarFunction([basePtr,this](double x, double y) {
        double plusDX  = basePtr->CallXY(x + dx, y);
        double minusDX = basePtr->CallXY(x - dx, y);
        return (plusDX - minusDX) / (2 * dx);
        });
    }


std::vector<double> Dmath::DoubleVarFunction::getPartialDerivteY(double start, double stopp, double stepps){
    Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = static_cast<size_t>((stopp-start)/stepps);

    std::vector<double> mainVec;

    for(size_t i = 0; i < num; i++){
        double currentX = (start + i * stepps);
        for(size_t j = 0; j < num ; j++){
            double currentY = start+j*stepps;
            double dxPlus   = this->funcBase->CallXY(currentX, currentY + dx);
            double dxMinus  = this->funcBase->CallXY(currentX, currentY - dx);

            double result   = ((dxPlus - dxMinus)/(2*dx));
            mainVec.push_back(result); 
        }
        
    } 
    return mainVec;
}



std::vector<double> Dmath::DoubleVarFunction::getAntiDerivativeX(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }

    size_t num = this->numOfElements(params);
    std::vector<double> mainVec;
    double integral = this->funcBase->CallXY(start, start);
    mainVec.push_back(integral);

    // Numerical integration over the interval in X direction
    for (size_t i = 0; i < num; i++) {
        double currentX = start + i * stepps;
        double nextX = currentX + stepps;
        
        for (size_t j = 0; j < num; j++) {
            double currentY = start + j * stepps;

            // Trapezoidal rule: Average of function values at currentX and nextX
            double avgValue = 0.5 * (this->funcBase->CallXY(currentX, currentY) + this->funcBase->CallXY(nextX, currentY));
            
            integral += avgValue * stepps;
            mainVec.push_back(integral); // Store the integrated value after each X interval
        }
        
    }
    return mainVec;
}

Dmath::Scalar Dmath::DoubleVarFunction::derivativeXAT(Dmath::Scalar x, Dmath::Scalar y){
    const Dmath::Scalar dx = ((this->funcBase->CallXY(x + 0.0001, y) - this->funcBase->CallXY(x - 0.0001, y)) / (2* 0.0001));
    return dx;
}

Dmath::Scalar Dmath::DoubleVarFunction::derivativeYAT(Dmath::Scalar x, Dmath::Scalar y){
    const Dmath::Scalar dy = ((this->funcBase->CallXY(x, y + 0.0001) - this->funcBase->CallXY(x, y - 0.0001)) / (2* 0.0001));
    return dy;
}

///////////////////////
//Second derivatives://
///////////////////////

Dmath::Scalar Dmath::DoubleVarFunction::secondDerivativeXX(Dmath::Scalar x, Dmath::Scalar y) {
    const Dmath::Scalar h = 0.0001;
    return (this->funcBase->CallXY(x + h, y) - 2 * this->funcBase->CallXY(x, y) + this->funcBase->CallXY(x - h, y)) / (h * h);
}

Dmath::Scalar Dmath::DoubleVarFunction::secondDerivativeYY(Dmath::Scalar x, Dmath::Scalar y) {
    const Dmath::Scalar h = 0.0001;
    return (this->funcBase->CallXY(x, y + h) - 2 * this->funcBase->CallXY(x, y) + this->funcBase->CallXY(x, y - h)) / (h * h);
}


Dmath::Scalar Dmath::DoubleVarFunction::secondDerivativeXY(Dmath::Scalar x, Dmath::Scalar y) {
    const Dmath::Scalar h = 0.0001;
    return ( this->funcBase->CallXY(x + h, y + h) - this->funcBase->CallXY(x + h, y - h) - this->funcBase->CallXY(x - h, y + h) + this->funcBase->CallXY(x - h, y - h)    ) / (4 * h * h);
}

//d/dx d/dy = d/dy d/dx
Dmath::Scalar Dmath::DoubleVarFunction::secondDerivativeYX(Dmath::Scalar x, Dmath::Scalar y){
    return this->secondDerivativeXY(x,y);
}


std::vector<double> Dmath::DoubleVarFunction::getAntiDerivativeY(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }

    size_t num = this->numOfElements(params);
    std::vector<double> mainVec;
    double integral = this->funcBase->CallXY(start, start);
    mainVec.push_back(integral);

    // Numerical integration over the interval in Y direction
    for (size_t i = 0; i < num; i++) {
        double currentX = start + i * stepps;
        
        for (size_t j = 0; j < num; j++) {
            double currentY = start + j * stepps;
            double nextY = currentY + stepps;

            // Trapezoidal rule: Average of function values at currentY and nextY
            double avgValue = 0.5 * (this->funcBase->CallXY(currentX, currentY) + this->funcBase->CallXY(currentX, nextY));
            
            integral += avgValue * stepps;
            mainVec.push_back(integral); // Store the integrated value after each Y interval

        }
    }
    return mainVec;
}



size_t Dmath::DoubleVarFunction::numOfElements(Dmath::Parameters params){
    if( !this->checkParams(params)){
        return 0;
    }
    size_t num = static_cast<size_t>((params.two - params.one)/params.three);
    return num;
}

#pragma endregion



#pragma region TrippleVar

Dmath::Scalar Dmath::TripleVarFunction::operator()(double x, double y, double z) {
    if (funcBase) {
        return funcBase->CallXYZ(x, y, z); // Delegate call to stored function
    }
    return 0.0; // Default value
}

Dmath::Scalar Dmath::TripleVarFunction::operator()(Dmath::Vec3D vector){
    if (funcBase) {
        return funcBase->CallXYZ(vector.getX(), vector.getY(), vector.getZ()); // Delegate call to stored function
    }
    return 0.0; // Default value
}

Dmath::TripleVarFunction Dmath::TripleVarFunction::operator+(Dmath::TripleVarFunction funcOne){
    Dmath::TripleVarFunction lhs = *this;
    Dmath::TripleVarFunction rhs = funcOne;

    auto addFunc = [lhs, rhs](double x, double y, double z) mutable -> double {
        return lhs(x,y,z) + rhs(x,y,z);
    };

    Dmath::TripleVarFunction func(addFunc);
    return func;
}

Dmath::TripleVarFunction Dmath::TripleVarFunction::operator-(Dmath::TripleVarFunction funcOne){
    Dmath::TripleVarFunction lhs = *this;
    Dmath::TripleVarFunction rhs = funcOne;

    auto subFunc = [lhs, rhs](double x, double y, double z) mutable -> double {
        return lhs(x,y,z) - rhs(x,y,z);
    };

    Dmath::TripleVarFunction func(subFunc);
    return func;
}

Dmath::TripleVarFunction Dmath::TripleVarFunction::operator*(Dmath::TripleVarFunction funcOne){
    Dmath::TripleVarFunction lhs = *this;
    Dmath::TripleVarFunction rhs = funcOne;

    auto multFunc = [lhs, rhs](double x, double y, double z) mutable -> double {
        return lhs(x,y,z) * rhs(x,y,z);
    };

    Dmath::TripleVarFunction func(multFunc);
    return func;
}

Dmath::TripleVarFunction Dmath::TripleVarFunction::operator/(Dmath::TripleVarFunction funcOne){
    Dmath::TripleVarFunction lhs = *this;
    Dmath::TripleVarFunction rhs = funcOne;

    auto divFunc = [lhs, rhs](double x, double y, double z) mutable -> double {
        return lhs(x,y,z) / rhs(x,y,z);
    };

    Dmath::TripleVarFunction func(divFunc);
    return func;
}

Dmath::TripleVarFunction& Dmath::TripleVarFunction::operator=(const TripleVarFunction& other) {
    if (this != &other) {
        this->funcBase = other.funcBase ? other.funcBase->clone() : nullptr;
    }
    return *this;
}


Dmath::TripleVarFunction& Dmath::TripleVarFunction::operator=(TripleVarFunction&& other) noexcept {
    if (this != &other) {
        this->funcBase = std::move(other.funcBase);
    }
    return *this;
}



bool Dmath::TripleVarFunction::checkParams(Dmath::Parameters params){
    if(params.one >= params.two || params.three == 0 ){
        return false;
    }
    return true;
}


size_t Dmath::TripleVarFunction::numberOfElements(Dmath::Parameters params){
    if(!this->checkParams(params)){ return 0; }

    size_t num = static_cast<size_t>((params.two - params.one)/params.three);
    return num;
}


std::vector<double> Dmath::TripleVarFunction::getFunctionVector(double start, double stopp, double stepps){
    Dmath::Parameters params(start,stopp,stepps);
    if(!this->checkParams(params)){
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;

    for(size_t x = 0; x < num; x++){
        double currentX = start + x * stepps;

        for(size_t y = 0; y < num; y++){
            double currentY = start + y * stepps;

            for(size_t z = 0; z < num; z++){
                double currentZ = start + z * stepps;

                double currentResult = this->funcBase->CallXYZ(currentX,currentY,currentZ);

                funcVector.push_back(currentResult);
            }
        }
    }
    return funcVector;
}



std::vector<double> Dmath::TripleVarFunction::getPartialDerivteX(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;
    funcVector.reserve(num * num * num);

    for (size_t x = 0; x < num; x++) {
        double currentX = (start + x * stepps);

        for (size_t y = 0; y < num; y++) {
            double currentY = (start + y * stepps);

            for (size_t z = 0; z < num; z++) {
                double currentZ = (start + z * stepps);  // Korrigiert auf z

                double xDX = this->funcBase->CallXYZ(currentX + this->dx, currentY, currentZ);
                double Xdx = this->funcBase->CallXYZ(currentX - this->dx, currentY, currentZ);

                double result = (xDX - Xdx) / (2 * this->dx);  // Klammern hinzugefügt
                funcVector.push_back(result);
            }
        }
    }

    return funcVector;
}


std::vector<double> Dmath::TripleVarFunction::getPartialDerivteY(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;
    funcVector.reserve(num * num * num);

    for (size_t x = 0; x < num; x++) {
        double currentX = (start + x * stepps);

        for (size_t y = 0; y < num; y++) {
            double currentY = (start + y * stepps);

            for (size_t z = 0; z < num; z++) {
                double currentZ = (start + z * stepps); // Z bleibt unverändert

                double yDY = this->funcBase->CallXYZ(currentX, currentY + this->dx, currentZ);
                double Ydy = this->funcBase->CallXYZ(currentX, currentY - this->dx, currentZ);

                double result = (yDY - Ydy) / (2 * this->dx); // Berechnung der Ableitung in Y-Richtung
                funcVector.push_back(result);
            }
        }
    }

    return funcVector;
}


std::vector<double> Dmath::TripleVarFunction::getPartialDerivteZ(double start, double stopp, double stepps) {
    Dmath::Parameters params(start, stopp, stepps);
    if (!this->checkParams(params)) {
        return std::vector<double>(0);
    }
    const size_t num = this->numberOfElements(params);

    std::vector<double> funcVector;
    funcVector.reserve(num * num * num);

    for (size_t x = 0; x < num; x++) {
        double currentX = (start + x * stepps);

        for (size_t y = 0; y < num; y++) {
            double currentY = (start + y * stepps);

            for (size_t z = 0; z < num; z++) {
                double currentZ = (start + z * stepps);  // Korrigiert auf z

                double zDZ = this->funcBase->CallXYZ(currentX, currentY, currentZ + this->dx);
                double Zdz = this->funcBase->CallXYZ(currentX, currentY, currentZ - this->dx);

                double result = (zDZ - Zdz) / (2 * this->dx);  // Klammern hinzugefügt
                funcVector.push_back(result);
            }
        }
    }

    return funcVector;
}


Dmath::Scalar Dmath::TripleVarFunction::derivativeXAt(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z){
    const Dmath::Scalar dx = this->funcBase->CallXYZ(x + 0.0001, y, z);
    const Dmath::Scalar DX = this->funcBase->CallXYZ(x - 0.0001, y, z);

    const Dmath::Scalar derivative = ((dx - DX) / (2 * 0.0001));

    return derivative;
}

Dmath::Scalar Dmath::TripleVarFunction::derivativeYAt(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z){
    const Dmath::Scalar dy = this->funcBase->CallXYZ(x, y + 0.0001, z);
    const Dmath::Scalar DY = this->funcBase->CallXYZ(x, y - 0.0001, z);

    const Dmath::Scalar derivative = ((dy - DY) / (2 * 0.0001));

    return derivative;
}

Dmath::Scalar Dmath::TripleVarFunction::derivativeZAt(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar z){
    const Dmath::Scalar dz = this->funcBase->CallXYZ(x, y, z + 0.0001);
    const Dmath::Scalar DZ = this->funcBase->CallXYZ(x, y, z - 0.0001);

    const Dmath::Scalar derivative = ((dz - DZ) / (2 * 0.0001));

    return derivative;
}

#pragma endregion