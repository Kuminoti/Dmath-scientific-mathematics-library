#pragma once 

#ifndef DMATH_FREE_MAP_HPP
#define DMATH_FREE_MAP_HPP

#include"../Functional/vectorfunction.hpp"
#include<initializer_list>



/* File: types/FreeMap.hpp
 * Date: 19.08.2026
 *
 * Author: D. Kuminoti (https://github.com/Kuminoti)
 * License: MIT
 *
 * Description:
 * This file contains the Dmath::FreeMap container and the auxiliary
 * Dmath::Obj and Dmath::ObjType types.
 *
 * FreeMap is a heterogeneous associative container designed for the
 * Dmath library. Unlike a conventional std::map, whose mapped type is
 * fixed, FreeMap allows different types of objects to be stored under
 * the same key type.
 *
 * The supported object types include scalar and natural numbers,
 * strings, vectors, complex numbers, mathematical functions,
 * vector-valued functions and matrices.
 *
 * Each stored object is represented internally by an Obj instance.
 * Obj contains a type identifier and storage for the supported Dmath
 * datatypes. ObjType<T> provides the compile-time association between
 * a C++/Dmath type and its corresponding Obj::Type identifier.
 *
 * Objects can subsequently be accessed through their index and their
 * concrete type can be obtained using Obj::get<T>().
 *
 * The container is intended primarily for situations in which objects
 * of different mathematical types need to be stored and retrieved
 * dynamically, for example in symbolic mathematics, function
 * registries, parsers or mathematical expression systems.
 *
 */


NAMESPACESTART

struct Obj {

    enum class Type {
        NONE,
        STRING,
        SCALAR,
        NATURAL,
        VEC2,
        VEC3,
        COMPLEX,
        FUNC,
        SINGLE_FUNC,
        DOUBLE_FUNC,
        TRIPLE_FUNC,
        SINGLE_VEC_FUNC,
        DOUBLE_VEC_FUNC,
        TRIPLE_VEC_FUNC,
        MATRIX, //<Dmath::Scalar>

    };

    Type type = Type::NONE;

    Dmath::Scalar num{};
    Dmath::Natural intNum{};
    Dmath::Vec2D vec2{};
    Dmath::Vec3D vec3{};
    Dmath::Complex complex{};
    Dmath::Function Func{};
    Dmath::SingleVarFunction sFunc{};
    Dmath::DoubleVarFunction dFunc{};
    Dmath::TripleVarFunction tFunc{};
    Dmath::SingleVectorFunction svFunc{};
    Dmath::DoubleVectorFunction dvFunc{};
    Dmath::TripleVectorFunction tvFunc{};
  
 
    std::string str{};

template<typename T>
    T& get() {

        if (type != ObjType<T>::value)
            throw std::runtime_error("DArray: wrong type access");

        if constexpr (std::is_same_v<T, std::string>){
            return str;
        }
        else if constexpr (std::is_same_v<T, Dmath::Scalar>){
            return num;
        }
        else if constexpr (std::is_same_v<T, Dmath::Natural>){
            return intNum;
        }
        else if constexpr (std::is_same_v<T, Dmath::Vec2D>){
            return vec2;
        }
        else if constexpr (std::is_same_v<T, Dmath::Vec3D>){
            return vec3;
        }

        else if constexpr (std::is_same_v<T, Dmath::Complex>){
            return complex;
        }

        else if constexpr (std::is_same_v<T, Dmath::Function>){
            return Func;
        }

        else if constexpr (std::is_same_v<T, Dmath::SingleVarFunction>){
            return sFunc;
        }

        else if constexpr (std::is_same_v<T, Dmath::DoubleVarFunction>){
            return dFunc;
        }

        else if constexpr (std::is_same_v<T, Dmath::TripleVarFunction>){
            return tFunc;
        }
        

    }

};

#pragma region Types

template<typename T>
struct ObjType;

