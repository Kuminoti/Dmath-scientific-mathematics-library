#pragma once

#ifndef DMATH_GRAPH_HPP
#define DMATH_GRAPH_HPP


#include"Dmath.hpp"
#include <fstream>

NAMESPACESTART

typedef Dmath::Trio<byte,byte,byte> RGB;

class Plotter {

private:

    Dmath::Natural width  = 1920;
    Dmath::Natural height = 1080;
    Dmath::Natural cx = width  / 2;
    Dmath::Natural cy = height / 2;

    std::vector<RGB> image;
    std::string filename;


public: //mainConstructor:

    Plotter(const std::string& file) : filename(file), image(width * height, RGB{255,255,255}) { DrawAxes(); }


public: //Public main methods

    void save() { writeBMP(); }

    void plotFunction(const Dmath::SingleVarFunction& func, Dmath::Scalar scale = 50.0, RGB color = RGB{255,0,0});

    void plotCurve(Dmath::SingleVectorFunction& curve, Dmath::Scalar scale = 50.0, RGB color = RGB{255,0,0});

    void plotVector(Dmath::Vec2D vec, Dmath::Scalar scale = 50.0, RGB color = RGB{255,0,0});

    void plotComplexNum(Dmath::Complex z, Dmath::Scalar scale = 50.0, RGB color = RGB{0,0,255});

    void plotVectorField(Dmath::DoubleVectorFunction& vectorField, Dmath::Scalar gap = 50, RGB color = RGB{0,0,255});

    void drawLine(int x0, int y0, int x1, int y1, RGB color);

    void drawPoint(Dmath::Scalar x, Dmath::Scalar y, Dmath::Scalar scale = 50, RGB color = RGB{0,0,255});

    void clear();
    
public: //public getters and setters:

    void setWidth(unsigned int w) { width = w; }

    void setHeight(unsigned int h) { height = h; }

    void setPath(std::string fileName) { this->filename = fileName; }

    Dmath::Natural getWidth() const { return width; }

    Dmath::Natural getHeight() const { return height; }

    Dmath::Natural getCenterX() const { return cx; }

    Dmath::Natural getCenterY() const { return cy; }


private: //private helper methods

    void setPixel(int x, int y, RGB color);

    void DrawAxes();

    void DrawGrid();

    void writeBMP();

    RGB mapValueToColorSmooth(double value, double minVal, double maxVal);
    
};



NAMESPACEEND

#endif //DMATH_GRAPH_HPP