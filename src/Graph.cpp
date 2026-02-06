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


void Dmath::Plotter::plotVector(Dmath::Vec2D vec, double scale, RGB color) {
    int ox = (int)vec.getOriginX();
    int oy = (int)vec.getOriginY(); // Pixel-Rasterpunkt
    double vx = vec.getX() * scale;
    double vy = vec.getY() * scale;

    // Endpunkt des Pfeils
    int ex = ox + (int)vx;
    int ey = oy - (int)vy; // Pixel-Y nach oben invertiert

    // Linie zeichnen
    drawLine(ox, oy, ex, ey, color);

    // Pfeilspitze berechnen
    double len = std::sqrt(vx*vx + vy*vy);
    if(len == 0) return;

    double ux = vx / len;
    double uy = vy / len;
    double arrowLength = 5.0;
    double arrowAngle = PI/6;

    int lx = (int)(ex - ux * arrowLength * std::cos(arrowAngle) + uy * arrowLength * std::sin(arrowAngle));
    int ly = (int)(ey + ux * arrowLength * std::sin(arrowAngle) + uy * arrowLength * std::cos(arrowAngle));

    int rx = (int)(ex - ux * arrowLength * std::cos(arrowAngle) - uy * arrowLength * std::sin(arrowAngle));
    int ry = (int)(ey - ux * arrowLength * std::sin(arrowAngle) + uy * arrowLength * std::cos(arrowAngle));

    drawLine(ex, ey, lx, ly, color);
    drawLine(ex, ey, rx, ry, color);

    // Endpunkt selbst
    setPixel(ex, ey, color);
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



void Dmath::Plotter::plotVectorField(Dmath::DoubleVectorFunction& vectorField, Dmath::Scalar step, RGB color) {
    const double arrowLength = 15.0;      // Länge in Pixeln
    const double unitPerPixel = 50.0;     // Skalierung mathematisch -> Pixel

    for(int px = 0; px < (int)width; px += (int)step){
        for(int py = 0; py < (int)height; py += (int)step){
            
            // Pixel -> Mathematische Koordinaten
            double x = (px - (int)cx) / unitPerPixel;
            double y = ((int)cy - py) / unitPerPixel; // invertiert für korrekte Richtung

            // Vektor aus Funktion
            Dmath::Vec3D currentVec = vectorField(x, y);
            double vx = currentVec.getX();
            double vy = -currentVec.getY();

            if(vx == 0 && vy == 0) continue; // Skip Nullvektoren

            // Normieren und skalieren auf Pfeillänge
            double len = std::sqrt(vx*vx + vy*vy);
            vx = (vx / len) * arrowLength;
            vy = (vy / len) * arrowLength;

            // Pixelkoordinaten für Startpunkt (OriginX/Y)
            // ACHTUNG: Y invertieren, da Pixel-Y nach unten
            Dmath::Vec2D vec(vx, -vy, px, py);

            // Pfeil zeichnen
            plotVector(vec, 1.5, color);
        }
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