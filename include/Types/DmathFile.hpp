#pragma once
#ifndef DMATH_EXPERIMENTAL_OPEN_HPP
#define DMATH_EXPERIMENTAL_OPEN_HPP

#include "../Dmath.hpp"
#include <fstream>
#include <type_traits>

NAMESPACESTART

#define FILE_VERSION "INPROGRESS"

// ============================================================================
// DATA TYPES
// ============================================================================
enum Data_Type_File {
    NATURAL_NUMBER,
    SCALAR_NUMBER,
    SINGLE_FUNC,
    VEC_2D,
    VEC_3D,
    SET,
    STRING_D,
    MATRIX,
    UNKNOWEN_INPUT
};

template<typename T>
struct FileElement {
    Data_Type_File type;
    T data;
};

inline void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch){ return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch){ return !std::isspace(ch); }).base(), s.end());
}

Dmath::Trio<std::string, std::string, std::string>
functionData(const std::string& FunctionString);
// ============================================================================
// CLASS
// ============================================================================
class DmathFile {

private:
    std::string content;
    bool isDmathFile = true;

    Dmath::StringHelper strH;

public:
    // ------------------------------------------------------------------------
    // Constructor
    // ------------------------------------------------------------------------
    DmathFile();


public: //BinaryOperations
    void writeDmathBinary(const std::string& path);
    std::string readDmathBinary(const std::string& path);

    DmathFile loadBinary  (const std::string &path);
    DmathFile loadTextFile(const std::string &path);

public: //adders


    void addFunction(std::string FunctionString);

    // ------------------------------------------------------------------------
    // Output
    // ------------------------------------------------------------------------
    std::string getContent() const;

    void saveToFile(const std::string& path) const;


     std::vector<std::string> extractFunctions() {
        std::vector<std::string> functions;
        std::istringstream stream(this->content);
        std::string line;

    while (std::getline(stream, line)) {
        // Entferne führende Leerzeichen
        Dmath::trim(line);

        if (line.rfind("Function:", 0) == 0) {
            try {
                functions.push_back(getFunctionString(line));
            }
            catch (...) {
                // Ungültige Funktionszeile → ignorieren oder loggen
            }
        }
    }

    return functions;
}




private: //private getters and setters
    // ------------------------------------------------------------------------
    // Template structure (UNCHANGED)
    // ------------------------------------------------------------------------
    std::string getDmathTemplate() const;

    // ------------------------------------------------------------------------
    // Insert text inside <{ }>
    // ------------------------------------------------------------------------
    void insertIntoBlock(const std::string& text);


    // ------------------------------------------------------------------------
    // Private content setter
    // ------------------------------------------------------------------------
    void setContent(const std::string &newContent){ this->content = newContent; }



   

    std::string getFunctionString (std::string functionName);

public: //Template functions
    // ------------------------------------------------------------------------
    // Convert data to text (FORMAT UNCHANGED)
    // ------------------------------------------------------------------------
    template<typename T>
    std::string getData(Data_Type_File type, const T& element, const std::string& name) {

        if constexpr (std::is_arithmetic_v<T>) {

            if (type == SCALAR_NUMBER)
                return "Scalar: " + name + "<" + std::to_string(element) + ">";

            if (type == NATURAL_NUMBER)
                return "Natural: " + name + "<" + std::to_string(element) + ">";
        }

        else if constexpr (std::is_same_v<T, Dmath::Vec2D>) {

            if (type == VEC_2D)
                return "Vec2D: " + name + "[" +
                    std::to_string(element.getX()) + "," +
                    std::to_string(element.getY()) + "]";
        }

        else if constexpr (std::is_same_v<T, Dmath::Vec3D>) {

            if (type == VEC_3D)
                return "Vec3D: " + name + "[" +
                    std::to_string(element.getX()) + "," +
                    std::to_string(element.getY()) + "," +
                    std::to_string(element.getZ()) + "]";
        }

        else if constexpr (std::is_same_v<T, std::string>) {

        if (type == STRING_D)
            return "String: " + name + "<\"" + element + "\">";

        if (type == SINGLE_FUNC)
            return "Function: " + name + "<" + element + ">";
    }

        else {
            static_assert(!sizeof(T), "Unsupported type for DmathFile");
        }

        throw std::invalid_argument(
            "Type mismatch between Data_Type_File and template argument for '" + name + "'"
        );
    }

    // ------------------------------------------------------------------------
    // Add element to <{ ... }>
    // ------------------------------------------------------------------------
    template<typename T>
    void addElement(const std::string& name, const FileElement<T>& element) {

        if (element.type == UNKNOWEN_INPUT)
            throw std::invalid_argument("Invalid Dmath file element");

        std::string entry = getData(element.type, element.data, name) + ";\n";

        insertIntoBlock(entry);
    }

};

NAMESPACEEND
#endif




// Dmath::Trio<std::string, std::string, std::string>
// functionData(const std::string& FunctionString)
// {
//     std::string funcName;
//     std::string usedVar;
//     std::string term;

//     // remove spaces
//     std::string s;
//     for (char c : FunctionString)
//         if (!std::isspace(static_cast<unsigned char>(c)))
//             s += c;

//     // split at '='
//     size_t equalPos = s.find('=');
//     if (equalPos == std::string::npos)
//         throw std::invalid_argument("Function must contain '='");

//     funcName = s.substr(0, equalPos);
//     term     = s.substr(equalPos + 1);

//     // find '(' and ')'
//     size_t l = funcName.find('(');
//     size_t r = funcName.find(')');

//     if (l == std::string::npos || r == std::string::npos || r <= l + 1)
//         throw std::invalid_argument("Invalid function signature");

//     usedVar = funcName.substr(l + 1, r - l - 1);

//     return { funcName, usedVar, term };
// }