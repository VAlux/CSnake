#ifndef SNAKE_H
#define SNAKE_H

#define MM_HEIGHT 4
#define MM_WIDTH 4
#define ERR_INDEX 4

#include <QPair>
#include <QVector>
#include <graphicsengine.h>

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct MovingState{
    Point *direction;
    unsigned short index;

    MovingState(){
        this->direction = new Point();
        this->index = ERR_INDEX;
    }

    MovingState(Point *direction, const short index){
        this->direction = direction;
        this->index = index;
    }
};

class Snake
{
public:
    Snake();
    Snake(Point *headCoords);
    ~Snake();
    int getLength() const { return _length; }
    void changeDirection(const short index);
    void move();
    void feed();
    bool isIntersecting(const Point *pt) const;
    char getBodyTexture() const { return _tailTexture; }
    char getHeadTexture() const { return _headTexture; }

    Point *headCoords;
    Point *tailCoords;
    QVector<Point*> *getBodyCoords() const { return _bodyCoords; }

private:
    MovingState **_movingMatrix;
    MovingState   _curMovState;
    QVector<Point*> *_bodyCoords;
    unsigned int _length;
    char _tailTexture;
    char _headTexture;

    void createMovingMatrix();
    MovingState recognizeDirection(const short index);
};

#endif // SNAKE_H
