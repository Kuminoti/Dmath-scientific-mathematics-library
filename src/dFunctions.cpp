#include"../include/dFunctions.hpp"





double Dmath::pyth2(double a, double b){
    double result = 0;
    result = std::sqrt( a*a + b*b);
    return result;
}

double Dmath::pyth3(double x, double y, double z){
        double result = 0;
        result = std::sqrt( x*x + y*y + z*z);
        return result;
    }

double Dmath::derivativeAt(Dmath::singleVarFunction func, double point){
    const Scalar limit = 0.00001;
    Scalar value = func(point + limit) - func(point) / limit;
    return value;

}


double Dmath::roundTo(double value, int digits) {
  double factor = std::pow(10.0, digits);
  return std::round(value * factor) / factor;
}

std::vector<Dmath::Scalar> Dmath::derivativeVector(Dmath::singleVarFunction func, double start, double end, double res){
    const Dmath::Parameters param(start,end,res);

    if(!Dmath::checkParams(param)){
        return std::vector<double>(0);
    }
    const size_t num = Dmath::numberOfElements(param);
    const Dmath::Scalar limit = 0.00000001;
    std::vector<Dmath::Scalar> mainVector;

    for(size_t i = 0; i < num; i++ ){
        Dmath::Scalar currentVar = start + i * res;
        Dmath::Scalar plsDX = func(currentVar + limit);
        Dmath::Scalar minDX = func(currentVar - limit);
        Dmath::Scalar result = (plsDX - minDX) / (2*limit);
        mainVector.push_back(result);
    }

    return mainVector;
}


double Dmath::SigmaAdd(size_t start, size_t end){
    double result = 0;
    bool valid = Dmath::greaterThan(end,start);
    if(!valid){
        return 0;

    }
    for(size_t i = start; i < end; i++){
        result +=i; 
    }
    return result;
}



double Dmath::sigmaAddFunc(size_t start, size_t end, Dmath::singleVarFunction mainFunc){
    double result = 0;
    
    if(!greaterThan(end,start)){
        return 0;
    }

    for(size_t i = start; i < end; i++){
        result += mainFunc(i); 
    }
    return result;
}

size_t Dmath::numberOfElements(Dmath::Parameters params){
    size_t num = static_cast<size_t>((params.two - params.one)/params.three);
    return num;
}

bool Dmath::checkParams(Dmath::Parameters params){
    if(params.one >= params.two || params.three <= 0){
        return false;
    }

    //Faulty data will be fully catched in the if block, so no need for an else 
    return true;
}


double Dmath::kelvinToCelsius(double Kelvin){
    double result = 0;
    if(Kelvin < 0){
        result = Kelvin + ZERO_KELVINC; // + 273.17
    }
    return result;
}

double Dmath::CelsiusToKelvin(double celsius){
    double result = 0;
    if(celsius > ZERO_KELVINK){
        result = celsius + ZERO_KELVINK;
    }
    return result;
}


double Dmath::celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

double Dmath::fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}



double Dmath::radiansToDegrees(double radians) {
    return radians * (180.0 / PI);
}

double Dmath::degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}


double Dmath::fDotProduct(Dmath::sVec2f vecOne, Dmath::sVec2f vecTwo){
    double result = vecOne.X * vecTwo.X + vecOne.Y * vecTwo.Y;
    return result;
}

size_t Dmath::iDotProduct(Dmath::sVec2i vecOne, Dmath::sVec2i vecTwo){
    size_t result = vecOne.X * vecTwo.X + vecOne.Y * vecTwo.Y;
    return result;
}


double Dmath::fDotProduct(Dmath::sVec3f vecOne, Dmath::sVec3f vecTwo){
    double result = vecOne.X * vecTwo.X + vecOne.Y * vecTwo.Y + vecOne.Z * vecTwo.Z;
    return result;
}




size_t Dmath::binomialCoefficient(size_t n, size_t k) {
    if (k > n) return 0; 
    
    size_t nFaktor = 1;
    for (size_t i = 1; i <= n; i++) {
        nFaktor *= i;
    }

    size_t kFaktor = 1;
    for (size_t i = 1; i <= k; i++) {
        kFaktor *= i;
    }

    size_t nkFakt = 1;
    for (size_t i = 1; i <= (n - k); i++) {
        nkFakt *= i;
    }

    size_t result = nFaktor / (kFaktor * nkFakt);
    return result;
}




