#ifndef DRAWING_H
#define DRAWING_H

#include "bmplib.h"
#include <string>
#include <vector>

using namespace std;

//Define your structs/classes in this file

struct Point {
	double x, y;
};
// Helper function (provided by the lab) 
vector<Point> plotLine(Point start, Point end);

struct ColorPixel {
	uint8_t red, green, blue;
};

class ColorImage {
	public:
		ColorImage(uint32_t xdim, uint32_t ydim); // constructor
		void setPixel(ColorPixel p, uint32_t x, uint32_t y);
		ColorPixel getPixel(uint32_t x, uint32_t y);
		void render(string filename);

		//additional functions to let Drawing::draw() work
		uint32_t width() { return data[0].size(); }
		uint32_t height() { return data.size(); }

			
	private:
		vector< vector<ColorPixel> > data;
}; 

struct Line {
	Point start, end;
	ColorPixel c;
};

class Drawing {
	public:
		Drawing();
		void parse(string filename);
		void draw();
		void write(string filename);
	private:
		ColorImage image;
		vector<Line> lines;
};



#endif