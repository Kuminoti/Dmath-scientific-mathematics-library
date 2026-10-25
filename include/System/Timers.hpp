#pragma once 

#ifndef DMATH_TIMERS_HPP
#define DMATH_TIMERS_HPP


#include "Dmath.hpp"

NAMESPACESTART

class Timer{
  protected: 
    using Clock = std::chrono::steady_clock;

    Clock::time_point startTime;
    Clock::time_point stopTime;
    bool running = false;


  public:

    Timer () = default;
    
    void start() {
        startTime = Clock::now();
        running = true;
    }


    virtual void stop() {
        stopTime = Clock::now();
        running = false;
    }



    double getMillis() const {
        auto endTime = running ? Clock::now() : stopTime;

        return std::chrono::duration<double, std::milli>(
            endTime - startTime
        ).count();
    }

};



class StopWatch : public Timer{
  private:
    std::vector<Dmath::Scalar> timeStamps; //The timestamps relative to the starttime
    std::vector<Dmath::Scalar> roundTimes; //The time of each individual round

  public:

    void Round(){
        if(!this->running){
            std::cerr << "Timer is not running!\n";
            return;
        }
        auto currentTime = Clock::now();
        Dmath::Scalar roundTime = std::chrono::duration<double, std::milli>(currentTime - startTime).count();
        timeStamps.push_back(roundTime);
    }

    void stop() override {
        if(!this->running){
            std::cerr << "Timer is not running!\n";
            return;
        }
        stopTime = Clock::now();
        running = false;
        timeStamps.push_back(getMillis());
    }

    std::vector<Dmath::Scalar> getTimestamps(){ return this->timeStamps; }

    void clear(){ timeStamps.clear(); }
}

NAMESPACEEND


#endif