#include "shapes.h"
#include "algorithm"

#include <algorithm>
#include <cmath>

//Implement your shapes here



// PARENT CLASS -------------------------------------------------------

Shape::Shape(Color c) : m_color(c) {}



// TRIANGLE -----------------------------------------------------------

Triangle::Triangle(Point t[3], Color c) : Shape(c)
{
    m_tri[0] = t[0];
    m_tri[1] = t[1];
    m_tri[2] = t[2];
}

Triangle::~Triangle(){}

/* BoundingBox Triangle::getBoundingBox() 
{
    BoundingBox b;

    uint32_t xmin =0, ymin =0, xmax=0, ymax=0; // min is top left, max is bottom right

    for (int i=0; i<3; i++){
        // check x
        if(m_tri[0].x < xmin){
            xmin= m_tri[0].x;
        }
        else if (m_tri[0].x > xmax){
            xmax= m_tri[0].x;
        }

        // check y
        if(m_tri[0].y < ymin){
            ymin= m_tri[0].y;
        }
        else if (m_tri[0].y > ymax){
            ymax= m_tri[0].y;
        }
    }

    b.ul.x= xmin;
    b.ul.y= ymin;
    b.br.x= xmax;
    b.br.y= ymax;

    return b;
} */


// SIMPLER VERSION using "algorithm" library

BoundingBox Triangle::getBoundingBox() 
{
    BoundingBox b;

    b.ul.x= min(m_tri[0].x, m_tri[1].x, m_tri[2].x);
    b.ul.y= min(m_tri[0].y, m_tri[1].y, m_tri[2].y);

    b.br.x= max(m_tri[0].x, m_tri[1].x, m_tri[2].x);
    b.br.y= max(m_tri[0].y, m_tri[1].y, m_tri[2].y);
}

 bool Triangle::inside(uint32_t x, uint32_t y)
{
    Point p = {x,y};
    return PointInTriangle(p, m_tri);
}



// CIRCLE -------------------------------------------------------------

Circle::Circle(Point center, uint32_t r, Color c) : Shape(c) {
    m_center = center;
    m_radius = r;
}

Circle::~Circle() {}

BoundingBox Circle::getBoundingBox() {
    BoundingBox b;
    b.ul.x = m_center.x - m_radius; 
    b.ul.y = m_center.y - m_radius;
    b.br.x = m_center.x + m_radius;
    b.br.y = m_center.y + m_radius;

    return b;
}

bool Circle::inside(uint32_t x, uint32_t y) {
    double px = static_cast<double>(x);
    double py = static_cast<double>(y);
    double dist = sqrt((m_center.x - px) * (m_center.x - px) + 
                           (m_center.y - py) * (m_center.y - py));

    return dist < m_radius; 
}



// RECTANGLE ------------------------------------------------------------

Rectangle::Rectangle(Point topLeft, Point bottomRight, Color c) : Shape(c) {
    m_topLeft = topLeft;
    m_bottomRight = bottomRight;
}

Rectangle::~Rectangle() {}

BoundingBox Rectangle::getBoundingBox() {
    BoundingBox b;
    b.ul = m_topLeft;
    b.br = m_bottomRight;
    return b;
}

bool Rectangle::inside(uint32_t x, uint32_t y) {
    return (x >= m_topLeft.x && x <= m_bottomRight.x 
            && y >= m_topLeft.y && y <= m_bottomRight.y);
}


