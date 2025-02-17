#include "double_vector.h"
#include <cstddef>
#include <stddef.h>
#include <cmath>

using namespace std;

double_vector::double_vector() : double_vector(0) {}
double_vector::double_vector(size_t capacity)
{
    if (capacity > max_size())
    {
        capacity = max_size();
    }
    
    this->size_ = capacity;
    this->capacity_ = capacity;

    if (this->capacity_ != 0) // data_ will stay a nullptr otherwise
    {
        this->data_ = new double[this->capacity_];
    }
}

double_vector::double_vector(const double_vector &rhs)
{
    //*this = double_vector(rhs);
    this->capacity_ = rhs.capacity_;
    this->size_ = rhs.size_;
    this->data_ = new double[this->capacity_];
    for (size_t i = 0; i < this->capacity_; i++)
    {
        this->data_[i] = rhs.data_[i];
    }
}

double_vector &double_vector::operator=(const double_vector &rhs)
{
    this->capacity_ = rhs.capacity_;
    this->size_ = rhs.size_;
    delete[] this->data_;
    this->data_ = new double[this->capacity_];
    for (size_t i = 0; i < this->capacity_; i++)
    {
        this->data_[i] = rhs.data_[i];
    }
    return *this;
}

double_vector::~double_vector()
{
    delete[] this->data_;
    this->data_ = nullptr;
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
    // if n is smaller than old data's size
    if (n < this->size_)
    {
        // set all values n through size to 0

        for (size_t i = n; i < size_; ++i)
        {
            this->data_[i] = val;
        }
    }
    if (n > this->size_ && n < this->capacity_)
    {
        for (size_t i = this->size_; i < n; ++i)
        {
            this->data_[i] = val;
        }
    }
    if (n > this->capacity_)
    {
        reallocate(n);
    }

    this->size_ = n;
}

bool double_vector::empty()
{
    return this->size_ == 0 ? true : false;
}

void double_vector::reserve(size_t n)
{
    if (n > this->capacity_)
    {
        reallocate(n);
    }
}

void double_vector::shrink_to_fit()
{
    reallocate(this->size_);
}

// ELEMENT ACCESS

double &double_vector::operator[](size_t n)
{
    return this->data_[n];
}

double &double_vector::at(size_t n)
{
    // size_t cannot be negative
    if (n >= this->size_)
    {
        throw std::range_error("Index out of range");
    }
    return this->data_[n];
}

double &double_vector::front()
{
    return this->data_[0];
}

double &double_vector::back()
{
    return this->data_[size_];
}

double *double_vector::data()
{
    return this->data_;
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
    end.ptr = this->data_;
    end.ptr += this->size_;
    return end;
}

// MODIFIERS
void double_vector::reallocate(size_t n)
{
    if (n > max_size())
    {
        n = max_size();
    }

    this->capacity_ = n;
    double *new_data;
    if (this->capacity_ == 0)
    {
        new_data = nullptr;
    }
    else
    {
        new_data = new double[this->capacity_];
    }

    //  if n is smaller than old data's size, only copy n values into new array
    if (n < this->size_)
    {
        // lesser size, size_ needs update
        this->size_ = n;
    }

    for (size_t i = 0; i < this->size_; ++i)
    {
        new_data[i] = this->data_[i];
    }
    delete[] data_;
    this->data_ = new_data;
    new_data = nullptr;
}

void double_vector::push_back(const double &val)
{
    // if at capacity, double the vector size
    if (this->size_ == this->capacity_)
    {
        reallocate(this->capacity_ * 2);
    }

    if (this->capacity_ == 0)
    {
        reallocate(1);
    }
    this->data_[this->size_] = val;
    ++this->size_;
}

void double_vector::pop_back()
{
    this->data_[size_] = 0;
    --this->size_;
}

void double_vector::swap(double_vector &other)
{
    double_vector temp = other;
    other = *this;
    *this = temp;
}

void double_vector::clear()
{
    delete[] this->data_;
    this->data_ = new double[this->capacity_];
    this->size_ = 0;
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
    if (this->ptr == other.ptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool double_vector::iterator::operator!=(const iterator &other) const
{
    if (this->ptr != other.ptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}