// Numerical computation of the Gamma function
double Dmath::gammaFunction(double x) {
    if (x <= 0 && std::floor(x) == x) {
        // Gamma function is not defined for non-positive integers
        return 0;
    }

    if (x > 0 && std::floor(x) == x) {
        // For positive integers: Gamma(n) = (n-1)!
        double result = 1.0;
        for (int i = 1; i < static_cast<int>(x); ++i) {
            result *= i;
        }
        return result;
    }

    // Numerical integration using the trapezoidal rule
    const double epsilon = 1e-7; // Accuracy
    const double step = 1e-3;    // Step size for the integral
    const double limit = 100.0;  // Upper limit of the integral (large enough)

    double sum = 0.0;
    for (double t = step; t < limit; t += step) {
        // Evaluate the function at the left and right edges of the interval
        double f1 = std::pow(t, x - 1) * std::exp(-t);          // Left edge
        double f2 = std::pow(t + step, x - 1) * std::exp(-(t + step)); // Right edge

        // Add the area of the trapezoid to the sum
        sum += 0.5 * (f1 + f2) * step;
    }

    return sum;
}

double Dmath::average(std::vector<double> input){
    double result = 0;

    const size_t num = input.size();
    for(size_t i = 0; i < num; i++){
        result += input[i];
    }
    result = result/num;
    return result;
}


double Dmath::lorenzFactor(double v){
    if(v >= CAUSALITY){
        return 0;
    }
    return (1/std::sqrt( (v/CAUSALITY) * (v/CAUSALITY) ) );
}




int Dmath::digitSum(int number) {
    // Take the absolute value to handle negative numbers
    number = std::abs(number);
    int sum = 0;

    // Calculate the sum of the digits
    while (number > 0) {
        sum += number % 10; // Add the last digit to the sum
        number /= 10;       // Remove the last digit
    }

    return sum;
}


size_t Dmath::randomNumber(size_t min, size_t max) {
    if (min > max) {
        throw std::invalid_argument("min cannot be greater than max");
    }
    
    // Zufallszahlengenerator initialisieren (mit Zufalls-Seed)
    std::random_device rd;                         // Hardware-Seed
    std::mt19937 gen(rd());                        // Mersenne-Twister-Generator
    std::uniform_int_distribution<size_t> dist(min, max); // Gleichverteilte Zahlen im Bereich [min, max]

    return dist(gen); // Zufallswert zurückgeben
}

// Numerical approximation of the Psi (Digamma) function
double Dmath::psiFunction(double x) {
    if (x <= 0 && std::floor(x) == x) {
        // The Psi function is not defined for non-positive integers
        return 0;
    }

    // Constants for numerical approximation
    const double epsilon = 1e-7;   // Precision
    const double large = 1e6;     // Threshold for series approximation
    const double eulerMascheroni = 0.5772156649015328606; // Euler-Mascheroni constant

    double result = 0.0;

    if (x < large) {
        // Use recurrence relation: psi(x) = psi(x + 1) - 1/x
        while (x < large) {
            result -= 1 / x;
            x += 1;
        }
    }

    // Use asymptotic expansion for large x
    double invX = 1 / x;
    result += std::log(x) - 0.5 * invX;
    double term = invX * invX;
    result -= term * (1.0 / 12.0 - term * (1.0 / 120.0 - term * (1.0 / 252.0)));

    return result;
}


double Dmath::psiToBar(double psi) {
    return psi / BAR_TO_PSI;
}



 double Dmath::milesToKm(double miles) {
    return miles * MILES_TO_KM;
}

 double Dmath::kmToMiles(double km) {
    return km / MILES_TO_KM;
}

// Pfund <-> Kilogramm
 double Dmath::poundsToKg(double pounds) {
    return pounds * POUNDS_TO_KG;
}

 double Dmath::kgToPounds(double kg) {
    return kg / POUNDS_TO_KG;
}

// Bar <-> PSI
 double Dmath::barToPsi(double bar) {
    return bar * BAR_TO_PSI;
}






std::string Dmath::getCurrentDate()
{
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t time = system_clock::to_time_t(now);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << tm.tm_mday << "."
        << std::setw(2) << (tm.tm_mon + 1) << "."
        << (tm.tm_year + 1900);

    return oss.str();
}