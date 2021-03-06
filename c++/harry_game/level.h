// default level boundaries

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "object.h"

class Level {
private:
    float floor;
    float left_b;
    float right_b;
public:
    Level();
    ~Level();
    float getFloor() {return floor;};
    float getLeft_b() {return left_b;};
    float getRight_b() {return right_b;};
};

Level::Level(){
// level boundaries set here for now
    floor = 550.0f;
    left_b = -150.0f;
    right_b = 5000.0f;
}
Level::~Level(){}

#endif