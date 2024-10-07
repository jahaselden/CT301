#include "rectangle.h"
#include "square.h"
#include "circle.h"

using namespace colliders;
using namespace std;

Rectangle::Rectangle() : Rectangle(1, 1) {} // Defalt width is 1
Rectangle::Rectangle(double width, double height) : Rectangle(0, 0, width, height) {}
Rectangle::Rectangle(int x, int y) : Rectangle(x, y, 1, 1) {}
Rectangle::Rectangle(int x, int y, double width, double height) : Rectangle(x, y, width, height){}

double Rectangle::GetHeight() const { return this->height; }

bool Rectangle::Collides(const Collider &other) const
{

    // If perfectly overlapped, shapes collide
    if (this->GetX() == other.GetX() && this->GetY() == other.GetY())
    {
        return true;
    }

    // get the square comparison coordinates
    int s1_upper_x = this->GetX() + (this->GetWidth() / 2);
    int s1_lower_x = this->GetX() - (this->GetWidth() / 2);
    int s1_upper_y = this->GetY() + (this->GetHeight() / 2);
    int s1_lower_y = this->GetY() - (this->GetHeight() / 2);

    // square to square
    if (const Rectangle *const target = dynamic_cast<const Rectangle *const>(&other))
    {
        int s2_upper_x = other.GetX() + (target->GetWidth() / 2);
        int s2_lower_x = other.GetX() - (target->GetWidth() / 2);
        int s2_upper_y = this->GetY() + (target->GetHeight() / 2);
        int s2_lower_y = this->GetY() - (target->GetHeight() / 2);

        // compare x-axis values for collision
        if (s1_upper_x >= s2_lower_x && s1_lower_x <= s2_upper_x)
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

    // rectangle to circle
    if (const Circle *const target = dynamic_cast<const Circle *const>(&other))
    {
        // if ((distance of x) ^ 2 + (distance of y) ^ 2) < radius ^ 2))
            //there is a collision
    }

    // square to rectangle
    if (const Square *const target = dynamic_cast<const Square *const>(&other))
    {
        
    }
}

ostream &operator<<(ostream &out, const Rectangle &rec)
{
    out << "Rectangle:\n"
        << "\t(X,Y): (" << rec.GetX() << "," << rec.GetY() << ")\n";
    out << "\tWidth: " << rec.GetWidth() << "\n";
    out << "\tHeight: " << rec.GetHeight() << "\n";
    return out;
}