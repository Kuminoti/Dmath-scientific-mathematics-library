#pragma once 

#ifndef DMATH_LIST_HPP
#define DMATH_LIST_HPP

#include"../Utils/macros.hpp"
#include<iostream>
#include"node.hpp"

NAMESPACESTART


template<class dType>
class List {
private:
    size_t numberOfElements = 0;
    size_t elementsright = 0;
    size_t elementsleft  = 0;
    

public:
Dmath::Node<dType>* headNode = nullptr;
    List(dType input) {
        this->numberOfElements = 1;
        this->headNode = new Dmath::Node<dType>(input, 0);
    }

    void pushright(dType data) {
        this->elementsright++;
        this->numberOfElements++;
        this->headNode->addright(data, elementsright);
    }

    void pushleft (dType data) {
        this->elementsleft ++;
        this->numberOfElements++;
        this->headNode->addleft (data, -elementsleft );
    }

    dType getElementFromID(int ID) {
        return this->headNode->findFromID(ID);
    }

    size_t size() { return this->numberOfElements; }
    size_t leftElements() { return this->elementsleft ; }
    size_t rightElements() { return this->elementsright; }
};

NAMESPACEEND
#endif