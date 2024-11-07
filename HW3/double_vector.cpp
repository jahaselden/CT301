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
    if (capacity_ != 0) //data_ will stay a nullptr otherwise
    {
        data_ = new double[capacity_];
    }
}

double_vector::double_vector(const double_vector &rhs)
{
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
    return size_;
}

size_t double_vector::max_size()
{
    return (pow(2, 32) / sizeof(double)) - 1;
}

size_t double_vector::capacity()
{
    return capacity_;
}

void double_vector::resize(size_t n)
{
    resize(n, 0);
}

void double_vector::resize(size_t n, double val)
{
    capacity_ = n;
    double *new_data = new double[capacity_];

    // if n is smaller than old data's size, only copy n values into new array
    if (capacity_ < size_)
    {
        for (size_t i = 0; i < capacity_; ++i)
        {
            new_data[i] = data_[i];
        }
    }
    else
    {
        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        // set any data beyond the size to be 0;
        for (size_t i = size_; i < capacity_; ++i)
        {
            new_data[i] = val;
        }
    }

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
    this->ptr = data_
}

double_vector::iterator double_vector::end() const
{
    data_[size_];
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
        reallocate(0);
    }

    data_[size_] = val;
    ++size_;
}

void double_vector::pop_back()
{
    data_[size_] = 0;
    --size_;
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
    delete [] data_;
    data_ = new double[capacity_];
    size_ = 0;
}

// ITERATOR SUBCLASS
double *double_vector::iterator::get_ptr()
{
    return ptr;
}

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
