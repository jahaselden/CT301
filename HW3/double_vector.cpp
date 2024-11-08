#include "double_vector.h"
#include <cstddef>
#include <stddef.h>
#include <cmath>

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
    if (capacity_ != 0) // data_ will stay a nullptr otherwise
    {
        data_ = new double[capacity_];
    }
}

double_vector::double_vector(const double_vector &rhs)
{
    //*this = double_vector(rhs);
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = new double[capacity_];
    for (size_t i = 0; i < capacity_; i++)
    {
        data_[i] = rhs.data_[i];
    }
}

double_vector &double_vector::operator=(const double_vector &rhs)
{
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    delete[] data_;
    data_ = new double[capacity_];
    for (size_t i = 0; i < capacity_; i++)
    {
        data_[i] = rhs.data_[i];
    }
    return *this;
}

double_vector::~double_vector()
{
    delete[] data_;
    data_ = nullptr;
}

// CAPACITY METHODS

size_t double_vector::size()
{
    return this->size_;
}

size_t double_vector::max_size()
{
    return (pow(2, 32) / sizeof(double)) - 1;
}

size_t double_vector::capacity()
{
    return this->capacity_;
}

void double_vector::resize(size_t n)
{
    resize(n, 0);
}

void double_vector::resize(size_t n, double val)
{
    double *new_data = new double[n];

    // if n is smaller than old data's size, only copy n values into new array
    if (n < size_)
    {
        for (size_t i = 0; i < n; ++i)
        {
            new_data[i] = data_[i];
        }
    }
    else // n is greater than size_
    {
        // copy old data to new data up to size
        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        // set new data beyond the size to be 0 (up to capacity)
        for (size_t i = size_; i < n; ++i)
        {
            new_data[i] = val;
        }
    }

    capacity_ = n;
    delete[] data_;
    data_ = new_data;
    new_data = nullptr;
}

bool double_vector::empty()
{
    return size_ == 0 ? true : false;
}

void double_vector::reserve(size_t n)
{
    if (n > capacity_)
    {
        reallocate(n);
    }
}

void double_vector::shrink_to_fit()
{
    reallocate(size_);
}

// ELEMENT ACCESS

double &double_vector::operator[](size_t n)
{
    return data_[n];
}

double &double_vector::at(size_t n)
{
    if (n > size_)
    {
        throw std::range_error("Index out of range");
    }
    return data_[n];
}

double &double_vector::front()
{
    return data_[0];
}

double &double_vector::back()
{
    return data_[size_];
}

double *double_vector::data()
{
    return data_;
}

double_vector::iterator double_vector::begin() const
{
    double_vector::iterator begin;
    begin.ptr = this->data_;
    return begin;
}

double_vector::iterator double_vector::end() const
{
    double_vector::iterator end;
    // size_t is 8 bytes, iterate through using ints to get to last element
    for (size_t i = 0; i < size_; i++)
    {
        ++end.ptr;
    }
    return end;
}

// MODIFIERS
void double_vector::reallocate(size_t n)
{
    if (n > max_size())
    {
        n = max_size();
    }

    capacity_ = n;
    double *new_data;

    if (capacity_ == 0)
    {
        new_data = nullptr;
    }
    else
    {
        new_data = new double[capacity_];
    }

    int values = capacity_ < size_ ? capacity_ : size_;
    // if n is smaller than old data's size, only copy n values into new array
    for (int i = 0; i < values; ++i)
    {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    new_data = nullptr;
}

void double_vector::push_back(const double &val)
{
    // if at capacity, double the vector size
    if (size_ == capacity_)
    {
        reallocate(capacity_ * 2);
    }

    if (capacity_ == 0)
    {
        reallocate(1);
    }

    data_[size_] = val;
    ++size_;
}

void double_vector::pop_back()
{
    data_[this->size_] = 0;
    --this->size_;
}

void double_vector::swap(double_vector &other)
{
    double_vector temp = other;
    other = *this;
    *this = temp;
    // do i need to delete temp?
}

void double_vector::clear()
{
    delete[] data_;
    data_ = new double[capacity_];
    size_ = 0;
}

// ITERATOR SUBCLASS

double_vector::iterator &double_vector::iterator::operator++()
{
    ++ptr;
    return *this;
}

double_vector::iterator double_vector::iterator::operator++(int)
{
    iterator copy = *this;
    ++ptr;
    return copy;
}

double_vector::iterator &double_vector::iterator::operator--()
{
    --ptr;
    return *this;
}

double_vector::iterator double_vector::iterator::operator--(int)
{
    iterator copy = *this;
    --ptr;
    return copy;
}

double &double_vector::iterator::operator*()
{
    return *ptr;
}

bool double_vector::iterator::operator==(const iterator &other) const
{
    if (&ptr == &other.ptr)
    {
        return true;
    }
    return false;
}

bool double_vector::iterator::operator!=(const iterator &other) const
{
    if (&ptr != &other.ptr)
    {
        return true;
    }
    return false;
}
