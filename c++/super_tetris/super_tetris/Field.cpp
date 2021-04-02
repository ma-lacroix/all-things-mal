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

void Field::ResetInventory(){
    m_inventory.clear();
    for(auto square: m_field){
        std::map<float,int>::iterator it = m_inventory.find(square.getPosition().y);
        if(it!=m_inventory.end()){
            it->second++;
            std::cout << "Current: " << it->first << " " << it->second << std::endl;
        }else{
            m_inventory.insert(std::make_pair(square.getPosition().y,1));
            std::cout << "Creating: " << square.getPosition().y << std::endl;
        }
    }
}

void Field::DropLines(float c_block_y){
    std::cout << "dropping lines" << std::endl;
    for(auto line: m_complete_lines){
        for(size_t i{0};i<m_field.size();++i){
            if(m_field.at(i).getPosition().y<line){
                
                std::cout << "Match: " << m_field.at(i).getPosition().x << " " << m_field.at(i).getPosition().y << std::endl;
                m_field.at(i).move(0.0f,c_block_y);
                std::cout << "Moved: "  << m_field.at(i).getPosition().x << " " << m_field.at(i).getPosition().y << std::endl;
            }
        }
    }
}

void Field::EraseLines(float c_block_y){
    
    // O(g(x)) massively unoptimised search and find algorithm!
    
    for(auto c_line_index: m_complete_lines){
        std::cout << "c line: " << c_line_index << std::endl;
        for(size_t i = m_field.size()-1;i>0;--i){
            if(m_field.at(i).getPosition().y==c_line_index){
                m_field.erase(m_field.begin()+i);
            }
        }
        for(size_t i {0};i<m_field.size();++i){
            if(m_field.at(i).getPosition().y==c_line_index){
                m_field.erase(m_field.begin()+i);
            }
        }
    }
}

void Field::CheckLines(float c_block_y){
    
    for(std::map<float,int>::iterator it = m_inventory.begin();it!=m_inventory.end();++it){
        std::cout << it->first << " " << it->second << std::endl;
        if(it->second >= 8){
            std::cout << "Line " << it->first << " if full! " << std::endl;
            m_complete_lines.push_back(static_cast<int>(it->first));
        }
    }
}

void Field::CleanUp(float c_block_y){
    
    ResetInventory();
    m_complete_lines.clear();
    CheckLines(c_block_y);
    
    if(m_complete_lines.size()>0){
        EraseLines(c_block_y);
        DropLines(c_block_y);
    }
}

void Field::Add_field(sf::RectangleShape c_rect){
    m_field.push_back(c_rect);
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
