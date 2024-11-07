#include <iostream>

using namespace std;

/**
 * main
 * @param argc the program name being called
 * @param argv the data being passed to the program name for use
 * @returns an int representing success or failure of program
 */
int main(int argc, char *argv[])
{
    cout << sizeof(size_t) << endl;
    cout << sizeof(int) << endl;
    size_t test = 1;
    int tested = static_cast<int>(test);
    cout << sizeof(test);
}