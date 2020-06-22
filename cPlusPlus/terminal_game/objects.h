// class Objects header file - holds coordinates of fallen objects in game window

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <iostream>
#include <string>
#include <vector>

class Objects {

private:
    std::vector<int> y;
    std::vector<int> x;
public:
    //constructors
    Objects();
    Objects(std::vector<int> y_values, std::vector<int> x_values);
    Objects(const Objects &source);
    ~Objects();
    
    //function prototypes
    std::vector<int> get_y() {return y;};
    std::vector<int> get_x() {return x;};
    void push_y(int new_y);
    void push_x(int new_x);
};

Objects::Objects()
    :y{},x{} {}

Objects::Objects(std::vector<int> y_values, std::vector<int> x_values) 
    :y{y_values},x{x_values} {}

void Objects::push_y(int new_y){
// if a piece falls at the bottom of the board - update the y coordinates of fallen objects
    y.push_back(new_y);
}

void Objects::push_x(int new_x){
// if a piece falls at the bottom of the board - update the x coordinates of fallen objects
    x.push_back(new_x);
}

Objects::~Objects() {}

#endif