template<> struct ObjType<std::string> {
    static constexpr Obj::Type value = Obj::Type::STRING;
};

template<> struct ObjType<Dmath::Scalar> {
    static constexpr Obj::Type value = Obj::Type::SCALAR;
};

template<> struct ObjType<Dmath::Natural> {
    static constexpr Obj::Type value = Obj::Type::NATURAL;
};

template<> struct ObjType<Dmath::Vec2D> {
    static constexpr Obj::Type value = Obj::Type::VEC2;
};

template<> struct ObjType<Dmath::Vec3D> {
    static constexpr Obj::Type value = Obj::Type::VEC3;
};

template<> struct ObjType<Dmath::Complex> {
    static constexpr Obj::Type value = Obj::Type::COMPLEX;
};

template<> struct ObjType<Dmath::Function> {
    static constexpr Obj::Type value = Obj::Type::FUNC;
};

template<> struct ObjType<Dmath::SingleVarFunction> {
    static constexpr Obj::Type value = Obj::Type::SINGLE_FUNC;
};

template<> struct ObjType<Dmath::DoubleVarFunction> {
    static constexpr Obj::Type value = Obj::Type::DOUBLE_FUNC;
};

template<> struct ObjType<Dmath::TripleVarFunction> {
    static constexpr Obj::Type value = Obj::Type::TRIPLE_FUNC;
};

template<> struct ObjType<Dmath::SingleVectorFunction> {
    static constexpr Obj::Type value = Obj::Type::SINGLE_VEC_FUNC;
};

template<> struct ObjType<Dmath::DoubleVectorFunction> {
    static constexpr Obj::Type value = Obj::Type::DOUBLE_VEC_FUNC;
};

template<> struct ObjType<Dmath::TripleVectorFunction> {
    static constexpr Obj::Type value = Obj::Type::TRIPLE_VEC_FUNC;
};
template<> struct ObjType<Dmath::Matrix<Dmath::Scalar>> {
    static constexpr Obj::Type value = Obj::Type::MATRIX;
};

#pragma endregion Types




template<typename dmath> //Key datatype
class FreeMap{
  private: //Private members:

    std::vector<Dmath::Duo<dmath, Obj>> mainMap;
    Dmath::Natural size = 0;


  public: 

    template<typename T>
    T get(dmath key){
        return this->getFromKey(key).get<T>();
    }

    Obj& operator[](Dmath::Natural i) {
        return mainMap.at(i).two;
    }

    template<typename Input>
    void insert(dmath dataKey,Input value ){
        Obj obj;
        if constexpr (std::is_same<Input,std::string>::value){
            obj.type = Obj::Type::STRING;
            obj.str = value;
        }
        else if constexpr (std::is_same<Input,Dmath::Scalar>::value){
            obj.type = Obj::Type::SCALAR;
            obj.num = value;
        }
        else if constexpr (std::is_same<Input,Dmath::SingleVarFunction>::value){
            obj.type = Obj::Type::SINGLE_FUNC;
            obj.sFunc = value;
        }
        else if constexpr (std::is_same<Input,Dmath::Function>::value){
            obj.type = Obj::Type::FUNC;
            obj.Func = value;
        }

        this->mainMap.push_back({dataKey, obj});
        
    }




    Obj& getFromKey(const dmath& key) {

        for (size_t i = 0; i < mainMap.size(); ++i) {

            if (key == mainMap.at(i).one) {
                return mainMap.at(i).two;
            }
        }

        throw std::runtime_error(
            "Dmath::FreeMap::getFromKey(): Key not found"
        );
    }


    Dmath::Natural getSize() { return mainMap.size();}



  private:
    bool searchKey(dmath key){
        const Dmath::Natural num = this->mainMap.size();
        for(size_t i = 0; i < num; i++){
            if(key == mainMap.at(i).one){
                return true;
            }
        }
        return false;
    }

};




NAMESPACEEND

#endif //DMATH_LEXICON_HPP