#include "../include/Graph.hpp"



void Dmath::Plotter::plotFunction(const Dmath::SingleVarFunction& func, Dmath::Scalar scale, RGB color){
    for (int px = 0; px < (int)width; px++) {
        double x = (px - (int)cx) / scale;
        double y = func(x);

        int py = (int)cy - (int)(y * scale);
        setPixel(px, py, color);
    }
}




void Dmath::Plotter::plotCurve(Dmath::SingleVectorFunction& curve, Dmath::Scalar scale, RGB color) {
    for (int t = 0; t < 1000; t++) {
        double param = t / 100.0; // Beispiel: t von 0 bis 10 in Schritten von 0.01
        Dmath::Vec2D point = curve.call2D(param);

        int px = (int)cx + (int)(point.getX() * scale);
        int py = (int)cy - (int)(point.getY() * scale);
        setPixel(px, py, color);
    }
}


void Dmath::Plotter::plotVector(Dmath::Vec2D vec, Dmath::Scalar scale, RGB color) {
    // Zielkoordinaten in Pixel
    int px = (int)cx + (int)(vec.getX() * scale) + vec.getOriginX() * scale;
    int py = (int)cy - (int)(vec.getY() * scale) - vec.getOriginY() * scale; 

    // Linie vom Ursprung zum Endpunkt
    int steps = 100;
    for (int i = 0; i <= steps; i++) {
        int stepX = (int)(vec.getX() * scale * i / steps) + vec.getOriginX() * scale;
        int stepY = (int)(vec.getY() * scale * i / steps) + vec.getOriginY() * scale;
        setPixel((int)cx + stepX, (int)cy - stepY, color);
    }

    // --- arrow tip ---
    double dx = px - (int)cx;
    double dy = py - (int)cy;
    double len = std::sqrt(dx*dx + dy*dy);
    if(len == 0) return;

    double ux = dx / len;
    double uy = dy / len;

    double arrowLength = 5.0;      // Länge der Pfeilspitze in Pixel
    double arrowAngle  = PI / 6;  // Winkel der Spitze (30 Grad)

    // Linke Spitze
    int lx = (int)(-ux * arrowLength * std::cos(arrowAngle) + uy * arrowLength * std::sin(arrowAngle));
    int ly = (int)(-uy * arrowLength * std::cos(arrowAngle) - ux * arrowLength * std::sin(arrowAngle));

    // Rechte Spitze
    int rx = (int)(-ux * arrowLength * std::cos(arrowAngle) - uy * arrowLength * std::sin(arrowAngle));
    int ry = (int)(-uy * arrowLength * std::cos(arrowAngle) + ux * arrowLength * std::sin(arrowAngle));

    // Zeichne die Pfeilspitze
    drawLine(px, py, px + lx, py + ly, color);
    drawLine(px, py, px + rx, py + ry, color);

    // Endpunkt selbst
    setPixel(px, py, color);
}

// Hilfsfunktion zum Zeichnen von Linien (Bresenham)
void Dmath::Plotter::drawLine(int x0, int y0, int x1, int y1, RGB color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while(true) {
        setPixel(x0, y0, color);
        if(x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if(e2 >= dy) { err += dy; x0 += sx; }
        if(e2 <= dx) { err += dx; y0 += sy; }
    }
}


void Dmath::Plotter::setPixel(int x, int y, RGB color) {
    if (x < 0 || x >= (int)width || y < 0 || y >= (int)height) return;
    image[y * width + x] = color;
}









    void Dmath::Plotter::DrawAxes() {

    const int minorStep = 10;   // kleine Striche
    const int majorStep = 50;   // große Striche
    const int minorSize = 3;
    const int majorSize = 6;

    // X-Achse
    for (unsigned int x = 0; x < width; x++) {
        setPixel(x, cy, RGB{0,0,0});

        int dx = abs((int)x - (int)cx);

        if (dx % majorStep == 0) {
            for (int i = -majorSize; i <= majorSize; i++)
                setPixel(x, cy + i, RGB{0,0,0});
        }
        else if (dx % minorStep == 0) {
            for (int i = -minorSize; i <= minorSize; i++)
                setPixel(x, cy + i, RGB{0,0,0});
        }
    }

    // Y-Achse
    for (unsigned int y = 0; y < height; y++) {
        setPixel(cx, y, RGB{0,0,0});

        int dy = abs((int)y - (int)cy);

        if (dy % majorStep == 0) {
            for (int i = -majorSize; i <= majorSize; i++)
                setPixel(cx + i, y, RGB{0,0,0});
        }
        else if (dy % minorStep == 0) {
            for (int i = -minorSize; i <= minorSize; i++)
                setPixel(cx + i, y, RGB{0,0,0});
        }
    }
}






void Dmath::Plotter::writeBMP() {
        int rowPadding = (4 - (width * 3) % 4) % 4;
        int fileSize = 54 + (3 * width + rowPadding) * height;

        unsigned char fileHeader[14] = {
            'B','M',
            (byte)(fileSize),
            (byte)(fileSize >> 8),
            (byte)(fileSize >> 16),
            (byte)(fileSize >> 24),
            0,0,0,0,
            54,0,0,0
        };

        unsigned char infoHeader[40] = {
            40,0,0,0,
            (byte)(width),
            (byte)(width >> 8),
            (byte)(width >> 16),
            (byte)(width >> 24),
            (byte)(height),
            (byte)(height >> 8),
            (byte)(height >> 16),
            (byte)(height >> 24),
            1,0,
            24,0
        };

        std::ofstream file(filename, std::ios::binary);
        file.write((char*)fileHeader, 14);
        file.write((char*)infoHeader, 40);

        unsigned char pad[3] = {0,0,0};

        for (int y = height - 1; y >= 0; y--) {
            for (unsigned int x = 0; x < width; x++) {
                const RGB& p = image[y * width + x];
                byte bgr[3] = { p.three, p.two, p.one }; // RGB → BGR
                file.write((char*)bgr, 3);
            }
            file.write((char*)pad, rowPadding);
        }

        file.close();
    }