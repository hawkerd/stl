#include <cstddef>
#include <stdexcept>
#include <limits>

using namespace std;

/**
 * @class Vector
 * @brief A dynamically resizable array implementation
 * 
 * The Vector template class is a container that manages a dynamically
 * allocated array. It is meant to replicate the C++ STL std::vector<T>
 * 
 * @tparam T The type of data stored in the vector
 */
template <typename T>
class Vector {
    private:
        // Current size of the vector (how many elements are in the vector)
        size_t _size;

        // Current capacity of the vector (how much memory is allocated)
        size_t _capacity;

        // Pointer to the start of our array
        T* contents;

    public:

        /**
         * @name Constructors and Destructors
         * @{
         */
        /**
         * @brief Constructs a Vector with the given size and initialization.
         * @param size The initial size of the vector.
         * @param value The value each element is initialized to.
         */
        Vector(size_t size = 0, const T& value = T())
            : _size(size), _capacity(size) {
            
            /* Allocate memory */
            contents = nullptr;
            if (_size > 0) {
                contents = new T[_size];
            }

            /* Initialize the vector */
            for (size_t i = 0; i < _size; i++) {
                contents[i] = value;
            }
        }

        /**
         * @brief Destroys the Vector and deallocates memory.
         */
        ~Vector() {
            delete[] contents;
            contents = nullptr;
        }
        /** @} */


        /**
         * @name Element Access
         * @{
         */
        
        /**
         * @brief Returns a reference to the element at the specified index with bounds checking.
         * @param index The index of the element to access.
         * @return A reference to the element at the given index
         * @throws std::out_of_range if index is out of bounds
         */
        T& at(size_t index) {
            /* Return a reference if the element is in bounds, or throw an exception */
            if (index >= _size) {
                throw out_of_range("Index out of range");
            } else {
                return contents[index];
            }
        }

        /**
         * @brief Returns a reference to the element at the specified index.
         * @param index The index of the element to access.
         * @return A reference to the element at the given index
         */
        T& operator[](size_t index) {
            /* Return a reference */
            return contents[index];
        }

        /**
         * @brief Returns a pointer to the underlying array.
         * @return A pointer to the first element in the array.
         */
        T* data() {
            return this->contents;
        }

        /**
         * @brief Returns a reference to the first element in the vector.
         * @return A reference to the first element in the vector.
         * @throws std::out_of_range If the vector is empty.
         */
        T& front() {
            if (_size > 0) {
                return contents[0];
            } else {
                throw std::out_of_range("Vector is empty");
            }
        }

        /**
         * @brief Returns a reference to the last element in the vector.
         * @return A reference to the last element.
         * @throws std::out_of_range If the vector is empty.
         */
        T& back() {
            if (_size > 0) {
                return contents[_size - 1];
            } else {
                throw std::out_of_range("Vector is empty");
            }
        }
        /** @} */

        /**
         * @name Capacity
         * @{
         */
        /**
         * @brief Returns the current size of the vector.
         * @return The number of elements in the vector.
         */
        size_t size() {
            return _size;
        }

        /**
         * @brief Returns the maximum number of elements the vector can hold
         * @return The maximum number of elements
         */
        size_t max_size() const {
            return numeric_limits<size_t>::max() / sizeof(T);
        }

        /**
         * @brief Resizes the vector to the specified size.
         * @param new_size The new size of the vector.
         * @param value The value to initialize new elements with.
         */
        void resize(size_t new_size, const T& value = T()) {
            /* If we are expanding, reserve space and copy elements */
            if (new_size > _size) {
                reserve(new_size);
                for (size_t i = _size; i < new_size; i++) {
                    contents[i] = value;
                }
            }
            /* Update size */
            _size = new_size;
        }

        /**
         * @brief Returns the current capacity of the vector.
         * @return The total capacity of the vector.
         */
        size_t capacity() {
            return _capacity;
        }

        /**
         * @brief Returns whether the vector is empty.
         * @return A boolean representing whether the vector is empty.
         */
        bool empty() {
            if (size == 0) {
                return true;
            } else {
                return false;
            }
        }

