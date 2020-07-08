// class Piece header file - defines the actual playing falling pieces on the game board
// each piece contains 6 coordinates in 3 vectors: initial positions, actual positions and 4x4 matrix defining rotation status

#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <string>
#include <vector>

class Piece {

private:

    std::vector<int> y_init {}; // initial position of the piece
    std::vector<int> x_init {};
    std::vector<int> y_shape {}; // current position of the piece
    std::vector<int> x_shape {};
    std::vector<int> rot_y {}; // 4x4 matrix used to rotate the piece
    std::vector<int> rot_x {};

public:
    //constructors
    Piece();
    Piece(std::vector<int>,std::vector<int>, std::vector<int>,std::vector<int>,
                        std::vector<int>,std::vector<int>);
    Piece(const Piece &source);
    ~Piece();
    
    //get functions
    std::vector<int> get_y_init() {return y_init;};
    std::vector<int> get_x_init() {return x_init;};
    std::vector<int> get_y_shape() {return y_shape;};
    std::vector<int> get_x_shape() {return x_shape;};
    std::vector<int> get_rot_y() {return rot_y;};
    std::vector<int> get_rot_x() {return rot_x;};

    //function prototypes
    void update_y_shape(int y, int i);
    void update_x_shape(int x, int i);
    void update_rot_y(int y, int i);
    void update_rot_x(int x, int i);
    void reset_position(std::vector<int> y_init, std::vector<int> x_init, int i);
    void reset_rotation(std::vector<int> y_init, std::vector<int> x_init, int y, int x,int i);

};

Piece::Piece() 
    :y_init{3,3,2,1},
    x_init{2,1,1,1},
    y_shape{3,3,2,1},
    x_shape{2,1,1,1},
    rot_y{3,3,2,1},
    rot_x{2,1,1,1} {}

Piece::Piece(std::vector<int> y_init,std::vector<int> x_init, 
            std::vector<int> y_shape,std::vector<int> x_shape,
            std::vector<int> rot_y, std::vector<int> rot_x)
    :y_init{y_init},
    x_init{x_init},
    y_shape{y_shape},
    x_shape{x_shape},
    rot_y{rot_y},
    rot_x{rot_x} {}

Piece::Piece(const Piece &source)
       : Piece {source.y_init, source.x_init, source.y_shape, source.x_shape, source.rot_y, source.rot_x}  {}

void Piece::update_rot_y(int y, int i) {
    rot_y[i] += y;
}

void Piece::update_rot_x(int x, int i) {
    rot_x[i] += x;
}

void Piece::update_y_shape(int y, int i) {
    y_shape[i] += y;
}

void Piece::update_x_shape(int x, int i) {
    x_shape[i] += x;
}

void Piece::reset_position(std::vector<int> y_init, std::vector<int> x_init, int i) {
    y_shape[i] = y_init[i];
    x_shape[i] = x_init[i];
}

void Piece::reset_rotation(std::vector<int> y_init, std::vector<int> x_init, int y_start, int x_start, int i) {
    rot_y[i] = y_init[i]-y_start;
    rot_x[i] = x_init[i]-x_start;
}

Piece::~Piece() {}

#endif
