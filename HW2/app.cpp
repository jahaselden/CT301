#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "square.h"
#include "circle.h"
#include "rectangle.h"
#include "collider.h"

using namespace std;
using namespace colliders;

/**
 * main
 * @param argc the program name being called
 * @param argv the data being passed to the program name for use
 * main provides an interface for users to add shapes to a graph. It sanitizes any errant
 * data, and then checks that a shape does not collide with pre-existing shapes. If this is
 * the case, shapes are added to the current shapes.
 * @returns an int representing success or failure of program
 */
int main(int argc, char *argv[])
{
    string program_name = argv[0];
    if (argc < 2)
    {
        cerr << "Usage: " << endl
             << program_name << endl
             << "Must provide a shape file including: Shape XCoord YCoord Radius/Width Height";
        return 1;
    }
    else
    {
        string filename = argv[1];
        ifstream file(filename);

        if (file.is_open())
        {
            cerr << "Error! Could not open file: " << filename << endl;
            return 1;
        }

        // create a vector of type collision to store all the shapes
        vector<Collider *> shapes;
        string line;
        while (getline(file, line))
        {
            stringstream shape(line);

            string name;
            // check if first ss is a string
            if (!(shape >> name))
            {
                cerr << "Error: " << program_name << endl
                     << "Invalid shape type: " << line << endl;
                return -1;
            }

            int x, y;
            double width;
            double height;
            double radius;
            bool collides = false;

            Collider *shape_;
            // if shape name "is "Square"
            if (name.compare("Square"))
            {
                if (!(shape >> x >> y >> width))
                {
                    cerr << "Error: " << program_name << endl
                         << "Invalid data: " << line << endl;
                }
                else
                {
                    // create square object
                    shape_ = new Square(x, y, width);
                    for (Collider *shape_obj : shapes)
                    {
                        if (shape_->Collides(*shape_obj))
                        {
                            collides = true;
                        }
                    }
                    if (!collides)
                    {
                        shapes.push_back(shape_);
                    }
                }

                // if shape name is "Rectangle"
                if (name.compare("Rectangle"))
                {

                    if (!(shape >> x >> y >> width >> height))
                    {
                        cerr << "Error: " << program_name << endl
                             << "Invalid data: " << line << endl;
                    }
                    else
                    {
                        // create rectangle object
                        shape_ = new Rectangle(x, y, width, height);
                        for (Collider *shape_obj : shapes)
                        {
                            if (shape_->Collides(*shape_obj))
                            {
                                collides = true;
                            }
                        }
                        if (!collides)
                        {
                            shapes.push_back(shape_);
                        }
                    }
                }
                // if shape name is "Circle"
                if (name.compare("Circle"))
                {
                    //
                    if (!(shape >> x >> y >> radius))
                    {
                        cerr << "Error: " << program_name << endl
                             << "Invalid data: " << line << endl;
                    }
                    else
                    {
                        // create circle object
                        shape_ = new Circle(x, y, radius);
                        for (Collider *shape_obj : shapes)
                        {
                            if (shape_->Collides(*shape_obj))
                            {
                                collides = true;
                            }
                        }
                        if (!collides)
                        {
                            shapes.push_back(shape_);
                        }
                    }
                }
            }

            for (Collider *shape_obj : shapes)
            {
                if (const Rectangle *const target = dynamic_cast<const Rectangle *const>(shape_obj)){
                    cout << target;
                }
                if (const Circle *const target = dynamic_cast<const Circle *const>(shape_obj)){
                    cout << target;
                }
                if (const Square *const target = dynamic_cast<const Square *const>(shape_obj)){
                    cout << target;
                }
            }

            file.close();
            return 0;
        }
    }
}