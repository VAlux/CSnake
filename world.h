#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include <QString>
#include <QPair>
#include <QTimer>
#include <QThread>
#include <QMap>
#include <QtCore>

#include <graphicsengine.h>
#include <snake.h>

enum ObjectType {
    WALL,
    FOOD,
    BONUS
};

class Interactor : public QThread
{
public:
    Interactor(QQueue<int> *cq);
    void run();

private:
    QQueue<int> *_commandsQueue;
    QMap<char, int> *_avaliableCommands;
    void loadCommands();
};

class World : public QObject
{
    Q_OBJECT

public:
    World();
    World(unsigned int width, unsigned int height);
    ~World();
    void loadFromFile(const QString path); // TODO: implement later.
    void render() const;
    void loadDefaultWorld();
    void generateObject(ObjectType oType);
    void destroyObject(Point *pt);
    QPair<int, int> getSize() const;

private:
    //fields:
    int             _delay;
    unsigned int    _width;
    unsigned int    _height;
    char          **_worldMatrix;
    char            _wallTexture;
    char            _foodTexture;
    char            _spaceTexture;
    Snake          *_snake;
    GraphicsEngine *_gEngine;
    QTimer         *_timer;
    QQueue<int>    *_commands;
    Interactor     *_interactor;

    //methods:
    void    _renderSnake() const;
    void    _createFrame() const;
    void    _defaultGameSetup();
    void    _handleCollisions();
    Point  *_generateSafeCoords() const;

private slots:
    void tick();
};


#endif // WORLD_H
