#include <iostream>

//#include "glm.hpp"
#include "image/image.hpp"
//#include "test/test.hpp"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"



int main() {
	Image image(640, 480);
	
	for (unsigned int x = 0; x < image.width; x++) {
		for (unsigned int y = 0; y < image.height; y++) {
			if (x < image.width/3) {
				image.data[x][y] = glm::vec4(0.0, 0.0, 1.0, 1.0);
			} else if (image.width/3 <= x && x < (2*image.width)/3) {
				image.data[x][y] = glm::vec4(1.0, 1.0, 1.0, 1.0);
			} else {
				image.data[x][y] = glm::vec4(1.0, 0.0, 0.0, 1.0);
			}
		}
	}
	
	image.save("test.png");
	
	std::cout << "yes" << std::endl;
	
	return 0;
}