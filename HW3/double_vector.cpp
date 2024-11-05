#include "double_vector.h"
#include <cstddef>
#include <stddef.h>

using namespace std;

double_vector::double_vector() : double_vector(0) {}
double_vector::double_vector(size_t capacity) : size_(0)
{
    if (capacity > max_size())
    {
        capacity_ = max_size();
    }
    else
    {
        capacity_ = capacity;
    }
    this->data_ = new double[this->capacity_];
}

double_vector::double_vector(const double_vector &rhs)
{
    // this->capacity_ = rhs.capacity_;
    // this->size_ = rhs.size_;
    // this->data_ = new double[capacity_];
    // for (size_t i = 0; i < capacity_; i++)
    // {
    //     data_[i] = rhs.data_[i];
    // }
    *this = double_vector(rhs);
}

double_vector &double_vector::operator=(const double_vector &rhs)
{
    this->capacity_ = rhs.capacity_;
    this->size_ = rhs.size_;
    this->data_ = new double[capacity_];
    for (size_t i = 0; i < capacity_; i++)
    {
        data_[i] = rhs.data_[i];
    }
}

double_vector::~double_vector()
{
    delete[] data_;
    data_ = nullptr;
}

// CAPACITY METHODS

size_t double_vector::size()
{
    return size_;
}

size_t double_vector::max_size()
{
    return ((2 ^ 32) / sizeof(double)) - 1;
}

size_t double_vector::capacity()
{
    return capacity_;
}

void double_vector::resize(size_t n, double val)
{
}

bool double_vector::empty()
{
    return size_ == 0 ? true : false;
}

void double_vector::reserve(size_t n)
{
}

void double_vector::shrink_to_fit()
{
}

// ELEMENT ACCESS

double double_vector::&operator[](size_t n)
{
}

double double_vector::&at(size_t n)
{
}

double double_vector::&front()
{
}

double double_vector::&back()
{
}

double double_vector::*data()
{
}

double_vector::iterator begin()
{
}

double_vector::iterator end()
{
}

// MODIFIERS
void double_vector::reallocate(size_t n)
{
    double *new_data = new double[n];
    // if n is smaller than old data's size,
    // only copy n values into new array
    for (int i = 0; i < n && i < size_; i++)
    {
        // to do
    }
    delete[] data_;
    data_ = new_data; // is this right?
}

void double_vector::push_back(const double &val)
{
}

void double_vector::pop_back()
{
}

void double_vector::swap(double_vector &other)
{
}

void double_vector::clear()
{
    return size_ == 0 ? true : false;
}

// ITERATOR SUBCLASS

double_vector::iterator &double_vector::iterator::operator++()
{
}

double_vector::iterator double_vector::iterator::operator++(int)
{
}

double_vector::iterator &double_vector::iterator::operator--()
{
}

double_vector::iterator double_vector::iterator::operator--(int)
{
}

double &double_vector::iterator::operator*()
{
}

bool double_vector::iterator::operator==(const iterator &) const
{
}

bool double_vector::iterator::operator!=(const iterator &) const
{
}
