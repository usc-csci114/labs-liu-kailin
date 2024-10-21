#include <iostream>
#include <fstream>
#include "bmplib.h"
#include "drawing.h"

using namespace std;

int main(int argc, char* argv[])
{
	//use the structs/classes you defined in drawing.h to implement the program in this file
	/* ColorImage test(100,100); // creating a ColorImage called "test"
	ColorPixel white = {255, 255, 255};
	for (int i=0; i<100; i++){
		for (int j=0; j<100; j++){
			test.setPixel(white, j,i);
		}
	}
	test.render("test.bmp"); */

	ifstream ifile(argv[1]);
    if (ifile.fail()) {
       	cout << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

	Drawing drawing;
    drawing.parse(argv[1]);
    drawing.draw();
    drawing.write("output.bmp");

    return 0;

}
