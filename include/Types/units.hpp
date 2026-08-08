#pragma once
#ifndef DMATH_UNITS_HPP
#define DMATH_UNITS_HPP

// This header file is part of the Dmath library.
// It is used to calculate units and conversions between them.

#include "../Utils/dataTypes.hpp"
#include <stdexcept>
#include<ostream>
#include"../Vector/mathVector.hpp"

NAMESPACESTART

enum class UnitType {
    LENGTH = 1001,
    MASS = 1002,
    TIME = 1003,
    ELECTRIC_CURRENT = 1004,
    THERMODYNAMIC_TEMPERATURE = 1005,
    LUMINOUS_INTENSITY = 1006,
    AMOUNT_OF_SUBSTANCE = 1007,
};

// Jeder physikalische Wert ist als Produkt von SI-Basiseinheiten mit bestimmten Exponenten darstellbar.
struct SI_Units {
    int length = 0;                    // Länge in Metern
    int mass = 0;                      // Masse in Kilogramm
    int time = 0;                      // Zeit in Sekunden
    int electricCurrent = 0;           // Elektrische Stromstärke in Ampere
    int thermodynamicTemperature = 0; // Temperatur in Kelvin
    int luminousIntensity = 0;         // Lichtstärke in Candela
    int amountOfSubstance = 0;         // Stoffmenge in Mol

    SI_Units(int l = 0, int m = 0, int t = 0, int e = 0, int th = 0, int luminous = 0, int amount = 0)
        : length(l), mass(m), time(t), electricCurrent(e), thermodynamicTemperature(th), luminousIntensity(luminous), amountOfSubstance(amount) {}

    bool operator==(const SI_Units& other) const {
        return length == other.length &&
               mass == other.mass &&
               time == other.time &&
               electricCurrent == other.electricCurrent &&
               thermodynamicTemperature == other.thermodynamicTemperature &&
               luminousIntensity == other.luminousIntensity &&
               amountOfSubstance == other.amountOfSubstance;
    }
    bool operator!=(const SI_Units& other) const {
    return !(*this == other);
}
};


#pragma region PhysicalUnit

class PhysicalUnit {
private:
    SI_Units siUnits;       // SI-Units
    Dmath::Scalar factor;   // factor

    Dmath::Vec3D vectorFactor;
    bool isVector = false;

public:

    PhysicalUnit() = default;

    //Vektor units like velocity 
    PhysicalUnit(SI_Units units, Dmath::Vec3D vec) : siUnits(units), vectorFactor(vec) { this->isVector = true; }

    //Scalar Units like Tempature
    PhysicalUnit(SI_Units units, Dmath::Scalar faktor) : siUnits(units), factor(faktor) {}


    PhysicalUnit(Dmath::Scalar faktor, int length = 0, int mass = 0, int time = 0,
                 int electricCurrent = 0, int thermodynamicTemperature = 0,
                 int luminousIntensity = 0, int amountOfSubstance = 0)
                : PhysicalUnit(SI_Units(length, mass, time, electricCurrent, thermodynamicTemperature, luminousIntensity, amountOfSubstance), faktor) {}

    // Operator Overloading
    PhysicalUnit operator+( PhysicalUnit& other) ;

    PhysicalUnit operator-( PhysicalUnit& other) ;

    PhysicalUnit operator*( PhysicalUnit& other) ;

    PhysicalUnit operator/( PhysicalUnit& other) ;


    



    // Vergleichsoperatoren
    bool operator==( PhysicalUnit& other)  { return (this->siUnits == other.siUnits && this->factor == other.factor); }

    bool operator!=( PhysicalUnit& other)  {  return !(*this == other); }

    // operators 
    bool operator<( PhysicalUnit& other) ;

    bool operator<=( PhysicalUnit& other)  { return (*this < other || *this == other); }

    bool operator>( PhysicalUnit& other)   {  return !(*this <= other);}

    bool operator>=( PhysicalUnit& other)  {  return !(*this < other);}


    // Getter und Setter
    void setSIUnits( SI_Units& units) { this->siUnits = units; }
    void setFactor(Dmath::Scalar faktor)   { this->factor = faktor; }
    void setVector(Dmath::Vec3D vecFaktor) { this->vectorFactor = vecFaktor; }


    //Setters to set individual SI units
    void setMeter(int length)  { this->siUnits.length = length; }

    void setKilogram(int mass) { this->siUnits.mass = mass;     }

    void setSecond(int time)   { this->siUnits.time = time;     }



    void setAmpere(int electricCurrent) { this->siUnits.electricCurrent = electricCurrent; }

    void setKelvin(int thermodynamicTemperature) { this->siUnits.thermodynamicTemperature = thermodynamicTemperature; }

    void setCandela(int luminousIntensity) { this->siUnits.luminousIntensity = luminousIntensity; }

    void setMole(int amountOfSubstance) { this->siUnits.amountOfSubstance = amountOfSubstance; }


    const SI_Units& getSIUnits()   { return this->siUnits; }
    
    Dmath::Scalar getFactor();
    Dmath::Vec3D  getVector();


    private: //private methods
    //This method changes a scalar unit into a scala or the other way around
    void changeFaktorType();







    public: //Public static methods
    static PhysicalUnit GetNewtons(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(1, 1, -2, 0, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetJoules(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -2, 0, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetWatts(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -3, 0, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetVolts(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -3, -1, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetOhms(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -3, -2, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetCoulombs(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(1, 0, -1, 1, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetFarads(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(-2, -1, 4, 2, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetHenrys(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -2, -2, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetTeslas(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(1, 1, -2, -1, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetWebers(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -2, -1, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetLumens(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(0, 0, 0, 0, 0, 1, 0), faktor);
    }

    static PhysicalUnit GetLux(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(-2, 0, 0, 0, 0, 1, 0), faktor);
    }

    static PhysicalUnit GetBecquerels(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(0, 0, -1, 0, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetSieverts(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -2, -1, 0, 0, 0), faktor);
    }

    static PhysicalUnit GetGrays(Dmath::Scalar faktor) {
        return PhysicalUnit(SI_Units(2, 1, -2, 0, 0, 0, 0), faktor);
    }
};

inline std::ostream& operator<<(std::ostream& os, const SI_Units& units) {
    os << "m^" << units.length << " "
       << "kg^" << units.mass << " "
       << "s^" << units.time << " "
       << "A^" << units.electricCurrent << " "
       << "K^" << units.thermodynamicTemperature << " "
       << "cd^" << units.luminousIntensity << " "
       << "mol^" << units.amountOfSubstance;
    return os;
}


inline std::ostream& operator<<(std::ostream& os,  PhysicalUnit& unit) {
    os << unit.getSIUnits() << " (Faktor: " << unit.getFactor() << ")";
    return os;
}

#pragma endregion 

NAMESPACEEND

#endif // DMATH_UNITS_HPP