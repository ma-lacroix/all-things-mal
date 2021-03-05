#ifndef BITMAPFILEHEADER_H
#define BITMAPFILEHEADER_H

#include<iostream>
#include<cstdint>

// #pragma pack(2)

struct Bitmapfileheader{
	char header[2]{'B','M'};
	int32_t fileSize;
	int32_t reserved{0};
	int32_t dataOffset;

};
#endif