//
//  Pieces.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Pieces.hpp"
#include "Field.hpp"

Piece::Piece(sf::Vector2f c_play_size, sf::Vector2f c_play_pos, int c_type){
    
    
    if(!m_texture.loadFromFile(resourcePath() + "blocks_2.png")){
        return EXIT_FAILURE;
    }
    
    switch (c_type) {
        case 1: // line
            this->m_positions = {{0.0f,1.0f},{1.0f,1.0f},{2.0f,1.0f},{3.0f,1.0f}};
            this->m_color = sf::Color(255,255,255);
            break;
        case 2: // T
            this->m_positions = {{0.0f,1.0f},{1.0f,1.0f},{2.0f,1.0f},{1.0f,2.0f}};
            this->m_color = sf::Color(255,200,10);
            break;
        case 3: // square
            this->m_positions = {{1.0f,1.0f},{2.0f,1.0f},{1.0f,2.0f},{2.0f,2.0f}};
            this->m_color = sf::Color(10,10,255);
            break;
        case 4: // S
            this->m_positions = {{1.0f,1.0f},{1.0f,2.0f},{2.0f,2.0f},{2.0f,3.0f}};
            this->m_color = sf::Color(255,10,10);
            break;
        case 5: // L
            this->m_positions = {{1.0f,1.0f},{2.0f,1.0f},{3.0f,1.0f},{3.0f,2.0f}};
            this->m_color = sf::Color(10,255,10);
            break;
        default:
            break;
    }
    
    this->m_block_size = {c_play_size.x/8,c_play_size.x/8};
    this->m_play_size = c_play_size;
    this->m_play_pos = c_play_pos;
    this->m_is_alive = false;
    
    int i {0};
    for(auto& pos: m_positions){
        sf::RectangleShape m_square;
        m_square.setSize(m_block_size*0.7f); // to fit "next box"
        m_square.setPosition({(pos.x*m_block_size.x*0.7f+c_play_size.x*1.20f),(pos.y*m_block_size.y*0.7f+c_play_pos.y*1.75f)});
        m_square.setFillColor(m_color);
        m_square.setTexture(&m_texture);
        m_square.setTextureRect(sf::IntRect(17+i*47,14,20,40));
        m_square.setOutlineColor(sf::Color::Black);
        m_square.setOutlineThickness(3.0f);
        m_squares.push_back(m_square);
        ++i;
    }
    for(auto square: m_squares){
        
    }

}

Piece::~Piece(){
    std::cout << "Piece destructor called" << std::endl;
}

void Piece::Activate_Piece(){
    m_is_alive = true;
    
    // move piece from "next box" to game board
    int i {0};
    for(auto& pos: m_positions){
        m_squares.at(i).setPosition({pos.x*m_block_size.x+m_play_pos.x,pos.y*m_block_size.y+m_play_pos.y});
        m_squares.at(i).setSize(m_block_size);
        ++i;
    }
}

std::vector<float> Piece::Get_piece_bounds(){
    
    std::vector<float> piece_bounds;
    float min_x {10000};
    float max_x {0};
    float max_y {0};
    
    for(auto& m_square: m_squares){
        if(m_square.getPosition().x < min_x) {min_x = m_square.getPosition().x;}
        if(m_square.getPosition().x+m_block_size.x > max_x) {max_x = m_square.getPosition().x;}
        if(m_square.getPosition().y+m_block_size.y > max_y) {max_y = m_square.getPosition().y+m_block_size.y;}
    }
    
    piece_bounds.push_back(min_x);
    piece_bounds.push_back(max_x);
    piece_bounds.push_back(max_y);
    
    return piece_bounds;
}

std::vector<sf::RectangleShape> Piece::Get_m_squares(){
    return m_squares;
}

bool Piece::Check_boundaries(float min_x, float max_x, sf::Vector2f c_move, Field* field){
    
    std::vector<float> piece_bounds = Get_piece_bounds();
    
    if(min_x+c_move.x*m_block_size.x <= m_play_pos.x-m_block_size.x ||
            max_x+c_move.x*m_block_size.x >= m_play_pos.x+m_play_size.x){
        return false;
    }else{
        return true;
    }
}

bool Piece::Check_bottom(float max_y, sf::Vector2f c_move, Field* field){
    
    if(max_y+c_move.y*m_block_size.y >= m_play_pos.y+m_play_size.y){
        return true;
    }else{
        return false;
    }
}

bool Piece::Check_status(){
    return m_is_alive;
}

void Piece::Move(sf::Vector2f c_move, Field* field){
    
    int coll_status {0};
    int index {0};
    bool print_data {false};
    
    std::vector<float> piece_bounds = Get_piece_bounds();
    
    for(auto& m_square: m_squares){
        coll_status = field->Collision(m_square,c_move,m_block_size);
        if(coll_status == 1 || coll_status == 2){
            break;
        }
        ++index;
    }
    
    if(coll_status==2 || Check_bottom(piece_bounds.at(2), c_move, field)){
        m_is_alive = false;
        for(auto& m_square: m_squares){
            m_square.move({c_move.x*m_block_size.x,c_move.y*m_block_size.y});
            field->Add_field(m_square);
        }
        field->CleanUp(m_block_size.y);
    }
    
    if(Check_boundaries(piece_bounds.at(0),piece_bounds.at(1),c_move,field) && m_is_alive && coll_status==0){
        for(auto& m_square: m_squares){
            m_square.move({c_move.x*m_block_size.x,c_move.y*m_block_size.y});
        }
    }
}

void Piece::Adjust_rotation(sf::Vector2f c_move){
// called when rotated piece ends up outside play area
    for(auto& m_square: m_squares){
        m_square.move({c_move.x,c_move.y});
    }
}

void Piece::Rotation_Outbound(){
    // adjusts piece if out of bounds after rotation
    
    std::vector<float> piece_bounds = Get_piece_bounds();
    
    if(piece_bounds.at(0) < m_play_pos.x){
        Adjust_rotation({m_play_pos.x-piece_bounds.at(0),0.0f});
    }else if(piece_bounds.at(1) > m_play_pos.x+m_play_size.x-m_block_size.x){
        Adjust_rotation({m_play_pos.x+m_play_size.x-piece_bounds.at(1)-m_block_size.x,0.0f});
    }else if(piece_bounds.at(2) > m_play_pos.y+m_play_size.y-m_block_size.y){
        Adjust_rotation({0.0f,m_play_pos.y+m_play_size.y-piece_bounds.at(2)-m_block_size.y});
    }
}

void Piece::Rotate(){
    if(m_is_alive){
        std::vector<sf::Vector2f> index {
            {0.0f,0.0f},{1.0f,0.0f},{2.0f,0.0f},{3.0f,0.0f},
            {0.0f,1.0f},{1.0f,1.0f},{2.0f,1.0f},{3.0f,1.0f},
            {0.0f,2.0f},{1.0f,2.0f},{2.0f,2.0f},{3.0f,2.0f},
            {0.0f,3.0f},{1.0f,3.0f},{2.0f,3.0f},{3.0f,3.0f},
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
}

void Piece::Draw(sf::RenderWindow& window){
    if(m_is_alive){
        for(auto& m_square: m_squares){
            window.draw(m_square);
        }
    }
}

void Piece::DrawNext(sf::RenderWindow& window){
    for(auto& m_square: m_squares){
        window.draw(m_square);
    }
}
