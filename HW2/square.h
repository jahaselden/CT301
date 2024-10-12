#ifndef SQUARE_INCLUDED
#define SQUARE_INCLUDED
#include <iostream>

#include "collider.h"
namespace colliders
{
    class Square : public Collider
    {   
        /**
         * width of the square
         */
        double width_;

    public:
        /**
         * Default ctor
         */
        Square();             

        /**
         * Size ctor
         * @param double the square width
         */
        Square(double);

        /**
         * Centroid ctor
         * @param int, int are the x and y coordinates of center point coordinates of square
         */
        Square(int, int);        
        
        /**
         * Centroid and Size ctor
         * @param int, int are the x and y coordinates of center point coordinates of square
         * @param double the square width
         */
        Square(int, int, double);

        /**
         * GetWidth
         * @returns width of the square
         */
        double GetWidth() const;        
        
        /**
         * Collides: virtual method implementation
         * Handles Square to Square and Square to Circle collision but passes Square to 
         * Rectangle collision to Rectangle's collide
         * @param Collider object is any shape that inherits from collider
         * @returns returns true if there is a collision, false otherwise
         */
        bool Collides(const Collider &) const; 
    };
}

std::ostream &operator<<(std::ostream &out, const colliders::Square &s);

#endif