#ifndef RECTANGLE_INCLUDED
#define RECTANGLE_INCLUDED
#include <iostream>
#include "square.h"
namespace colliders
{
    class Rectangle : public Square
    {
        /**
         * stores height of rectangle
         */
        double height_;

    public:
        /**
         * Default ctor
         */
        Rectangle();

        /**
         * Size ctor
         * @param double, double the width and height of a rectangle
         */
        Rectangle(double, double);

        /**
         * Centroid ctor
         * @param int, int the x and y coordinates of the rectangle's center
         */
        Rectangle(int, int);

        /**
         * Centroid and Size ctor
         * @param int, int are the x and y coordinates of center point coordinates
         * @param double, double the rectangle widtha nd height
         */
        Rectangle(int, int, double, double);

        /**
         * GetHeight
         * @returns height of rectangle
         */
        double GetHeight() const;

        /**
         * Collides: virtual method implementation
         * Handles Rectangle to Rectangle, Rectangle to Square, and Rectangle to Circle collision checks
         * @param Collider object is any shape that inherits from collider
         * @returns returns true if there is a collision, false otherwise
         */
        bool Collides(const Collider &) const; // Method definition for Virtual method Collides
    };
}

std::ostream &operator<<(std::ostream &out, const colliders::Rectangle &s);

#endif