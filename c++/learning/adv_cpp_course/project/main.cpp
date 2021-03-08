#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "Bitmap.hpp"
#include "Mandelbrot.hpp"

int main() {
    
    int const WIDTH = 800;
    int const HEIGHT = 800;
    Bitmap bitmap(WIDTH,HEIGHT);

    // bitmap.setPixel(WIDTH/2,HEIGHT/2,255,255,255);

    double min = 999999;
    double max = -999999;

    std::unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS + 1]{0});
    std::unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});

    for(int y = 0;y<HEIGHT;++y){
        for(int x = 0;x<WIDTH;++x){
            
            double xFractal = (x - WIDTH/2 - 200) * 2.0/WIDTH;
            double yFractal = (y - HEIGHT/2) * 2.0/HEIGHT;
            
            int iterations = Mandelbrot::getIterations(xFractal,yFractal);

            fractal[y*WIDTH+x] = iterations;

            if(iterations != Mandelbrot::MAX_ITERATIONS){
                histogram[iterations]++;
            }       
        }
    }

    int total=0;
    for(int i {0}; i<Mandelbrot::MAX_ITERATIONS;++i){
        total += histogram[i];
    }

    for(int y = 0;y<HEIGHT;++y){
        for(int x = 0;x<WIDTH;++x){

            uint8_t red {0};
            uint8_t green {0};
            uint8_t blue {0};

            int iterations = fractal[y*WIDTH+x];
            
            if(iterations != Mandelbrot::MAX_ITERATIONS){
                double hue = 0.0;
                for(int i=0; i <= iterations;++i){
                    hue += ((double)histogram[i])/total;
                }
                green = pow(255,hue);
            }
            
            red = 0;
            blue = 0;

            bitmap.setPixel(x,y,red,green,blue);

        }
    }
    
    bitmap.write("test.bmp");

    std::cout << "finished." << std::endl;
    return 0;
}