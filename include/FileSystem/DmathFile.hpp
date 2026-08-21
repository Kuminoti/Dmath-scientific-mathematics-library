#pragma once


#ifndef DMATH_DMATH_FILE_HPP
#define DMATH_DMATH_FILE_HPP

#include"../Text/chars.hpp"
#include"../Types/FreeMap.hpp"
#include"DmathFileStream.hpp"
#include"../Types/StringHelper.hpp"
#include"DmathSyntax.hpp"

NAMESPACESTART


/* File: DmathFile.hpp
 * Date: 19.08.26
 * Author: D.Kuminoti
 * License: MIT
 * 
 * Description: Dmath files allow it to save and load Damth Data
 * 
 * 
 * Example:
 * DMATH<{
 *  Vector3D v   := (x,y,z,ox,oy,oz);
 *  Scalar x     := 3;
 *  Function f(x):= (2*x+3);
 * }>
*/





class DmathFile : public Dmath::DFStraem {
  private: //private members

    Dmath::FreeMap<std::string> content;
    Dmath::Natural elements = 0;
    Dmath::StringHelper strH;

    std::string src = "";

    
    const std::string fileOpening = "DMATH<{\n\t";
    const std::string fileEnding  = "\n\t}>";


public: //public constructors and destructors
       // Dmath-Datei laden
    explicit DmathFile(const std::string& filePath) : src(filePath){
        Dmath::FreeMap<std::string> fm = this->loadDmathFile(filePath);
        this->importMap(fm);
     }
    
    DmathFile() = default;

  private: //private memberFunction

 
    std::string getDmathString(){
        std::string data = fileOpening;
        const Dmath::Natural num = this->content.getSize();
        for(size_t i = 0; i < num; i++){
            
            std::string objName = this->content.getKeyFromIndex(i);

            std::string name = this->strH.extractFirstWord(objName);

        

            if(name == "Vector3D"){
               
                Dmath::Vec3D vec3d = this->content[i].get<Dmath::Vec3D>(); 
               
                data += Dmath::fileVector3D(objName, vec3d);
                
                continue;
            }

            else if(name == "Vector2D"){
                Dmath::Vec2D vec2d = this->content[i].get<Dmath::Vec2D>(); 
                data += Dmath::fileVector2D(objName, vec2d);
                continue; 
            }
            else if(name == "Scalar"){
                Dmath::Scalar x  = this->content[i].get<Dmath::Scalar>(); 
                data += objName + " = " + std::to_string(x) + ";\n\t";
                
                continue; 
            }
            else if(name == "Natural"){
                
                Dmath::Natural x  = this->content[i].get<Dmath::Natural>(); 
                data += objName + " = " + std::to_string(x) + ";\n\t";
               
                continue; 
            }
            else if(name == "Function"){
                
                Dmath::SingleVarFunction f = this->content[i].get<Dmath::SingleVarFunction>();
               
                data += objName + " = (" + f.getFunctionData() + ");\n\t";
                continue; 
            }
            
           
            
        }
        data += this->fileEnding;
        return data;
    }    

    
public:

    void saveDmathFile(){
        if(writeFile(this->src,this->getDmathString())){
            std::cout << "Saved file as: " + src + "\n";
            return;
        }
        throw std::runtime_error("saveDmathFile(): Error writing file");
    }


    template<typename dmath>
    void insertDmathObject(std::string objName, dmath data){
        
        if constexpr (std::is_same<dmath,Dmath::Vec3D>::value){
           this->content.insert("Vector3D " + objName, data);
        }
        else if constexpr (std::is_same<dmath,Dmath::Vec2D>::value){
           this->content.insert("Vector2D " + objName,data);
        }

        else if constexpr (std::is_same<dmath,Dmath::Natural>::value){
           this->content.insert("Natural " + objName,data);
        }
        else if constexpr (std::is_same<dmath,Dmath::Scalar>::value){
           this->content.insert("Scalar " + objName,data);
        }
        else if constexpr (std::is_same<dmath,Dmath::SingleVarFunction>::value){
           this->content.insert("Function " + objName + "(x)",data);
        }
        else if constexpr (std::is_same<dmath,Dmath::SingleVectorFunction>::value){
           this->content.insert("Curve " + objName + "(x)" ,data);
        }
        else if constexpr (std::is_same<dmath,Dmath::Complex>::value){
           this->content.insert("Complex " + objName,data);
        }
    }
    
