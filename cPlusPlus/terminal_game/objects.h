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
    void reset(std::vector<int>,std::vector<int>);
    void erase_line(int);
    void push_y(int new_y);
    void push_x(int new_x);
};

Objects::Objects()
    :y{},x{} {}

Objects::Objects(std::vector<int> y_values, std::vector<int> x_values) 
    :y{y_values},x{x_values} {}


void Objects::reset(std::vector<int>new_y,std::vector<int>new_x) {
// reset the board - used when game is quit
    y = new_y;
    x = new_x;
}

void Objects::erase_line(int max){
// when a line is complete, remove it from the board
    int counter {0};
    std::vector<int> new_y;
    std::vector<int> new_x;

    for (int j {0};j<size(y);++j) {
        for (size_t i {0};i<size(y);++i){
            if (y[i]==j) {
                counter++;    
            }
        if (counter==max-2){ // size x of playable surface
            for (size_t k {0};i<size(y);++k){
                if (y[k]==j){
                    y.erase(y.begin()+k);
                    x.erase(x.begin()+k);
                    }
                }
            }
        }
        counter = 0;
    }
}

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