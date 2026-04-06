#pragma once 

#ifndef DAMTH_3D_ARRAY_HPP
#define DAMTH_3D_ARRAY_HPP

/* File: 3dArray.hpp 
 * Project Start: 07.11.25
 *
 * Purpose: This File contains the Structure for an 3D-array of data
 * to represent a Tensor of rank 3
 * 
*/


#include"complex" //If you want to store complex numbers
#include"vectorfunction.hpp" //To store all kinds of functions

NAMESPACESTART // namespace Dmath{ 


template<typename Cube>
class ThreeArray{
  private: //Private members

    Cube*** arr;
    Dmath::Natural num;   

    Dmath::Natural lenghtA;
    Dmath::Natural lenghtB;
    Dmath::Natural lenghtC; 

  public: //public constructors

    //Cube Constroctor: crates an 3D-array with e³ elements
    ThreeArray(Dmath::Natural elements){

        this->num = std::pow(elements,3);

        this->lenghtA = elements;
        this->lenghtB = elements;
        this->lenghtC = elements;

        this->arr = new Cube**[elements];
        for (size_t i = 0; i < elements; i++) {
            arr[i] = new Cube*[elements];
            for (size_t j = 0; j < elements; j++) {
                arr[i][j] = new Cube[elements]; // Speicher für die dritte Dimension
            }
        }
    }

    //Custom constructor with a*b*c elements
    ThreeArray(Dmath::Natural a, Dmath::Natural b, Dmath::Natural c){
        this->num = a*b*c;

        this->lenghtA = a;
        this->lenghtB = b;
        this->lenghtC = c;

        this->arr = new Cube**[a];
        for(size_t i = 0; i < a; i++){
            arr[i]= new Cube*[b];
            for(size_t j = 0; j < b; j++){
                arr[i][j] = new Cube[c];
            }
        }
    }

    //Copy constructor
    ThreeArray(const ThreeArray& other){
        lenghtA = other.lenghtA;
        lenghtB = other.lenghtB;
        lenghtC = other.lenghtC;
        num = other.num;

        arr = new Cube**[lenghtA];
        for(size_t i = 0; i < lenghtA; i++){
            arr[i] = new Cube*[lenghtB];
            for(size_t j = 0; j < lenghtB; j++){
                arr[i][j] = new Cube[lenghtC];
                for(size_t k = 0; k < lenghtC; k++){
                    arr[i][j][k] = other.arr[i][j][k];
                }
            }
        }
    }

    //Destructor
    ~ThreeArray(){
        for(size_t i = 0; i < lenghtA; i++){
            for(size_t j = 0; j < lenghtB; j++){
                delete[] arr[i][j];
            }
            delete[] arr[i];
        }
        delete[] arr;
    }


  public: //public setters
    //3D-arrays start at index 1
    void setElement(Dmath::Natural a, Dmath::Natural b, Dmath::Natural c, Cube data ){
        if(!checkSize(a,b,c) ){
            std::cerr << "Error out of index\n Error-code: " << Dmath::ERROR_CODE::OUT_OF_RANGE << std::endl;
            return;
        }
        this->arr[a-1][b-1][c-1] = data;
    }

    void setAll(Cube Data){
        for(size_t a = 0; a < lenghtA; a++){
            for(size_t b = 0; b < lenghtB; b++ ){
                for(size_t c = 0; c < lenghtC; c++){
                    this->arr[a][b][c] = Data;
                }
            }
        }
    }


  public: //Public getters

    Cube getElement(Dmath::Natural a, Dmath::Natural b, Dmath::Natural c){
        if(!checkSize(a,b,c)){
            return Cube{}; //error
        }
        return this->arr[a-1][b-1][c-1];
    }

    Cube operator()(Dmath::Natural a, Dmath::Natural b, Dmath::Natural c){
        if(!checkSize()){
            return Cube{}; //error
        }
        return arr[a-1][b-1][c-1];

    }

    Dmath::Natural getNumberOfElements(){ return this->num; }


  private: //Private Helper functions

    bool checkSize(Dmath::Natural a, Dmath::Natural b, Dmath::Natural c){
        if(a > lenghtA || a < 1 || b > lenghtB || b < 1 || c > lenghtC || c < 1 ){
            std::cerr << "Error out of index\n Error-code: " << Dmath::ERROR_CODE::OUT_OF_RANGE << std::endl;
            return false;
        }
        return true;
    }


};







NAMESPACEEND // } Dmath-namespace

#endif //DAMTH_3D_ARRAY_HPP