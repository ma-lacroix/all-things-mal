//
//  Pieces.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Pieces.hpp"

Piece::Piece(sf::Vector2f c_play_size, sf::Vector2f c_play_pos,std::vector<sf::Vector2f> c_initial_pos,sf::Color c_color){
    
    std::cout << "Piece constructor called" << std::endl;
    
    this->m_block_size = {c_play_size.x/10,c_play_size.x/10};
    this->m_color = c_color;
    this->m_positions = c_initial_pos;
    this->m_play_size = c_play_size;
    this->m_play_pos = c_play_pos;
    
    for(auto& pos: m_positions){
        sf::RectangleShape m_square;
        m_square.setSize(m_block_size);
        m_square.setPosition({pos.x*m_block_size.x+c_play_pos.x,pos.y*m_block_size.y+c_play_pos.y});
        m_square.setFillColor(m_color);
        m_squares.push_back(m_square);
    }
}

Piece::~Piece(){
    std::cout << "Piece destructor called" << std::endl;
}

std::vector<float> Piece::Get_piece_bounds(){
    
    std::vector<float> piece_bounds;
    float min_x {10000};
    float max_x {0};
    float max_y {0};
    
    for(auto& m_square: m_squares){
        if(m_square.getPosition().x < min_x) {min_x = m_square.getPosition().x;}
        if(m_square.getPosition().x+m_block_size.x > max_x) {max_x = m_square.getPosition().x;}
        if(m_square.getPosition().y+m_block_size.y > max_y) {max_y = m_square.getPosition().y;}
    }
    
    piece_bounds.push_back(min_x);
    piece_bounds.push_back(max_x);
    piece_bounds.push_back(max_y);
    
    return piece_bounds;
}

bool Piece::Check_boundaries(sf::Vector2f c_move){
    
    std::vector<float> piece_bounds = Get_piece_bounds();
    
    if(piece_bounds.at(0)+c_move.x*m_block_size.x <= m_play_pos.x-m_block_size.x ||
       piece_bounds.at(1)+c_move.x*m_block_size.x > m_play_pos.x+m_play_size.x ||
       piece_bounds.at(2)+c_move.y*m_block_size.y > m_play_pos.y+m_play_size.y-m_block_size.y){
        return false;
    }else{
        return true;
    }
}
bool Piece::Check_bottom(){
    
}

void Piece::Move(sf::Vector2f c_move){
    if(Check_boundaries(c_move)){
        for(auto& m_square: m_squares){
            m_square.move({c_move.x*m_block_size.x,c_move.y*m_block_size.y});
        }
    }
}

void Piece::Adjust_rotation(sf::Vector2f c_move){
    for(auto& m_square: m_squares){
        m_square.move({c_move.x,c_move.y});
    }
}

void Piece::Rotation_Outbound(){
    // adjusts piece if out of bounds after rotation
    
    std::vector<float> piece_bounds = Get_piece_bounds();
    
    if(piece_bounds.at(0) < m_play_pos.x){
        std::cout << "case 1" << std::endl;
        Adjust_rotation({m_play_pos.x-piece_bounds.at(0),0.0f});
    }else if(piece_bounds.at(1) > m_play_pos.x+m_play_size.x-m_block_size.x){
        std::cout << "case 2" << std::endl;
        Adjust_rotation({m_play_pos.x+m_play_size.x-piece_bounds.at(1)-m_block_size.x,0.0f});
    }else if(piece_bounds.at(2) > m_play_pos.y+m_play_size.y-m_block_size.y){
        std::cout << "case 3" << std::endl;
        Adjust_rotation({0.0f,m_play_pos.y+m_play_size.y-piece_bounds.at(2)-m_block_size.y});
    }
}

void Piece::Rotate(){
    std::vector<sf::Vector2f> index {
        {0.0f,0.0f},{0.0f,1.0f},{0.0f,2.0f},{0.0f,3.0f},
        {1.0f,0.0f},{1.0f,1.0f},{1.0f,2.0f},{1.0f,3.0f},
        {2.0f,0.0f},{2.0f,1.0f},{2.0f,2.0f},{2.0f,3.0f},
        {3.0f,0.0f},{3.0f,1.0f},{3.0f,2.0f},{3.0f,3.0f},
    };
    // 0 degrees => i = y*4+x
    // 90 degrees =>  i = 12+y-(x*4)
    int i {0};
    sf::Vector2f rotations;
    for(auto m_pos: m_positions){
        int ind1 = static_cast<int>(12.0f+m_pos.y-m_pos.x*4);
        int ind2 = static_cast<int>(m_pos.y*4+m_pos.x);
        rotations.x = index.at(ind1).x-index.at(ind2).x;
        rotations.y = index.at(ind1).y-index.at(ind2).y;
        m_positions.at(i) = index.at(ind1);
        m_squares.at(i).move({rotations.x*m_block_size.x,rotations.y*m_block_size.y});
        ++i;
    }
    Rotation_Outbound();
}

void Piece::Draw(sf::RenderWindow& window){
    for(auto& m_square: m_squares){
        window.draw(m_square);
    }
}
