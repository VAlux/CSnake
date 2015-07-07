#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <iostream>
#include <windows.h>
#include <QVector>

struct Point{

    int X;
    int Y;

    Point()
    {
        X = Y = 0;
    }

    Point(int x, int y)
    {
        this->X = x;
        this->Y = y;
    }

    void move(Point *direction){
        X += direction->X;
        Y += direction->Y;
    }
};

class GraphicsEngine
{
public:
    GraphicsEngine();
    ~GraphicsEngine();
    void renderPath(QVector<Point *> *path, const char texture) const;
    void renderPoint(Point *point, const char texture) const;
    void clearPoint(Point *point) const;
    void cursorVisible(bool visible);

private:

    HANDLE _outputDescriptor;

};

#endif // GRAPHICSENGINE_H
