#pragma once
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include"macros.hpp"
// #include"mathVector.hpp"

NAMESPACESTART


template<class mat>
class Matrix {
private: //Private members

    mat** mainMatrix;
    bool squaredMatrix = false;

    uint8_t elementsRow    = 0;
    uint8_t elementsColumn = 0;
    uint16_t totalElements = 0;

    
    

private: //Private methods and helper functions


    Matrix<mat> getSubMatrix(uint8_t excludingRow, uint8_t excludingCol) const {
        Matrix<mat> subMatrix(this->elementsRow - 1, this->elementsColumn - 1);
        uint8_t subMatrixRow = 0;
        uint8_t subMatrixCol = 0;

        for (uint8_t row = 0; row < this->elementsRow; row++) {
            if (row == excludingRow) continue;
            subMatrixCol = 0;
            for (uint8_t col = 0; col < this->elementsColumn; col++) {
                if (col == excludingCol) continue;
                subMatrix.setElement(subMatrixRow + 1, subMatrixCol + 1, this->getElement(row + 1, col + 1));
                subMatrixCol++;
            }
            subMatrixRow++;
        }

        return subMatrix;
    }


    bool checkMatrixSizes(Matrix matrixOne, Matrix matrixTwo){
        bool valid = false;

        if(matrixOne.elementsColumn == matrixTwo.elementsColumn &&
           matrixOne.elementsRow    == matrixTwo.elementsRow    ){
            valid = true;
        }
        return valid;
    }


public: // condtructor and destructor

    // Squared matrix constructor
    Matrix(uint8_t elements){
        this->squaredMatrix = true;
        this->elementsColumn = elements;
        this->elementsRow = elements;
        this->totalElements = elements * elements;

        this->mainMatrix = new mat*[this->elementsRow];
        for(uint8_t i = 0; i<this->elementsRow; i++){
            this->mainMatrix[i] = new mat[this->elementsColumn];
        }
    }

    Matrix(uint8_t elementsRow, uint8_t elementsColumn){
        this->elementsColumn =  elementsColumn;
        this->elementsRow    =  elementsRow;
        this->totalElements  =  elementsRow * elementsColumn;

        if(elementsColumn == elementsRow){
            this->squaredMatrix = true;
        }


        this->mainMatrix = new mat*[this->elementsRow];
        for(uint8_t i = 0; i<this->elementsRow; i++){
            this->mainMatrix[i] = new mat[this->elementsColumn];
        }
    }

    ~Matrix(){
        for(uint8_t i = 0; i < this->elementsRow; i++){
            delete[] this->mainMatrix[i];
        }
        delete[] this->mainMatrix;
        this->mainMatrix = nullptr;
    }


public: //Getters and setters

    inline bool isSquared(){
        return this->squaredMatrix;
    }

    uint8_t getElementsRow(){ return this->elementsRow; }
    uint8_t getElementsColumn(){ return this->elementsColumn;}

    void setAll(mat data){
        for(size_t i = 0; i < this->elementsRow; i++){
            for(uint8_t j = 0; j < this->elementsColumn; j++){
                this->mainMatrix[i][j] = data;
            }

        }
    }


    Matrix transpose() {
        Matrix transposedMatrix(this->elementsColumn, this->elementsRow);

        for (uint8_t row = 0; row < this->elementsRow; row++) {
            for (uint8_t col = 0; col < this->elementsColumn; col++) {
                transposedMatrix.setElement(col + 1, row + 1, this->getElement(row + 1, col + 1));
            }
        }

        return transposedMatrix;
    }

public: 

    Matrix inverse() {
    if (!this->isSquared()) {
        return Matrix<mat>(1);
    }

    Matrix<mat> inverseMatrix(this->elementsRow);

    if (elementsRow == 2) {

        Dmath::SingleVarFunction a = this->getElement(1,1);
        Dmath::SingleVarFunction b = this->getElement(1,2);
        Dmath::SingleVarFunction c = this->getElement(2,1);
        Dmath::SingleVarFunction d = this->getElement(2,2);

        // determinant = ad - bc
        Dmath::SingleVarFunction determinant = a * d - b * c;

        Dmath::SingleVarFunction minusB = [=](Dmath::Scalar x) {
            return -b(x);
        };

        Dmath::SingleVarFunction minusC = [=](Dmath::Scalar x) {
            return -c(x);
        };

        inverseMatrix.setElement(1,1, d / determinant);
        inverseMatrix.setElement(1,2, minusB / determinant);
        inverseMatrix.setElement(2,1, minusC / determinant);
        inverseMatrix.setElement(2,2, a / determinant);
    }

    return inverseMatrix;
}


    mat getElement(uint8_t row, uint8_t Column){
        if(row < 1 || row > this->elementsRow || Column < 1 || Column > this->elementsColumn){

            std::cerr << "Error out of range" <<std::endl;

            // NULL ((void *)0)
        }
        mat Result;
        Result = this->mainMatrix[row-1][Column-1]; //Since an array is 0 indexed
        return Result;
    }

    void setElement(uint8_t row, uint8_t Column, mat data){
        if(row < 1 || row > this->elementsRow || Column < 1 || Column > this->elementsColumn){

            std::cerr << "Error out of range" <<std::endl;

            return; 
        }
        this->mainMatrix[row-1][Column-1] = data;

    }

    Matrix getSquaredMatrix(uint8_t elements){
        return Matrix(elements);
    }   

public:

    mat determinant() const {
        if (!this->squaredMatrix) {
            std::cerr << "Determinant is undefined for non-square matrices. Returning 0." << std::endl;
            return DOUBLENULLFUNCTION; 
        }

        if (this->elementsRow == 1) {
            return this->mainMatrix[0][0]; // 1x1-Matrix
        }

        if (this->elementsRow == 2) {
            return this->mainMatrix[0][0] * this->mainMatrix[1][1] - this->mainMatrix[0][1] * this->mainMatrix[1][0];
        }

        // mat det = 0;
        // // for (uint8_t col = 0; col < this->elementsColumn; col++) {
        // //     Matrix<mat> subMatrix = this->getSubMatrix(0, col); // Untermatrix erstellen
        // //     det += (col % 2 == 0 ? 1 : -1) * this->mainMatrix[0][col] * subMatrix.determinant();
        // // }

        // return det;
    }



  

};

NAMESPACEEND

#endif //MATRIX_HPP