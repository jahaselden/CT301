#ifndef RECTANGLE_INCLUDED
#define RECTANGLE_INCLUDED
#include <iostream>
#include "square.h"
namespace colliders
{
    class Rectangle : public Square
    {
        double height;

    public:
        Rectangle();                         // Default Constructor
        Rectangle(double, double);           // Size Constructor
        Rectangle(int, int);                 // Coordinate constructor
        Rectangle(int, int, double, double); // Coordinate and Size constructor

        double GetHeight() const;
        // collides method??
        bool Collides(const Collider &) const; // Method definition for Virtual method Collides
    };
}

std::ostream &operator<<(std::ostream &out, const colliders::Rectangle &s);

#endif