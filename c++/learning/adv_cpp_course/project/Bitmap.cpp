#include "Bitmap.hpp"  
#include "Bitmapfileheader.h"
#include "Bitmapinfoheader.h"

Bitmap::Bitmap(int width, int height)
    :m_width(width),m_height(height),m_pPixel(new uint8_t[width*height*3]){
	std::cout << "constructor called" << std::endl;
}
	
Bitmap::~Bitmap(){
    std::cout << "destructor called" << std::endl;
} 

bool Bitmap::write(std::string filename){
    Bitmapfileheader fileheader;
    Bitmapinfoheader infoheader;

    fileheader.fileSize = sizeof(Bitmapfileheader) + sizeof(Bitmapinfoheader) + m_height*m_width*3;
    fileheader.dataOffset = sizeof(Bitmapfileheader) + sizeof(Bitmapinfoheader);

    infoheader.width = m_width;
    infoheader.height = m_height;
    
    std::ofstream file;

    file.open(filename,std::ios::out|std::ios::binary);

    if(!file){
        return false;
    }

    file.write((char *)&fileheader,sizeof(fileheader));
    file.write((char *)&infoheader,sizeof(infoheader));
    file.write((char *)m_pPixel.get(),m_width*m_height*3);

    file.close();

    return true;
}

bool Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green,uint8_t blue){
    uint8_t *pPixel = m_pPixel.get();
    pPixel += (y*3) * m_width + (x*3);
    pPixel[0] = blue;
    pPixel[0] = green;
    pPixel[0] = red;
    
    return false;
}