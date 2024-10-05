#include "circle.h"

#include <math.h>
using namespace colliders;
using namespace std;

Circle::Circle() : Circle(1) {}  // Default Radius of 1
Circle::Circle(double radius)
    : Circle(0, 0, radius) {}  // Constructor chaining to int int double
Circle::Circle(int x, int y)
    : Circle(x, y, 1) {}  // Constructor chaining to int int double
Circle::Circle(int x, int y, double radius)
    : Collider(x, y), radius_(radius) {}  // Standard Assignment
double Circle::GetRadius() const { return this->radius_; }
bool Circle::Collides(const Collider &other) const {
  if (this->GetX() == other.GetX() &&
      this->GetY() ==
          other.GetY())  // If perfectly overlapped automatically collided
    return true;
  if (const Circle *const target = dynamic_cast<const Circle *const>(&other)) {
    // Calculate the absolute distance between This and Other
    double distance = sqrt(pow(this->GetX() - target->GetX(), 2) +
                           pow(this->GetY() - target->GetY(), 2));
    double Rsum = this->GetRadius() + target->GetRadius();
    if (distance < Rsum) {
      return true;
    } else {
      return false;
    }
  } else {
    return other.Collides(*this);
  }
}
ostream &operator<<(ostream &out, const Circle &c) {
  out << "Circle:\n" << "\t(X,Y): (" << c.GetX() << "," << c.GetY() << ")\n";
  out << "\tRadius: " << c.GetRadius() << "\n";
  return out;
}
