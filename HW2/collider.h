#ifndef COLLIDER_INCLUDED
#define COLLIDER_INCLUDED
#include <iostream>
namespace colliders {
class Collider {
  int x_, y_;
 public:
  Collider(): x_(0),y_(0) {}
  Collider(int x, int y) : x_(x), y_(y){}
  int GetX() const {return this->x_;}
  int GetY() const {return this->y_;}
  virtual bool Collides(const Collider&) const = 0;
  virtual ~Collider() = default;
};
}  // namespace colliders

#endif