#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <square.h>
#include <circle.h>
#include <rectangle.h>
#include <vector>
#include <collider.h>

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
main(int argc, char *argv[])
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

        if (!file.is_open())
        {
            cerr << "Error! Could not open file: " << filename << endl;
            return 1;
        }

        // create a vector of type collision to store all the shapes
        vector<Collider> shapes;
        string line;
        while (getline(file, line))
        {
            stringstream shape(line);

            string name;
            // check if first ss is a string
            if (!(shape >> name))
            {
                cerr << "Error: " << program_name << endl
                     << "Invalid data: " << line << endl;
                return -1;
            }
            // if shape name "is "Square"
            if (name.compare("Square"))
            {
                int x, y;
                double width;
                if (!(shape >> x >> y >> width))
                {
                    cerr << "Error: " << program_name << endl
                         << "Invalid data: " << line << endl;
                }
                else
                {
                    // create square object
                    Square square = new Square(x, y, width);
                    // if vector is empty
                    if (shapes.size() == 0 || !square.Collides()){
                        shapes.push_back(square);
                    }
                }
            }

            // if shape name is "Rectangle"
            if (name.compare("Rectangle"))
            {
                int x, y;
                double width, height;
                if (!(shape >> x >> y >> width >> height))
                {
                    cerr << "Error: " << program_name << endl
                         << "Invalid data: " << line << endl;
                }
                else
                {
                    // create rectangle object
                    Rectangle rec = new Rectangle(x, y, width, height);

                    // if vector is empty
                    if (shapes.size() == 0 || !rec.Collides()){
                        shapes.push_back(rec);
                    }
                }
            }
            // if shape name is "Circle"
            if (name.compare("Circle"))
            {
                int x, y;
                int radius;
                if (!(shape >> x >> y >> radius))
                {
                    cerr << "Error: " << program_name << endl
                         << "Invalid data: " << line << endl;
                }
                else
                {
                    // create circle object - do these need to be pointers?
                    Circle circle = new Circle(x, y, radius);
                    // if vector is empty
                    if (shapes.size() == 0 || !circle.Collides())
                    {
                        shapes.push_back(circle);
                    }
                }
            }
        }

        file.close();
        return 0;
    }
}