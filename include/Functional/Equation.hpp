#pragma once 


#ifndef DMATH_EQUATION_HPP
#define DMATH_EQUATION_HPP

#include"mathFunction.hpp"

NAMESPACESTART

class EQ{


    Dmath::Scalar tollerance = 1e-10;
  public:

    bool solutionExists(Dmath::SingleVarFunction func, Dmath::Scalar solution ,Dmath::Parameters params ){
        Dmath::Scalar start = params.one;
        Dmath::Scalar end   = params.two;
        Dmath::Scalar step  = params.three;

        if(!Dmath::checkParams(params)){
            return false;
        }

        Dmath::Scalar previousX = start;
        Dmath::Scalar previousY = func(previousX);

        for(Dmath::Scalar x = start + step; x <= end; x += step)
        {
            Dmath::Scalar currentY = func(x);

            // Exakte Nullstelle gefunden
            if(std::abs(currentY - solution) < tollerance)
            {
                return true;
            }

            // Vorzeichenwechsel
            if(previousY * currentY < 0)
            {
                return true;
            }

            previousY = currentY;
        }

        return false;
    }

    Dmath::Scalar solveC(Dmath::SingleVarFunction& func, Dmath::Scalar solution ,Dmath::Parameters params = {-50,50,0.1}){
        Dmath::Natural maxIterations = Dmath::numberOfElements(params);
        Dmath::SingleVarFunction dx = func.getDerivative();
        
        for(int i = 0; i < maxIterations; i++){
            double fx = func(solution);
            double dfx = dx(solution);

            if(std::abs(dfx) < tollerance){
                throw std::runtime_error("Derivative too small.");
            }

            double next = solution - fx / dfx;

            if(std::abs(next - solution) < tollerance){
                return next;
            }

            solution = next;
        }

        throw std::runtime_error("No convergence.");
        return -1;
    }

    std::vector<Dmath::Scalar> solve(Dmath::SingleVarFunction lhs, Dmath::SingleVarFunction rhs, Dmath::Scalar solution, Dmath::Parameters params = {-50,50,0.1}){
        /* Solve:
         * f(x) = g(x)     | -g(x)
         * f(x) - g(x) = 0 | use newton method
        */
        Dmath::SingleVarFunction func = rhs - lhs; 
        std::vector<Dmath::Scalar> data = solve(func,0,params);
        return data;
    }



    std::vector<Dmath::Scalar> solve(Dmath::SingleVarFunction func, Dmath::Scalar solution, Dmath::Parameters params = {-50,50,0.1}){

        std::vector<Dmath::Scalar> solutions;

        double start = params.one;
        double end   = params.two;
        double step  = params.three;

        auto maxIterations = Dmath::numberOfElements(params);
        if(!checkParams(params)){ return solutions; }

        Dmath::Function c = [solution](){ return solution;  }; 

        Dmath::SingleVarFunction fofx = func - c;
        Dmath::SingleVarFunction derivative = fofx.getDerivative();

        for(double x0 = start; x0 <= end; x0 += step)
        {
            double x = x0;

            bool converged = false;

            // Newton iteration
            for(int i = 0; i < maxIterations; i++){
                double fx  = fofx(x);
                double dfx = derivative(x);

                if(std::abs(dfx) < tollerance)
                {
                    break;
                }

                double next = x - fx / dfx;

                if(std::abs(next - x) < tollerance)
                {
                    x = next;
                    converged = true;
                    break;
                }

                x = next;
            }

            // solution found
            if(converged)
            {
                bool alreadyExists = false;

                // avoid duplicates
                for(const auto& sol : solutions)
                {
                    if(std::abs(sol - x) < tollerance * 10)
                    {
                        alreadyExists = true;
                        break;
                    }
                }

                // verify root
                if(!alreadyExists &&
                std::abs(fofx(x)) < tollerance * 10)
                {
                    solutions.push_back(x);
                }
            }
        }

        return solutions;
    }














};


NAMESPACEEND

#endif //DMATH_EQUATION_HPP