#include "world.h"

World::World()
{
    this->_width = 78;
    this->_height = 24;
    this->_commands = new QQueue<int>();
    this->_interactor = new Interactor(_commands);
    _defaultGameSetup();
}

World::World(unsigned int width, unsigned int height)
{
    this->_width = width;
    this->_height = height;
    _defaultGameSetup();
}

World::~World()
{
    for (unsigned int i = 0; i < _height; ++i) {
        delete [] _worldMatrix[i];
    }
    delete [] _worldMatrix;
    delete _timer;
}

void World::_defaultGameSetup()
{
    // this should be loaded form file in release.
        _wallTexture = '#';
        _foodTexture = '$';
        _spaceTexture = ' ';
        _delay = 50;
    //
    srand(time(NULL));
    _snake = new Snake(new Point(_width / 2, _height / 2)); // center.
    _gEngine = new GraphicsEngine();
    _gEngine->cursorVisible(false);
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(tick()));
    _timer->start(_delay);
    _interactor->start(); // start to listen to the user input.
}

void World::_handleCollisions()
{
    char object = _worldMatrix[_snake->headCoords->Y][_snake->headCoords->X];
    if(object == _foodTexture)
    {
        destroyObject(_snake->headCoords);
        _snake->feed();
        generateObject(FOOD);
    }
    ///add "fail" state to snake automaton
}

Point *World::_generateSafeCoords() const
{
    Point *coords = new Point();
    do
    {
        coords->X = rand() % (_width  - 1) + 1;
        coords->Y = rand() % (_height - 1) + 1;
    } while(_worldMatrix[coords->Y][coords->X] != _spaceTexture);
    return coords;
}

void World::generateObject(ObjectType oType)
{
    Point *coords = _generateSafeCoords();
    char objTexture;
    switch (oType) {
    case FOOD:
        objTexture = _foodTexture;
        break;
    case WALL:
        objTexture = _wallTexture;
        break;
    default:
        return;
    }
    _gEngine->renderPoint(coords, objTexture);
    _worldMatrix[coords->Y][coords->X] = objTexture;
    delete coords;
}

void World::destroyObject(Point *pt)
{
    _worldMatrix[pt->Y][pt->X] = _spaceTexture;
}

void World::tick()
{
    if(_commands->size() > 0){                       // do we have any commands?
        _snake->changeDirection(_commands->front()); // execute command.
        _commands->pop_front();                      // proceed to the next command.
    }
    _handleCollisions();
    _gEngine->renderPoint(_snake->tailCoords, _spaceTexture);
    _snake->move();
    _gEngine->renderPoint(_snake->getBodyCoords()->front(), _snake->getBodyTexture());
    _gEngine->renderPoint(_snake->headCoords, _snake->getHeadTexture());
 }

void World::render() const
{
    for (unsigned int i = 0; i < _height; ++i) {
        for (unsigned int j = 0; j < _width; ++j) {
            std::cout << _worldMatrix[i][j];
        }
        std::cout <<"\n";
    }
    _renderSnake();
}

void World::loadDefaultWorld()
{
    _worldMatrix = new char*[_height];
    for(unsigned int i = 0; i < _height; ++i){
        _worldMatrix[i] = new char[_width];
        for (unsigned int j = 0; j < _width; ++j) {
            _worldMatrix[i][j] = _spaceTexture;
        }
    }
    _createFrame();
}

void World::_createFrame() const
{
    for (unsigned int i = 0; i < _width; ++i) {
        _worldMatrix[0][i] = _wallTexture;
        _worldMatrix[_height - 1][i] = _wallTexture;
    }
    for (unsigned int i = 1; i < _height - 1; ++i) {
        _worldMatrix[i][0] = _wallTexture;
        _worldMatrix[i][_width - 1] = _wallTexture;
    }
}

void World::_renderSnake() const
{
    _gEngine->renderPoint(_snake->headCoords, _snake->getHeadTexture());
    for (int i = 0; i < _snake->getBodyCoords()->size(); ++i) {
        _gEngine->renderPoint(_snake->getBodyCoords()->at(i), _snake->getBodyTexture());
    }
}

Interactor::Interactor(QQueue<int> *cq)
{
    this->_commandsQueue = cq;
    this->loadCommands();
}

void Interactor::run()
{
    char key;
    do
    {
        key = getch();
        if(_avaliableCommands->contains(key))
            _commandsQueue->append(_avaliableCommands->value(key));
    } while (key != _avaliableCommands->end().key());
}

void Interactor::loadCommands()
{
    // TODO: load all this data from file!.
    _avaliableCommands = new QMap<char, int>();
    _avaliableCommands->insert('w', 0);
    _avaliableCommands->insert('s', 1);
    _avaliableCommands->insert('a', 2);
    _avaliableCommands->insert('d', 3);
    _avaliableCommands->insert('q', 4);
}