    void importMap(const Dmath::FreeMap<std::string> inputMap){
    const Dmath::Natural num = inputMap.getSize();

    for (size_t i = 0; i < num; ++i){
        std::string currentKey = inputMap.getKeyFromIndex(i);
        Dmath::Obj obj = inputMap[i];

        switch (obj.type){
            case Dmath::Obj::Type::VEC2:
            {
                this->insertDmathObject<Dmath::Vec2D>(
                    currentKey,
                    obj.get<Dmath::Vec2D>()
                );
                break;
            }

            case Dmath::Obj::Type::VEC3:
            {
                this->insertDmathObject<Dmath::Vec3D>(
                    currentKey,
                    obj.get<Dmath::Vec3D>()
                );
                break;
            }

            case Dmath::Obj::Type::SCALAR:
            {
                this->insertDmathObject<Dmath::Scalar>(
                    currentKey,
                    obj.get<Dmath::Scalar>()
                );
                break;
            }

            case Dmath::Obj::Type::NATURAL:
            {
                this->insertDmathObject<Dmath::Natural>(
                    currentKey,
                    obj.get<Dmath::Natural>()
                );
                break;
            }

            case Dmath::Obj::Type::SINGLE_FUNC:
            {
                this->insertDmathObject<Dmath::SingleVarFunction>(
                    currentKey,
                    obj.get<Dmath::SingleVarFunction>()
                );
                break;
            }

            default:
                throw std::runtime_error(
                    "DmathFile::importMap(): unsupported object type"
                );
        }
    }
}

    Dmath::FreeMap<std::string> loadDmathFile(std::string filePath){
       
        //Check file ending and errorhandling
        auto fending = this->strH.getFileExtension(filePath);
        
        if(fending != ".dmath" && fending != ".Dmath" ){
            std::string errorMSG =
                "String input Error: \n"
                "Filesystem/DmathFile.hpp -> "
                "Dmath::FreeMap<std::string> loadDmathFile(std::string filePath): \n"
                "Unknown file: expected .Dmath or .dmath, but got: "
                + fending + "\n"
                "Dmath::ErrorCode: "
                + std::to_string(Dmath::ERROR_CODE::UNKNOWEN_FILE_TYPE)
                + "\n";
            throw std::runtime_error(errorMSG);
           }
        Dmath::FreeMap<std::string> DmathObjs;
        std::string inputFile = this->getTxtFromFile(filePath);
           
        /* Recreating the Dmath objs:
         * the DmathFile Saves the type of the obj, but we dont need the type directly in the code itself
         * instett the type is used to re create the original data:
        */
        //remove the file header and the bracets:
        
         inputFile = strH.extractFromTo(inputFile,'{','}');
        //convert the inputfile in its lines:
        std::vector<std::string> lines = strH.extractAfter(inputFile,';');
        
        
        const Dmath::Natural num = lines.size();
      
        for(size_t i = 0; i < num; i++){
            
            Dmath::ObjDef currentTypeData = Dmath::getTypeData(lines[i]);

            if(currentTypeData.one == "Vector2D"){
                Dmath::Vec2D vec = Dmath::getFromFileVec(currentTypeData);
                DmathObjs.insert<Dmath::Vec2D>(currentTypeData.two,vec);
            }

            else if(currentTypeData.one == "Scalar"){                
                Dmath::Scalar x = std::stod(currentTypeData.three);
                DmathObjs.insert<Dmath::Scalar>(currentTypeData.two,x);
            }

            else if(currentTypeData.one == "Natural"){    
                Dmath::Natural x = static_cast<Dmath::Natural>(std::stoi(currentTypeData.three));
                DmathObjs.insert<Dmath::Natural>(currentTypeData.two,x);
            }

            else if(currentTypeData.one == "Vector3D"){
                Dmath::Vec3D vec = Dmath::getFromFileVec3D(currentTypeData);
                DmathObjs.insert<Dmath::Vec3D>(currentTypeData.two,vec);
            }
            


        }

        return DmathObjs;
    }
};


NAMESPACEEND
#endif //DMATH_DMATH_FILE_HPP