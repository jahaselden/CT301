#include "square.h"
#include "rectangle.h"
#include "circle.h"

using namespace colliders;
using namespace std;

Square::Square() : Square(1) {} // Defalt width is 1
Square::Square(double width) : Square(0, 0, width) {}
Square::Square(int x, int y) : Square(x, y, 1) {}
Square::Square(int x, int y, double width) : Collider(x, y), width_(width) {}

double Square::GetWidth() const { return this->width_; }

bool Square::Collides(const Collider &other) const
{

    // If perfectly overlapped, shapes collide
    if (this->GetX() == other.GetX() && this->GetY() == other.GetY())
    {
        return true;
    }

    // get the square comparison coordinates
    int s1_right_x = this->GetX() + (this->GetWidth() / 2);
    int s1_left_x = this->GetX() - (this->GetWidth() / 2);
    int s1_upper_y = this->GetY() + (this->GetWidth() / 2);
    int s1_lower_y = this->GetY() - (this->GetWidth() / 2);

    // square to square
    if (const Square *const target = dynamic_cast<const Square *const>(&other))
    {
        int s2_right_x = other.GetX() + (target->GetWidth() / 2);
        int s2_left_x = other.GetX() - (target->GetWidth() / 2);
        int s2_upper_y = other.GetY() + (target->GetWidth() / 2);
        int s2_lower_y = other.GetY() - (target->GetWidth() / 2);
        // compare x-axis values for collision
        if (s1_right_x >= s2_left_x && s1_left_x <= s2_right_x)
        {
            return false;
        }
        // compare y-axis values for collision
        if (s1_upper_y <= s2_lower_y && s1_lower_y >= s2_upper_y)
        {
            return false;
        }
        // if both return false, there is a collision
        return true;
    }

    // square to circle
    if (const Circle *const target = dynamic_cast<const Circle *const>(&other))
    {
        int circle_x = target->GetX();
        int circle_y = target->GetY();

        // find closest x coord of square's side and circle centroid
        int min_x = (circle_x < s1_right_x) ? circle_x : s1_right_x;
        int closest_x = (s1_left_x < min_x) ? min_x : s1_left_x;

        // find closest y coord of  of square's top/bottom and circle centroid
        int min_y = (circle_y < s1_upper_y) ? circle_y : s1_upper_y;
        int closest_y = (s1_lower_y < min_y) ? min_y : s1_lower_y;

        int distance_x = circle_x - closest_x;
        int distance_y = circle_y - closest_y;

        // if ((distance of x) ^ 2 + (distance of y) ^ 2) < radius ^ 2))
        if (((distance_x * distance_x) + (distance_y * distance_y)) < target->GetRadius() * target->GetRadius())
        {
            // there is a collision
            return true;
        }
        else
        {
            // touching or do not collide
            return false;
        }
    }

    // square to rectangle
    // call rectangle's collide - let Rectangle handle all the collisions
    if (const Rectangle *const target = dynamic_cast<const Rectangle *const>(&other))
    {
        return target->Collides(*this);
    }
    return false;
}

ostream &operator<<(ostream &out, const Square &sq)
{
    out << "Square:\n"
        << "\t(X,Y): (" << sq.GetX() << "," << sq.GetY() << ")\n";
    out << "\tWidth: " << sq.GetWidth() << "\n";
    return out;
}