#ifndef DOUBLE_VECTOR_H_INCLUDED
#define DOUBLE_VECTOR_H_INCLUDED

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>

class double_vector
{
    /**
     * method name
     * @param name and description
     * @return value/type and description
     */

    /**
     * Pointer to data array. Remember to use new and delete keywords to properly allocate space for data.
     */
    double *data_ = nullptr;

    /**
     * How much data is currently stored.
     */
    std::size_t size_;

    /**
     * How much data can be stored before reallocation of data. Will double when a reallocation is triggered
     * due to capacity being full.
     */
    std::size_t capacity_;

    /**
     * reallocate
     * @param n the new length of data to reallocate to
     */
    void reallocate(size_t n);

public:
    /**
     * Default constructor defaults to capacity of 0.
     */
    double_vector();

    /**
     * Set the capacity and size to this value and default initialize all values between.
     */
    double_vector(size_t capacity);

    /**
     * Copy constructor (not defaulted). Copies all elements from rhs to lhs.
     */
    double_vector(const double_vector &rhs);

    /**
     * Copy assignment operator. Copies all elements from rhs to lhs.
     */
    double_vector &operator=(const double_vector &rhs);

    /**
     * Cleans up all memory allocations. Clears memory and deletes pointer when done.
     */
    ~double_vector();

    // do we default move ctor/assignment or do we just not include them?

    // CAPACITY METHODS

    /**
     * size
     * @returns the size of the stored data
     */
    size_t size();

    /**
     * max_size
     * @returns the value of the largest amount of data that can be stored
     */
    size_t max_size();

    /**
     * capacity
     * @returns the current capacity before reallocation will occur
     */
    size_t capacity();

    /**
     * resize
     * @param n the vector length to resize to
     */
    void resize(size_t n);

    /**
     * resize
     * @param n the vector length to resize to
     * @param val the default initialization for any empty elements (instead of 0)
     */
    void resize(size_t n, double val);

    /**
     * empty
     * @returns true if there is no data currently stored in vector (size is 0), false otherwise
     */
    bool empty();

    /**
     * reserve
     * @param n the size to reallocate to if n is greater than current capacity
     */
    void reserve(size_t n);

    /**
     * shrink_to_fit
     * @brief reduces the capacity of vector to current size
     */
    void shrink_to_fit();

    // ELEMENT ACCESS
    /**
     * [] operator overload
     * @param n the index of value to be accessed
     * @return the value stored at index n
     */
    double &operator[](size_t n);

    /**
     * at
     * @param n the index of the value to be accessed
     * @throws range_errorwhen n is out of bounds
     */
    double &at(size_t n);

    /**
     * front
     * @returns reference to the first element in the vector
     */
    double &front();

    /**
     * back
     * @returns reference to the last element in the vector
     */
    double &back();

    /**
     * data
     * @returns pointer to the data array
     */
    double *data();

    // MODIFIERS
    /**
     * push_back
     * @param val the element to be added to the end of the vector
     */
    void push_back(const double &val);

    /**
     * pop_back
     * @brief removes the last element in the vector reducing size by one
     */
    void pop_back();

    /**
     * swap
     * @param other the contents to swap data vector with
     */
    void swap(double_vector &other);

    /**
     * clear
     * @brief empties the array of all values and sets the size to 0
     */
    void clear();

    // ITERATOR SUBCLASS
    class iterator
    {
        double *ptr;

    public:
        /**
         * pre-increment operator
         * @brief moves the iterator forward and returns
         */
        iterator &operator++();

        /**
         * post-increment operator
         * @brief moves the iterator forward one step but returns iterator before moving forward
         */
        iterator operator++(int);

        /**
         * pre-decrement operator
         * @brief moves the iterator backwards one step and returns
         */
        iterator &operator--();

        /**
         * post-decrement operator
         * @brief moves the iterator backwards one step but returns iterator before moving backward
         */
        iterator operator--(int);

        /**
         * de-reference operator
         * @returns the location of the data the iterator is looking at
         */
        double &operator*();

        /**
         * equality operator
         * @param iterator to compare equality (same position in vector, NOT value)
         * @returns true if they are at same position in vector, false otherwise
         */
        bool operator==(const iterator &) const;

        /**
         * in-equality operator
         * @param to compare in-equality (not same position in vector)
         * @returns trues if they are not in the same index or memory location
         */
        bool operator!=(const iterator &) const;

        /**
         * get_ptr
         * @returns pointer of iterator object
         */
        double *get_ptr();
    };

    // where do these go
    /**
     * begin
     * @returns a double_vector::iterator() that looks at the first value in the data array
     */
    iterator begin() const;

    /**
     * end
     * @returns a double_vector::iterator() that looks at the position one index past the last value in the data array
     */
    iterator end() const;
    
};

#endif