        /**
         * @brief Increases the capacity of the vector without changing its size.
         * @param new_capacity The new capacity of the vector.
         */
        void reserve(size_t new_capacity) {
            if (new_capacity >= _capacity) {
                /* Allocate new memory */
                T* new_contents = new T[new_capacity];

                /* Copy over contents */
                for (size_t i = 0; i < _size; i++) {
                    new_contents[i] = contents[i];
                }

                /* Update pointers */
                delete[] contents;
                contents = new_contents;

                /* Update capacity */
                _capacity = new_capacity;
            }

        }

        /**
         * @brief Reeduces the capacity of the vector to match its size.
         */
        void shrink_to_fit() { 
            if (_capacity > _size) {
                T* new_contents = new T[_size];
                for (size_t i = 0; i < _size; i++) {
                    new_contents[i] = contents[i];
                }
                delete[] contents;
                contents = new_contents;
                _capacity = _size;
            }
        }
        /** @} */

        /**
         * @name Modifiers
         * @{
         */
        /**
         * @brief Assigns the vector a new size and contents.
         * @param count The new size of the vector.
         * @param value The new value of each element in the vector.
         */
        void assign(size_t count, const T& value) {
            /* Allocate memory if necessary */
            reserve(count);

            /* Overwrite all values */
            for (size_t i = 0; i < count; i++) {
                contents[i] = value;
            }

            /* Update size */
            _size = count;
        }

        /**
         * @brief Assigns the vector a new size and values from between two iterators.
         * @param first The beginning iterator.
         * @param last The ending iterator.
         */
        template <typename It>
        void assign(It first, It last) {
            /* Allocate memory if necessary */
            reserve(distance(first, last));

            /* Overwrite all values */
            size_t i = 0;
            for (It it = first; it != last; it++, ++i) {
                contents[i] = *it;
            }

            /* Update size */
            _size = distance(first, last);
        }

        /**
         * @brief Adds an element to the vector.
         * @param value The value to add.
         */
        void push_back(const T& value) {
            /* Reserve space if necessary */
            if (_size == _capacity) {
                reserve(_capacity * 2);
            }
            
            /* Add on the element and update size */
            contents[_size] = value;
            _size++;
        }

        /**
         * @brief Removes the last element from the vector.
         */
        void pop_back() {
            if (_size > 0) {
                _size--;
            }
        }
        
        /**
         * @brief Inserts element at a specified position.
         * @param position Position to insert the element at.
         * @param value The value to insert.
         * @throws out_of_range
         */
        void insert(size_t position, const T& value) {
            /* Bounds check */
            if (position > _size) {
                throw out_of_range("Out of range");
            } else if (position == size) {
                push_back(value);
                return;
            }

            /* Reserve memory if necessary */
            if (_size == _capacity) {
                reserve(_capacity * 2);
            }

            /* Shift elements */
            for (size_t i = _size; i > position; i--) {
                contents[i] = contents[i-1];
            }

            /* Insert element */
            contents[position] = value;
            _size++;
        }

        /**
         * @brief Insert multiple of the same element at a specified position.
         * @param position The position to insert the element at.
         * @param count How many of the same element to insert.
         * @param value The value to insert.
         */
        void insert(size_t position, size_t count, const T& value) {
            for (size_t i = 0; i < count; i++) {
                insert(position, value);
            }
        }
        
        /**
         * @brief Inserts the values betweeen two iterators at a specified position.
         * @param position The position to insert elements at.
         * @param first The first iterator.
         * @param last The last iterator.
         */
        template <typename It>
        void insert(size_t position, It first, It last) {
            /* Bounds check */
            if (position > _size) {
                throw out_of_range("Out of range");
            }

            size_t d = distance(first, last);

            /* Reserve memory if necessary */
            if (_capacity < d + _size) {
                reserve(d + _size);
            }

            /* Shift existing elements */
            for (size_t i = d; i > 0; i--) {
                contents[i] = contents[i - d]; //todo: fix this loop
            }

            /* Add new elements */
            size_t i = position;
            for (It it = first; it != last; it++, i++) {
                contents[i] = *it;
            }

            /* Update size */
            _size += d;
        }


        /** @} */

        /**
         * @brief Clears the vector and sets its size to 0.
         */
        void clear() {
            _size = 0;
        }

    
};