// class Piece header file - defines the actual playing falling pieces on the game board
// each piece contains 4 coordinates in 2 vectors

#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <string>
#include <vector>

class Piece {

private:

    std::vector<int> y_init {};
    std::vector<int> x_init {};
    std::vector<int> y_shape {};
    std::vector<int> x_shape {};

public:
    //constructors
    Piece();
    Piece(std::vector<int>,std::vector<int>, std::vector<int>,std::vector<int>);
    Piece(const Piece &source);
    ~Piece();
    
    //get functions
    std::vector<int> get_y_init() {return y_init;};
    std::vector<int> get_x_init() {return x_init;};
    std::vector<int> get_y_shape() {return y_shape;};
    std::vector<int> get_x_shape() {return x_shape;};

    //function prototypes
    void update_y_shape(int y, int i);
    void update_x_shape(int x, int i);

};

Piece::Piece() 
    :y_init{3,3,2,1},
    x_init{2,1,1,1},
    y_shape{3,3,2,1},
    x_shape{2,1,1,1} {}

Piece::Piece(std::vector<int> y_init,std::vector<int> x_init, 
            std::vector<int> y_shape,std::vector<int> x_shape)
    :y_init{y_init},
    x_init{x_init},
    y_shape{y_shape},
    x_shape{x_shape} {}

Piece::Piece(const Piece &source)
       : Piece {source.y_init, source.x_init, source.y_shape, source.x_shape}  {}

void Piece::update_y_shape(int y, int i) {
    y_shape[i] += y;
}

void Piece::update_x_shape(int x, int i) {
    x_shape[i] += x;
}

Piece::~Piece() {}

#endif