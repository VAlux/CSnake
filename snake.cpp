#include "snake.h"

Snake::Snake()
{
    this->_tailTexture = 'o';
    this->_headTexture = 'O';
    this->_length = 4;
    this->_curMovState = recognizeDirection(3); // default direction -- RIGHT
    createMovingMatrix();
}

Snake::Snake(Point *headCoords) : Snake()
{
    _bodyCoords = new QVector<Point*>();
    this->headCoords = headCoords;
    for (unsigned int i = 1; i < _length; ++i) {
        _bodyCoords->push_back(new Point(headCoords->X - _curMovState.direction->X * i,
                                         headCoords->Y - _curMovState.direction->Y * i));
    }
    tailCoords = _bodyCoords->back();
}

Snake::~Snake()
{
    for (int i = 0; i < MM_HEIGHT; ++i) {
        delete [] _movingMatrix[i];
    }
    delete [] _movingMatrix;
    qDeleteAll(*_bodyCoords);
}

void Snake::changeDirection(const short index)
{
    _curMovState = _movingMatrix[index][_curMovState.index];
}

void Snake::createMovingMatrix()
{
    /**
      0 -- UP
      1 -- DOWN
      2 -- LEFT
      3 -- RIGHT
      */
    short stateMatr[MM_HEIGHT][MM_WIDTH] = {
        {0, 1, 0, 0},
        {0, 1, 1, 1},
        {2, 2, 2, 3},
        {3, 3, 2, 3}
    };

    this->_movingMatrix = new MovingState*[MM_HEIGHT];
    for (int i = 0; i < MM_HEIGHT; ++i) {
        this->_movingMatrix[i] = new MovingState[MM_WIDTH];
        for (int j = 0; j < MM_WIDTH; ++j) {
            this->_movingMatrix[i][j] = recognizeDirection(stateMatr[i][j]);
        }
    }
}

MovingState Snake::recognizeDirection(const short index)
{
    switch(index){
        case 0: return MovingState(new Point(0, -1), index);
        case 1: return MovingState(new Point(0,  1), index);
        case 2: return MovingState(new Point(-1, 0), index);
        case 3: return MovingState(new Point(1,  0), index);
        default: return MovingState(new Point(), ERR_INDEX);
    }
}


void Snake::move()
{
    _bodyCoords->push_front(new Point(headCoords->X, headCoords->Y));
    delete _bodyCoords->back();
    _bodyCoords->pop_back();
    tailCoords = _bodyCoords->back();
    headCoords->move(_curMovState.direction);
}

void Snake::feed()
{
    Point *lastSeg = new Point(tailCoords->X, tailCoords->Y);
    move();
    _bodyCoords->push_back(lastSeg);
    tailCoords = lastSeg;
}
