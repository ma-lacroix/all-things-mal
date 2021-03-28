//
//  Field.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 25/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Field.hpp"

Field::Field(){
    std::cout<< "Field constructor called" << std::endl;
}

Field::~Field(){
    std::cout<< "Field destructor called" << std::endl;
}

void Field::Add_field(sf::RectangleShape c_rect){
    m_field.push_back(c_rect);
}

void Field::Print(){
}

int Field::Collision(sf::RectangleShape c_rect,sf::Vector2f c_move, sf::Vector2f c_block){
// 0 = no collision, 1 = lateral collision, 2 = vertical collision
    int result {0};
    
    float c_x_s = static_cast<int>(c_rect.getPosition().x+c_move.x*c_block.x);
    float c_x_e = static_cast<int>(c_rect.getSize().x+c_x_s);
    float c_y_s = static_cast<int>(c_rect.getPosition().y+c_move.y*c_block.y);
    float c_y_e = static_cast<int>(c_rect.getSize().y+c_y_s);
    
//    std::cout << "c_x_e: " << (c_x_e/c_block.x) << std::endl;
//    std::cout << "c_y_e: " << (c_y_e/c_block.x) << std::endl;
    
    for(auto square: m_field){
        // get field boundaries
        float f_x_s = static_cast<int>(square.getPosition().x);
        float f_x_e = static_cast<int>(square.getSize().x+f_x_s);
        float f_y_s = static_cast<int>(square.getPosition().y);
        float f_y_e = static_cast<int>(square.getSize().y+f_y_s);

        // get c_rect boundaries
        
            
//        std::cout << "f_x_e: " << static_cast<int>(f_x_e/c_block.x) << std::endl;
//        std::cout << "f_y_e: " << static_cast<int>(f_y_e/c_block.x) << std::endl;
        
        if(c_x_s == f_x_s && c_y_e == f_y_s){
            
            if(c_move.x!=0){
//                std::cout << "lateral collision" << std::endl;
//                std::cout << "f_x_e: " << static_cast<int>(f_x_e/c_block.x) << std::endl;
//                std::cout << "c_x_e: " << static_cast<int>(c_x_e/c_block.x) << std::endl;
//                std::cout << "f_y_e: " << static_cast<int>(f_y_e/c_block.x) << std::endl;
//                std::cout << "c_y_e: " << static_cast<int>(c_y_e/c_block.x) << std::endl;
                result+=1;
                break;
            }
            if(c_move.y!=0){
//                std::cout << "bottom collision" << std::endl;
//                std::cout << "f_x_e: " << static_cast<int>(f_x_e/c_block.x) << std::endl;
//                std::cout << "c_x_e: " << static_cast<int>(c_x_e/c_block.x) << std::endl;
//                std::cout << "f_y_e: " << static_cast<int>(f_y_e/c_block.x) << std::endl;
//                std::cout << "c_y_e: " << static_cast<int>(c_y_e/c_block.x) << std::endl;
                result+=2;
                break;
            }
        }
    }
    std::cout << " " << std::endl;
    return result;
}
void Field::Draw(sf::RenderWindow& window){
    for(auto square: m_field){
        window.draw(square);
    }
}
