#include "double_vector.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
int main(int argc, char const *argv[])
{
    double_vector d2;
    vector<double> v;
    cout << "Testing Default Constructor\n";
    cout << v.capacity() << " " << v.size() << endl;
    cout << d2.capacity() << " " << d2.size() << endl;
    cout << "Comparing Vector to Double_Vector\n" << endl;
    for (int i = 0; i < 13; ++i)
    {
        d2.push_back(i);
        v.push_back(i);
        cout << "Cap: " << d2.capacity() << " Size: " << d2.size() << endl;
        cout << "Cap: " << v.capacity() << " Size: " << v.size() << endl;
    }
    cout << "\nTesting [] operator\n"<<endl;
    for (size_t i = 0; i < d2.size(); ++i){
        cout << d2[i] << ' ';
    }
    cout << endl;
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] << ' ';
    }
    cout << endl;
    cout << "\nAttemtping Copy Constructor\nCopy: ";
    double_vector cp(d2);
    cp.front() = 18;
    for (size_t i = 0; i < cp.size(); ++i){
        cout << cp[i] << ' ';
    }
    cout << "\nOriginal: ";
    for (size_t i = 0; i < d2.size(); ++i){
        cout << d2[i] << ' ';
    }
    cout << "\nCopy: ";
    vector<double> cv(v);
    cv.front() = 18;
    for (size_t i = 0; i < cv.size(); ++i){
        cout << cv[i] << ' ';
    }
    cout << "\nOriginal: ";
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] << ' ';
    }
    cout << endl;
    cout << "\nTesting Assignment Operator\nCopy: ";
    double_vector d_assn;
    d_assn = cp;
    d_assn.back() = -1;
    for (size_t i = 0; i < d_assn.size(); ++i){
        cout << d_assn[i] << ' ';
    }
    cout <<"\nOriginal: ";
    for (size_t i = 0; i < cp.size(); ++i){
        cout << cp[i] << ' ';
    }
    cout << "\nCopy: ";
    vector<double> v_assn;
    v_assn = cv;
    v_assn.back() = -1;
    for (size_t i = 0; i < v_assn.size(); ++i){
        cout << v_assn[i] << ' ';
    }
    cout <<"\nOriginal: ";
    for (size_t i = 0; i < cv.size(); ++i){
        cout << cv[i] << ' ';
    }
    cout << endl;
    double_vector dv(2);
    vector<double> v_swap(2);
    dv.resize(5,3.14);
    v_swap.resize(5,3.14);
    cout << "\nTesting Swap\nBefore Swap:\n";
    cout << "d2 Cap: " << d2.capacity() << " Size: " << d2.size() << "\nd2 Elements: ";
    for (size_t  i = 0; i < d2.size(); ++i)
        cout << d2[i] << " ";
    cout << "\ndv Cap: " << dv.capacity() << " Size: " << dv.size() << "\ndv Elements: ";
    for (size_t  i = 0; i < dv.size(); ++i)
        cout << dv[i] << " ";
    dv.swap(d2);
    cout << "\nAfter Swap\n";
    cout << "d2 Cap: " << d2.capacity() << " Size: " << d2.size() << "\nd2 Elements: ";
    for (size_t  i = 0; i < d2.size(); ++i)
        cout << d2[i] << " ";
    cout << "\ndv Cap: " << dv.capacity() << " Size: " << dv.size() << "\ndv Elements: ";
    for (size_t  i = 0; i < dv.size(); ++i)
        cout << dv[i] << " ";
    cout << "\n\n";
    cout << "\nTesting Vector Swap\nBefore Swap:\n";
    cout << "v Cap: " << v.capacity() << " Size: " << v.size() << "\nv Elements: ";
    for (size_t  i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << "\nv_swap Cap: " << v_swap.capacity() << " Size: " << v_swap.size() << "\nv_swap Elements: ";
    for (size_t  i = 0; i < v_swap.size(); ++i)
        cout << v_swap[i] << " ";
    v_swap.swap(v);
    cout << "\nAfter Swap\n";
    cout << "v Cap: " << v.capacity() << " Size: " << v.size() << "\nd2 Elements: ";
    for (size_t  i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << "\nv_swap Cap: " << v_swap.capacity() << " Size: " << v_swap.size() << "\nv_swap Elements: ";
    for (size_t  i = 0; i < v_swap.size(); ++i)
        cout << v_swap[i] << " ";
    cout << "\n\n";
    cout << "Testing Iterator\n";
    for (double_vector::iterator iter = d2.begin(); iter != d2.end(); ++iter){
        cout << *iter << " ";
    }
    cout << '\n';
    for (vector<double>::iterator iter = v.begin(); iter != v.end(); ++iter){
        cout << *iter << " ";
    }
    cout << '\n';
    return 0;
}