#include "graphicsengine.h"

GraphicsEngine::GraphicsEngine()
{
    _outputDescriptor = GetStdHandle(STD_OUTPUT_HANDLE);
}

GraphicsEngine::~GraphicsEngine()
{
    CloseHandle(_outputDescriptor);
}

void GraphicsEngine::renderPath(QVector<Point*> *path, const char texture) const
{
    for (int i = 0; i < path->size(); ++i) {
        renderPoint(path->at(i), texture);
    }
}

void GraphicsEngine::renderPoint(Point *point, const char texture) const
{
    COORD coord; 
    coord.X = point->X;
    coord.Y = point->Y;
    SetConsoleCursorPosition(_outputDescriptor, coord);
    std::cout << texture;
}

void GraphicsEngine::clearPoint(Point *point) const
{
    renderPoint(point, ' ');
}

void GraphicsEngine::cursorVisible(bool visible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = sizeof(CONSOLE_CURSOR_INFO);
    info.bVisible = visible;
    SetConsoleCursorInfo(_outputDescriptor, &info);
}
