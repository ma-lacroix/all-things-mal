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
    char ch1 [2] {};
    char ch2 [2] {};
public:
    //constructors
    Piece();
    Piece(std::vector<int>,std::vector<int>, std::vector<int>,std::vector<int>);
    Piece(const Piece &source);
    ~Piece();
    
    //function prototypes
};

Piece::Piece() 
    :y_init{3,3,2,1},
    x_init{2,1,1,1},
    y_shape{3,3,2,1},
    x_shape{2,1,1,1},
    ch1{'#'},
    ch2{'@'} {}

Piece::Piece(std::vector<int> y_init,std::vector<int> x_init, 
            std::vector<int> y_shape,std::vector<int> x_shape)
    :y_init{y_init},
    x_init{x_init},
    y_shape{y_shape},
    x_shape{x_shape},
    ch1{'#'},
    ch2{'@'} {}

Piece::~Piece() {}

#endif