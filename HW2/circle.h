#ifndef CIRCLE_INCLUDED
#define CIRCLE_INCLUDED
#include <iostream>
#include "collider.h"

namespace colliders
{
  class Circle : public Collider
  {
    double radius_;

  public:
    Circle();                              // Default constructor
    Circle(double);                        // Radius Constructor
    Circle(int, int);                      // Centroid Constructor
    Circle(int, int, double);              // Centroid and Radius Constructor
    double GetRadius() const;              // Radius Getter
    bool Collides(const Collider &) const; // Method definition for Virtual method Collides
  };
}
std::ostream &operator<<(std::ostream &, const colliders::Circle &);

#endif