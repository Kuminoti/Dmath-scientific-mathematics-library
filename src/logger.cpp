#include"../include/Types/logger.hpp"


double DEBUG::LOGGER::getMilliseconds(){
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> elapsedMilliseconds = now - start;
    return elapsedMilliseconds.count();
}



DEBUG::LOGGER::LOGGER(std::string ProjectName){
    this->logFile = false;
    std::string firstString = "Project " + ProjectName + " Debug information\n\n"; 
    this->currentInformation +=firstString;
    start = std::chrono::system_clock::now();
}


DEBUG::LOGGER::LOGGER(std::string ProjectName, std::string file){
    this->logFile = true;
    this->filePath = file;
    std::string firstString = "Project " + ProjectName + " Debug information\n\n"; 
    this->currentInformation +=firstString;
    start = std::chrono::system_clock::now();
}


DEBUG::LOGGER::~LOGGER(){
        std::string Info = "Number of Warnings: " + std::to_string(this->numberOfWarnings) + "\nNumber of Errors: " + std::to_string(numberOfErrors) + "\nTotal execution time: " + std::to_string(getMilliseconds());
        this->currentInformation += Info;
        if(logFile){
            std::string src = this->filePath;
            std::ofstream loggerFile(src.c_str());
            loggerFile << currentInformation;
        }
        std::cout << this->currentInformation;
    }


void DEBUG::LOGGER::LOG(std::string info, const char* FILE, int LINE){
    std::string fileName = FILE; 
    std::string LineNumber = std::to_string(LINE);
    std::string logString = "File: " + fileName + " | Line: " + LineNumber + " | Info: " + info + "\n";
    std::cout << logString;
    std::string millis = std::to_string(getMilliseconds());
    std::string exeTime = "\t" + millis + " milliseconds after Logger start\n\n";
    logString += exeTime; 

    this->currentInformation += logString;
}


void DEBUG::LOGGER::LOG(std::string info){
        
    std::string logString = "Info:\n " + info + "\n";
    std::cout << logString;
    std::string millis = std::to_string(getMilliseconds());
    std::string exeTime = "\t" + millis + " milliseconds after Logger start\n\n";
    logString += exeTime; 

    this->currentInformation += logString;
}



void DEBUG::LOGGER::WARN(std::string warning){
    std::string warn = "Warning: " + warning + "!\n";
    this->currentInformation += warn;
    this->numberOfWarnings++;
}


void DEBUG::LOGGER::Error(int err, std::string errorMessage){
    std::string error = "Error: " + errorMessage + "\n\tERROR-CODE: " + std::to_string(err) + "\n";
    std::cout << error << std::endl;
    this->currentInformation += error;
    this->numberOfErrors++;
}


void DEBUG::LOGGER::addText(std::string info){
    this->currentInformation += info + "\n";
}