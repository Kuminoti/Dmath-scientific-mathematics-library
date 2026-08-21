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

  public: //String checking: 

    //Finds specific substrings in longer mainstrings
    bool exsitsIn(const std::string& mainString, const std::string& find);

    //Finds a specific char in a main string
    bool exsitsInC(const std::string& mainString, const char& find);

    //Checks if the string is a number "6769"
    bool isNumeric(const std::string& str);

    size_t howOften(const std::string& mainString, const std::string& find);


    
    size_t getFirstTopLevelPosition(const std::string& str, char target);


    Dmath::Duo<std::string, std::string> splitString(std::string mainString, size_t position);



  public: //Extractors
    //Extracts between two specific chars: ( "ILovehotMoms", I,h) => Love 
    std::string extractFromTo(const std::string& mainString, char start, char end);

     //Extracts between two specific substrings 
    std::string extractWords(const std::string& mainString, const std::string& start,const std::string &end);

    //Extracts pushes the data in a vector when a specific symbol is found
    //For example the extract commands seperated by a ;
    std::vector<std::string> extractAfter(const std::string& mainString, char symbol);

    //Stopps at a . ? or ! and pushes it into a a vector
    std::vector<std::string> extractSentences(const std::string& mainString);

    //Checks for whitespace or symbols like . , ; :
    std::string extractFirstWord(const std::string& str);
   
    //Gets the inside of  {[()]} seperated by a ,(2,3,4) 2,3,4
    std::string getInBrackets(const std::string& input);

    //gets a string of numbers 
    std::vector<Dmath::Scalar> getNumbersInBrackets(std::string input);



    //Formatter
    std::string toLower(const std::string& mainString);
    std::string toUpper(const std::string& mainString);


    //Replacer
    std::string replaceWordExact(const std::string& input, const std::string& target, const std::string& replacement);

    //File operations
    std::string getFileExtension(const std::string& filename);

    std::string fixDuplicates(std::string name, std::vector<std::string> existingNames);


    std::string fixDuplicate(const std::string& duplicate);

    //removers
    std::string removeWhitespace(const std::string& str);
    
//std::string deleteChar(char c){}
//std::string deleteSubStr(std::string subStr){}



};

NAMESPACEEND
#endif 