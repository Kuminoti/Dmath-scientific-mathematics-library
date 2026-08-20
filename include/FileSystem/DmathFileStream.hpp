#pragma once


#ifndef DMATH_BASIC_FILE_OPERATIONS_HPP
#define DMATH_BASIC_FILE_OPERATIONS_HPP

#include"../Dmath.hpp"
#include<fstream>
#include<sstream>
#include<bitset>

NAMESPACESTART

class DFStraem{
  private: 
    Dmath::StringHelper strH;

    /* The String component of the map holds the file ending (.txt, .Dmath, .exe etc)
     * and the Dmath::Function holds the specific file operations
    */
    Dmath::MapD<std::string, Dmath::Function> fileOPs;


  public:

    //Loads a file and returns
    std::string getTxtFromFile(const std::string& filePath){
        std::cout << "getTxtFromFile" << std::endl;
        std::ifstream file(filePath, std::ios::in);
        if(!file){
            return std::string();
        }

        std::ostringstream content;
        content << file.rdbuf();
        return content.str();
    }



    bool writeFile(const std::string& outputPath, const std::string& text){

        std::ofstream file(outputPath, std::ios::out);
        if(!file){
            return false;
        }

        file << text;
        return static_cast<bool>(file);
    }


    
std::string textToBitString(const std::string& text){
        std::string bits;
        bits.reserve(text.size() * 8);
        for(unsigned char c : text){
            bits += std::bitset<8>(c).to_string();
        }
        return bits;
    }


    std::string bitStringToText(const std::string& bits){
        if(bits.size() % 8 != 0){
            return std::string();
        }

        std::string text;
        text.reserve(bits.size() / 8);
        for(size_t i = 0; i < bits.size(); i += 8){
            std::bitset<8> byte(bits.substr(i, 8));
            text.push_back(static_cast<char>(byte.to_ulong()));
        }
        return text;
    }


    bool writeBinaryFile(const std::string& outputPath, const std::string& text){
        std::ofstream file(outputPath, std::ios::out | std::ios::binary);
        if(!file){
            return false;
        }

        const std::string bits = textToBitString(text);
        file.write(bits.data(), static_cast<std::streamsize>(bits.size()));
        return static_cast<bool>(file);
    }


    std::string getBinaryFromFile(const std::string& filePath){
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if(!file){
            return std::string();
        }

        std::ostringstream content;
        content << file.rdbuf();
        return bitStringToText(content.str());
    }
};


























NAMESPACEEND

#endif //DMATH_BASIC_FILE_OPERATIONS_HPP


