#ifndef APPLICATION_H
#define APPLICATION_H

#include "Node.h"

class Application : public Node
{
public:
    Application();
    bool isRunning();
    void update(float deltaTime);
    void draw();
private:
    bool running;
};

#endif