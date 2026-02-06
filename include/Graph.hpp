#pragma once

#ifndef DMATH_GRAPH_HPP
#define DMATH_GRAPH_HPP


#include"Dmath.hpp"
#include <fstream>

NAMESPACESTART

typedef Dmath::Trio<byte,byte,byte> RGB;

class Plotter {

private:

    unsigned int width  = 1000;
    unsigned int height = 800;
    unsigned int cx = width  / 2;
    unsigned int cy = height / 2;

    std::vector<RGB> image;
    std::string filename;

public: //Public main methods
    Plotter(const std::string& file) : filename(file), image(width * height, RGB{255,255,255}) { DrawAxes(); }

    void save() { writeBMP(); }

    // y = f(x)
    void plotFunction(const Dmath::SingleVarFunction& func, Dmath::Scalar scale = 50.0, RGB color = RGB{255,0,0});

    void plotCurve(Dmath::SingleVectorFunction& curve, Dmath::Scalar scale = 50.0, RGB color = RGB{255,0,0});

    void plotVector(Dmath::Vec2D vec, Dmath::Scalar scale = 50.0, RGB color = RGB{255,0,0});

    void plotVectorField(Dmath::DoubleVectorFunction& vectorField, Dmath::Scalar gap = 50, RGB color = RGB{0,0,255});

    void drawLine(int x0, int y0, int x1, int y1, RGB color);

    

private:



    void setPixel(int x, int y, RGB color);

    void DrawAxes();

    void writeBMP();
};



NAMESPACEEND

#endif //DMATH_GRAPH_HPP