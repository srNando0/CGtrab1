#include <iostream>

//#include "glm.hpp"
#include "image/image.hpp"
//#include "test/test.hpp"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"



int main() {
	Image image(640, 480);
	
	for (unsigned int x = 0; x <= image.getWidth(); x++) {
		for (unsigned int y = 0; y <= image.getHeight(); y++) {
			/*if (x < image.getWidth()/3) {
				image.mData[x][y] = glm::vec4(0.0, 0.0, 1.0, 1.0);
			} else if (image.getWidth()/3 <= x < 2*image.getWidth()/3) {
				image.mData[x][y] = glm::vec4(1.0, 1.0, 1.0, 1.0);
			} else {
				image.mData[x][y] = glm::vec4(1.0, 0.0, 0.0, 1.0);
			}*/
			//image.mData[x][y] = glm::vec4(1.0, 0.0, 0.0, 1.0);
		}
	}
	
	image.mData[0][0] = glm::vec4(1.0, 0.0, 0.0, 1.0);
	
	image.save("test.png");
	
	std::cout << image.mData[0][0].x << std::endl;
	
	return 0;
}