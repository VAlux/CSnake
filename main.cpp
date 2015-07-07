#include <QCoreApplication>
#include <world.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    World world;
    world.loadDefaultWorld();
    world.render();
    world.generateObject(FOOD);
    return a.exec();
}
