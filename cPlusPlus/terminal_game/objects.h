// class Objects header file - holds coordinates of objects in game window

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <iostream>
#include <string>

class Object {
private:
    int y;
    int x;
public:
    //constructors
    Object();
    Object(int y_value, int x_value);
    Object(const Object &source);
    ~Object();
    
    //functions
    int get_y() {return y;};
    int get_x() {return x;};
};

Object::Object()
    :y{1},x{1} {}

Object::Object(int y_value, int x_value) 
    :y{y_value},x{x_value} {}

Object::~Object() {}

#endif