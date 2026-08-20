#pragma once 

#ifndef DMATH_STRING_HELPER_HPP
#define DMATH_STRING_HELPER_HPP

#include"../Utils/dataTypes.hpp"
#include<unordered_map>
#include<stdexcept>
#include<algorithm>
#include <sstream>
#include<iostream>
NAMESPACESTART

class  StringHelper{

public:



    bool exsitsIn(const std::string& mainString, const std::string& find);
    bool exsitsInC(const std::string& mainString, const char& find);
    bool isNumeric(const std::string& str);

    size_t howOften(const std::string& mainString, const std::string& find);
    size_t getFirstTopLevelPosition(const std::string& str, char target);


    Dmath::Duo<std::string, std::string> splitString(std::string mainString, size_t position);

    //Extractors
    std::string extractFromTo(const std::string& mainString, char start, char end);

    std::string extractWords(const std::string& mainString, const std::string& start,const std::string &end);

    //Extracts pushes the data in a vector when a specific symbol is found
    //For example the extract commands seperated by a ;
    std::vector<std::string> extractAfter(const std::string& mainString, char symbol);

    //Stopps at a . ? or ! and pushes it into a a vector
    std::vector<std::string> extractSentences(const std::string& mainString);

    //Checks for whitespace or symbols like . , ; :
    std::string extractFirstWord(const std::string& str) {
    std::string result;

    for (char c : str) {
        if (c == ' ' || c == '.' || c == ',' || c == ';') break; // Stoppe bei Leerzeichen oder Punkt
        result += c;
    }

    return result;
}
    std::string getInBrackets(const std::string& input);
    std::vector<Dmath::Scalar> getNumbersInBrackets(std::string input);

    //Formatter
    std::string toLower(const std::string& mainString);
    std::string toUpper(const std::string& mainString);


    //Replacer
    std::string replaceWordExact(const std::string& input, const std::string& target, const std::string& replacement);

    //File operations
    std::string getFileExtension(const std::string& filename);
    
    //removers
    std::string removeWhitespace(const std::string& str);
    
};

NAMESPACEEND
#endif 