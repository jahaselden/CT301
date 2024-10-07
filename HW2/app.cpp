#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// sanitize error methods

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << endl
             << argv[0] << endl
             << "Must provide a shape file";
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

        string line;
        while (getline(file, line))
        {
            //just testing 
            cout << line << endl;
        }

        file.close();
        return 0;
    }
}