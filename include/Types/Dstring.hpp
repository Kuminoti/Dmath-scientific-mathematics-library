#pragma once 

#ifndef DSTRING_HPP
#define DSTRING_HPP

#include"../dataTypes.hpp"
#include<unordered_map>
#include<stdexcept>
#include<algorithm>
#include <sstream>

NAMESPACESTART

class SHARED_LIB StringHelper{

public:



    bool exsitsIn(const std::string& mainString, const std::string& find);
    bool exsitsInC(const std::string& mainString, const char& find);
    bool isNumeric(const std::string& str);

    size_t howOften(const std::string& mainString, const std::string& find);

    Dmath::Duo<std::string, std::string> splitString(std::string mainString, size_t position);

    //Extractors
    std::string extractFromTo(const std::string& mainString, char start, char end);
    Dmath::Text extractSentences(const std::string& mainString);
    std::string extractFirstWord(const std::string& str);
    std::string getInBrackets(const std::string& input);

    //Formatter
    std::string toLower(const std::string& mainString);
    std::string toUpper(const std::string& mainString);


    //Replacer
    std::string replaceWordExact(const std::string& input, const std::string& target, const std::string& replacement);

    //File operations
    std::string getFileExtension(const std::string& filename);
    std::string removeWhitespace(const std::string& str){
    std::string result;
    result.reserve(str.size()); // Performance-Optimierung

    for (char c : str)
        if (!std::isspace(static_cast<unsigned char>(c)))
            result.push_back(c);

    return result;
}
    
};

NAMESPACEEND
#endif 