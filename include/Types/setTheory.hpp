#pragma once



#ifndef DMATH_DYNAMIC_ARRAY_HPP
#define DMATH_DYNAMIC_ARRAY_HPP

#include"../dataTypes.hpp"

NAMESPACESTART

template<class math>

class Set{

    
private: //private members

    math* arr;
    size_t elements = 0;
    size_t capacity = 10;


private: //private methods

    template<typename ST>
    bool isSameType(Set<ST> otherSet){
        if constexpr (!std::is_same<ST,math>::value){
            return false;
        }
        return true;
    }




public:
    

    Set(){ this->arr = new math[capacity];  }

    ~Set(){
        delete[] this->arr;
        this->arr = nullptr;
    }

    Set(size_t numberOfElements){
        this->arr = new math[numberOfElements];
        this->elements = numberOfElements;
    }

    void push_back(math element) {
        if (elements == capacity) {
            capacity *= 2;
            math* newArray = new math[capacity];
            for (size_t i = 0; i < elements; ++i) {
                newArray[i] = arr[i];
            }
            delete[] arr;
            arr = newArray;
        }
        // Add Element 
        arr[elements] = element;
        ++elements;
    }

    // Remove element 
    void pop_back() {
        if (elements > 0) {
            --elements;
        }
    }

    size_t size(){ return this->elements; }


    math operator[](size_t index){
        if(index >= elements){
            return 0;
        }
        return this->arr[index];
    }

    template<typename s>
    void Union(Set<s> otherSet){
        if constexpr (!std::is_same<math,s>::value){
            std::cerr << "Error Types need to be the same! Error-code: \n"<< Dmath::ERROR_CODE::TYPE_ERROR << std::endl;
            return;
        }

        //Loop over the Set
        const size_t num = otherSet.size();
        for(size_t i = 0; i < num; i++){
            math currentObj = otherSet[i];
            

            bool exists = false;
            for(size_t j = 0; j < this->elements; j++){
                if (this->arr[j] == currentObj){
                    exists = true;
                    break;
                }
            }

            if(!exists){
                this->push_back(currentObj);
            }
        }
    }


};

NAMESPACEEND

#endif //DMATH_DYNAMIC_ARRAY_HPP