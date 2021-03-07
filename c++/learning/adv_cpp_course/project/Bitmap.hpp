#ifndef BITMAP_H
#define BITMAP_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>

class Bitmap{
	private:
		int m_width{0};
		int m_height{0};
		std::unique_ptr<uint8_t[]> m_pPixel{nullptr};
	public:
		Bitmap(int width, int heigth);
		~Bitmap();
		bool write(std::string filename);
		bool setPixel(int x, int y, uint8_t red, uint8_t green,uint8_t blue);

};
#endif