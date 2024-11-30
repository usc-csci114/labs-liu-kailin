#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <matplot/matplot.h>

using namespace matplot;

int main() {
	
	std::ifstream ifile("atmosphere.txt");
	std::string line;
	std::vector<double> p, h, t;
	//follow the lab instructions to generate task1.png, task2a.png and task2b.png
	
    
    // TASK 2A ----------------------------------------------------
    
    // skip first 4 lines
    for (int i=0; i<4; i++){
        std::getline(ifile,line);
    }
    // get actual lines
    double PRES, HGHT, TEMP;
    while(std::getline(ifile,line)){
        // parse line
        std::stringstream ss(line);
        // take in necessary values
        ss >> PRES >> HGHT >> TEMP;
        // add to corresponding vector
        p.push_back(PRES);
        h.push_back(HGHT);
        t.push_back(TEMP);
    }
	
    ifile.close();
    
    // plot
    plot(h, p, "-bx");
    // update labels
    xlabel("Height (m)");
    ylabel("Pressure (hPa)");
    // show and save
    show();
    save("task2a.png");
    
    
    // TASK 2B ----------------------------------------------------
    
    //find min and max using iterators
    double t_min = *std::min_element(t.begin(), t.end());
    double t_max = *std::max_element(t.begin(), t.end());
    
    // add temperature
    hold(on);
    plot(h, t, "-rx") -> use_y2(true);
    y2lim({t_min, t_max});
    y2label("Temperature (C)");
    show();
    save("task2a.png");
    
    
	return 0;
}
