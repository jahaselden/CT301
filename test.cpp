#include "square.h"
#include "circle.h"

#include <iostream>

using namespace std;
using namespace colliders;

int main()
{
    Square s(3, 3, 4);
    Circle c(0, 0, 2);
    // boolalpha makes it so the ostream prints "true" or "false" instead of "1" or "0" respectively
    cout << std::boolalpha << (s.Collides(c)) << '\n'; // True
    Square s2 = Square();
    Circle c2 = Circle(4, 0, 2);
    cout << c2.Collides(c) << '\n';  // False
    cout << s2.Collides(c) << '\n';  // True
    cout << s2.Collides(c2) << '\n'; // False
    cout << c2 << '\n'
         << s << '\n';
    return 0;
}