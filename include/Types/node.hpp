#pragma once

#ifndef DMATH_NODE_HPP
#define DMATH_NODE_HPP
#include"dataTypes.hpp"

NAMESPACESTART

template<typename dType>
class Node {
private:
   
    int ID;
    dType data;

public:
    Node* right = nullptr;
    Node* left  = nullptr;
    Node(dType Data, int ID) : data(Data), ID(ID) {}

    dType findFromID(int searchID) {
        if (searchID > this->ID) {
            return (right != nullptr) ? right->findFromID(searchID) : throw std::runtime_error("ID nicht gefunden");
        }
        else if (searchID < this->ID) {
            return (left  != nullptr) ? left ->findFromID(searchID) : throw std::runtime_error("ID nicht gefunden");
        }
        return this->data;
    }

    void addright(dType newData, int newID) {
        if (right == nullptr) {
            right = new Node<dType>(newData, newID);
        }
        else {
            right->addright(newData, newID);
        }
    }

    void addleft (dType newData, int newID) {
        if (left  == nullptr) {
            left  = new Node<dType>(newData, newID);
        }
        else {
            left ->addleft (newData, newID);
        }
    }
};



NAMESPACEEND


#endif