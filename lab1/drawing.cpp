#include <iostream>
#include <cmath>
#include <vector>

#include <stdexcept>
#include <fstream>
#include <sstream>

#include "bmplib.h"
#include "drawing.h"

//implement your classes in this file

//adapted from https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
std::vector<Point> plotLine(Point start, Point end)
{
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;
	
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	
	std::vector<Point> line;
	
	while(true)
	{
		Point p = {x0, y0};
		line.push_back(p);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * error;
		if(e2 >= dy) {
			error = error + dy;
			x0 = x0 + sx;
		}
		if(e2 <= dx) {
			error = error + dx;
			y0 = y0 + sy;
		}
	}
	return line;
}


//ColorImage Class Functions

//uint32_t --> unsigned int but more specific 
ColorImage::ColorImage(uint32_t xdim, uint32_t ydim )
{
    // intialize "data" vector (previate member of ColorImage)
    // ydim: rows, xdim: columns
    data.resize(ydim); // create rows first
    for(size_t i=0; i < data.size(); i++){ // data.size() returns number of rows right now
        data[i].resize(xdim);
    }
}

// setpixel
void ColorImage::setPixel(ColorPixel p, uint32_t x, uint32_t y) {
	uint32_t ysize = data.size();
	uint32_t xsize = data[0].size();
	if( x< xsize && y < ysize){ // x indicates number of columns, y indicates number of rows 
												// since this is a double vector, the length of data[0] is the number of rows
		data[y][x] = p; // row major, y comes first
	}
	
}

//getPixel
ColorPixel ColorImage::getPixel(uint32_t x, uint32_t y) {
	uint32_t ysize = data.size();
	uint32_t xsize = data[0].size();
	if( x< xsize && y < ysize){ // x indicates number of columns, y indicates number of rows 
												// since this is a double vector, the length of data[0] is the number of rows
		return data[y][x];
	}
	throw std::range_error("bad size on getPixel");
}


// render
void ColorImage::render(string filename){
	size_t ydim = data.size();
	size_t xdim = data[0].size();

	uint8_t*** image = new uint8_t**[ydim];

	for(int i=0; i<data.size(); i++) {
		image[i] = new uint8_t*[xdim];
		for(int j=0; j<xdim; j++){
			image[i][j] = new uint8_t[3]; // store RGB values
			image[i][j][R] = data[i][j].red;
			image[i][j][G] = data[i][j].green;
			image[i][j][B] = data[i][j].blue;
		}
	}
	writeRGBBMP(filename.c_str(), image, ydim, xdim);

	for (size_t y = 0; y < data.size(); ++y) {
        for (size_t x = 0; x < data[y].size(); ++x) {
            delete[] image[y][x]; // delete RGB info
        }
        delete[] image[y]; // delete each row
    }
    delete[] image; // delete the overall array

}



// Drawing Class Functions


void Drawing::parse(string filename) {
    ifstream ifile(filename);
    if (ifile.fail()) {
        cout << "Error: could not open file " << filename << endl;
        exit(1);
    }

    string line;
    bool first = true; // will be true only once

    while (getline(ifile, line)) {
        stringstream ss(line);

        if (first) { // first line has dimensions 
            uint32_t xdim, ydim;
            ss >> xdim >> ydim;
            image = ColorImage(xdim, ydim); 
            first = false;
        }  
		else { // following lines contain line information
            double x1, y1, x2, y2;
            int r, g, b;
            ss >> x1 >> y1 >> x2 >> y2 >> r >> g >> b;

			// create new Line struct
            Line line;
            line.start.x = x1;
			line.end.x = x2;
            line.start.y = y1;
			line.end.y = y2;

            line.c.red = static_cast<uint8_t>(r);
            line.c.green = static_cast<uint8_t>(g);
            line.c.blue = static_cast<uint8_t>(b);

            // Add the line to the vector
            lines.push_back(line);
        }
    }

    ifile.close();
}


void Drawing::draw() {
    for (size_t i = 0; i < lines.size(); ++i) { // loop through vector
        const Line &line = lines[i];
        // Use plotLine to get the vector of points that represent the line
        vector<Point> points = plotLine(line.start, line.end);
        
        // Set each point on the ColorImage to the color of the line
        for (size_t j = 0; j < points.size(); ++j) {
            const Point &p = points[j];
            if (p.x >= 0 && p.x < (image.width()) && p.y >= 0 && p.y < image.height()) {
                image.setPixel(line.c, static_cast<uint32_t>(p.x), static_cast<uint32_t>(p.y));
            }
        }
    }
}


void Drawing::write(std::string filename) {
    image.render(filename);  
}


