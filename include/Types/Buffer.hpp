#pragma once 

#ifndef DMATH_BUFFER_HPP
#define DMATH_BUFFER_HPP

#include"../dataTypes.hpp"

NAMESPACESTART

template<typename Tp>
class Buffer {

private:
    Dmath::Natural capacity;
    Dmath::Natural index = 0;
    bool full = false;
    Tp* arr = nullptr;

public:
    Buffer(Dmath::Natural capacity)
        : capacity(capacity)
    {
        arr = new Tp[capacity];
    }

    ~Buffer(){
        delete[] arr;
    }

    // Keine Kopien erlauben (wichtig!)
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    void pushBack(const Tp& data){
        arr[index] = data;
        index = (index + 1) % capacity;

        if(index == 0)
            full = true;
    }

    Dmath::Natural size() const {
        return full ? capacity : index;
    }

    const Tp& operator[](Dmath::Natural i) const {
        if(i >= size()){
            std::cerr << "Out of range"<< Dmath::ERROR_CODE::OUT_OF_RANGE << std::endl;
            std::abort();
        }
        return arr[i];
    }

    std::vector<Tp> toVectorChronological() const {
        std::vector<Tp> result;
        Dmath::Natural currentSize = size();

        result.reserve(currentSize);

        if(!full) {
            // Noch nicht überschrieben
            for(Dmath::Natural i = 0; i < index; i++)
                result.push_back(arr[i]);
        }
        else {
            // Buffer ist voll → ältestes Element ist bei index
            for(Dmath::Natural i = 0; i < capacity; i++) {
                Dmath::Natural pos = (index + i) % capacity;
                result.push_back(arr[pos]);
            }
        }

        return result;
    }
};





NAMESPACEEND

#endif