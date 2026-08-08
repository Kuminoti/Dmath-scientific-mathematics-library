#pragma once

#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include"../Utils/dataTypes.hpp"
#include<mutex>
NAMESPACESTART
class Callback {

private:

    std::atomic<bool> intervalRunning{false}; 
    std::thread intervalThread;               
    std::mutex debounceMutex;                 
    bool debounceRunning = false;             

public:

    void setInterval(Dmath::voidFunction func, size_t millis) {
        stopInterval();  

        intervalRunning = true;
        intervalThread = std::thread([this, func, millis]() {
            while (intervalRunning) {
                func(); 
                std::this_thread::sleep_for(std::chrono::milliseconds(millis)); 
            }
        });
        intervalThread.detach(); 
    }

    void setTimeOut(Dmath::voidFunction func, size_t millis) {
        std::thread([func, millis]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(millis));
            func(); 
        }).detach(); 
    }

    void stopInterval() {
        intervalRunning = false;
        if (intervalThread.joinable()) {
            intervalThread.join(); 
        }
    }

    void debounce(Dmath::voidFunction func, size_t delayMillis) {
        std::lock_guard<std::mutex> lock(debounceMutex); 

        if (debounceRunning) {
            return; 
        }

        debounceRunning = true;
        std::thread([this, func, delayMillis]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMillis)); 
            func(); 
            debounceRunning = false; 
        }).detach();
    }

    ~Callback() {
        stopInterval();
    }
};


NAMESPACEEND

#endif