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
    void erase_line(int,int);
    void push_y(int);
    void push_x(int);
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

// example of y and x for debugging purposes
// y {1,1,1,3,3,2,2,1,1,1}
// x {1,2,3,1,2,1,2,4,5,6}

void Objects::erase_line(int size_y,int size_x) {
// when a line is complete, remove it from the board
    
    int counter {0};
    std::vector<size_t> temp_vec {};
    for (int j {0};j<(size_y-2);++j) {
        for (size_t i {0};i<size(y);++i) {
            if (y[i]==j) {
                ++counter;
                if(counter==(size_x-2)) {
                    temp_vec.push_back(j);    
                    }
                }
            }
        counter = 0;
        }
    if (size(temp_vec)>0) {
        for (size_t l {0};l<size(temp_vec);++l) {
            for (size_t k {0};k<size(y);++k){
                if (y[k]==temp_vec[l]) {
                    y.erase(y.begin()+k);
                    x.erase(x.begin()+k);
                    }
                }
            }
        }
    temp_vec.clear();
    
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