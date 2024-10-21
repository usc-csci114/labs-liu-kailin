#include <iostream>
#include "bmplib.h"
#include "shapes.h"

using namespace std;

uint8_t*** newImage(uint8_t bground[3], uint32_t h, uint32_t w)
{
	uint8_t*** img = new uint8_t**[h];
	for(int r=0; r < h; r++) {
		img[r] = new uint8_t*[w];
		for(int c = 0; c < w; c++) {
			img[r][c] = new uint8_t[3];
			img[r][c][0] = bground[0];
			img[r][c][1] = bground[1];
			img[r][c][2] = bground[2];
		}
	}
	return img;
}

// helper function to print instructions
void instructions(){
	cout << "What kind of shape would you like to draw?" << endl;
	cout << "For a Triangle, enter T." << endl;
	cout << "For a Circle, enter C." << endl;
	cout << "For a Rectangle, enter R." << endl;
	cout << "To exit this program, enter 'quit'. " << endl;
}


int main(int argc, char* argv[])
{
	// intializes image with certain background color
	uint8_t bg[] = {255,255,255};
	uint8_t*** image = newImage(bg, 1024, 1024);
	
	//add your code here
	
	//ask the user what shape the want to draw
	//collect the required information
	//instantiate the shape, draw it into the image
	//loop and ask for another shape, "quit" to stop

	string type;
	instructions();
	cin >> type;

	bool print = true; // stays true unless an invalid input is entered
						// prevents printing empty image

	while( type != "quit") {
		// triangle
		if (type == "T") {
			Point vertices[3];
            Color red = {255, 0, 0};
            cout << "Enter the coordinates for the triangle" << endl;
			cout << "Please follow the format of ' x1 y1 x2 y2 x3 y3 ' separated by spaces" << endl;
            cin >> vertices[0].x >> vertices[0].y 
				>> vertices[1].x >> vertices[1].y 
				>> vertices[2].x >> vertices[2].y;
            Triangle T(vertices, red);
            T.draw(image, 1024, 1024);
		}
		// circle
		else if (type == "C") {
			Point center;
            Color green = {0, 255, 0};
            int radius;
            cout << "Enter the center coordinates and radius" << endl;
			cout << "Please follow the format of ' x y r ' separated by spaces" << endl;
            cin >> center.x >> center.y >> radius;
            Circle C(center, radius, green);
            C.draw(image, 1024, 1024);
		}
		// rectangle
		else if (type == "R"){
			Point topLeft, bottomRight;
			Color blue = {0, 0, 255}; 
			cout << "Enter the coordinates for the top-left and bottom-right corners of the rectangle" << endl;
			cout << "Please follow the format of 'x1 y1 x2 y2' separated by spaces" << endl;
			cin >> topLeft.x >> topLeft.y 
				>> bottomRight.x >> bottomRight.y;
			Rectangle R(topLeft, bottomRight, blue);
			R.draw(image, 1024, 1024); 
		
		}
		// other
		else {
			cout << "Invalid shape! Please try again." << endl;
			print = false; 
		}
	}
	
	if (print){
		writeRGBBMP("output.bmp", image, 1024, 1024);
	}
	else {
		instructions();
	}

	instructions();
	cin >> type;
}
