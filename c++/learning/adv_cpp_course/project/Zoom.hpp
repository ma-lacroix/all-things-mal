#include <iostream>

#ifndef ZOOM_H
#define ZOOM_H
#pragma once
	
struct Zoom{

	int x {0};
	int y {0};
	double scale {0.0};
	Zoom(int x, int y, double scale)
			:x(x),y(y),scale(scale){
				std::cout << "Zoom class called" << std::endl;
			};
	~Zoom();

};

#endif