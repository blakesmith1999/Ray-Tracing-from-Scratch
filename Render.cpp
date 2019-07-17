#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

void render() {
  const int width = 1024;
  const int height = 768;
  const float fov = M_PI/3.;
  std::vector<Vec3f> framebuffer(width*height);
  
  #pragma omp parallel for
  for (size_t j =0; j<height; j++) {
    for (size_t i = 0; i<width; i++) {
      float dir_x =(i+0.5)-width/2.;
      float dir_y =-(j+0.5)+height/2.;
      float dir_z = -height/(2.*tan(fov/2));
      framebuffer[i+j*width] =cast_ray(Vec3f(dir_x, dir_y, dir_z).normalize(), spheres, lights);
    }
  }
  
  std::ofstream ofs;
  ofs.open("./out.ppm");
  ofs<<"P6\n"<<width<<" "<<height<<"\n255\n";
  for (size_t i = 0; i<height*width; ++i) {
    for (size_t j =0; j<3; j++) {
      ofs<<(char)(255*std::max(0.f, std::min(1.f, framebuffer[i][j])));
    }
  }
  ofs.close();
}

int main() {
  render();
  return 0;
}
