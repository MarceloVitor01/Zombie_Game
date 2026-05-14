#ifndef COMMAND_H
#define COMMAND_H

#include "Vec2.h"

enum CommandType
{
    MOVE,
    SHOOT
};

class Command
{
public:
    Command(CommandType type, float x, float y);

    CommandType type;
    Vec2 pos;
};

#endif