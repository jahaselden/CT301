#ifndef SQUARE_INCLUDED
#define SQUARE_INCLUDED
#include <iostream>

#include "collider.h"
namespace colliders
{
    class Square : public Collider
    {
        double width_;

    public:
        Square();                 // Default constructor
        Square(double);           // Size constructor
        Square(int, int);         // Centroid constructor
        Square(int, int, double); // Centroid and Size constructor

        double GetWidth() const;    // Width Getter

        bool Collides(const Collider &) const; // Method definition for Virtual method Collides
    };
}

std::ostream &operator<<(std::ostream &out, const colliders::Square &s);

#endif