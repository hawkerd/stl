#include <cstddef>
#include <stdexcept>
#include <limits>
#include <initializer_list>
#include <iterator>


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
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
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
         * @brief Constructs a vector from an existing vector.
         * @param other The exisiting vector.
         */
        Vector(const Vector& other) {
            /* Copy size and capacity */
            _size = other._size;
            _capacity = other._capacity;

            /* Allocate memory for the new vector */
            contents = nullptr;
            if (_size > 0) {
                contents = new T[_capacity];
            }

            /* Initialize elements */
            for (size_t i = 0; i < _size; i++) {
                contents[i] = other.contents[i];
            }
        }

        /**
         * @brief Constructs a Vector from an initializer list.
         * @param list The initializer list used to construct the Vector.
         */
        Vector(initializer_list<T> list) {
            /* Update size and capacity */
            _size = list.size();
            _capacity = _size;

            /* Allocate memory */
            contents = nullptr;
            if (_size > 0) {
                contents = new T[_size];
            }

            /* Initialize elements */
            size_t i = 0;
            for (auto it = list.begin(); it != list.end(); it++, i++) {
                contents[i] = *it;
            }
        }


        /**
         * @brief Assigns the contents of one vector to another
         * @param other The vector being copied
         */
        Vector& operator=(const Vector& other) {
            /* Check for self assignment */
            if (this == &other) {
                return *this;
            }

            /* Clean up memory */
            delete[] contents;

            /* Copy over fields */
            _size = other._size;
            _capacity = other._capacity;
            
            /* Allocate memory according to _capacity */
            contents = new T[_capacity];

            /* Copy over elements */
            for (size_t i = 0; i < _size; i++) {
                contents[i] = other.contents[i];
            }

            /* Return a reference */
            return *this;
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
         * @brief Returns a constant reference to the element at the specified index with bounds checking.
         * @param index The index of the element to access.
         * @return A constant reference to the element at the given index.
         * @throw std::out_of_range if index is out of bounds.
         */
        const T& at(size_t index) const {
            /* Return a constant reference if the element is in bounds, or throw an exception */
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
         * @brief Returns a constant reference to the element at the specified index.
         * @param index The index of the element to access.
         * @return A reference to the element at the given index
         */
        const T& operator[](size_t index) const {
            /* Return a constant reference */
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
         * @brief Returns a constant pointer to the underlying array.
         * @return A constant pointer to the first element in the array.
         */
        const T* data() const {
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
         * @brief Returns a constant reference to the first element in the vector.
         * @return A constant reference to the first element in the vector.
         * @throws std::out_of_range If the vector is empty.
         */
        const T& front() const {
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

        /**
         * @brief Returns a reference to the last element in the vector.
         * @return A reference to the last element.
         * @throws std::out_of_range If the vector is empty.
         */
        const T& back() const {
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
        size_t size() const {
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
            /* Todo: call T destructor */

            /* Update size */
            _size = new_size;
        }

        /**
         * @brief Returns the current capacity of the vector.
         * @return The total capacity of the vector.
         */
        size_t capacity() const {
            return _capacity;
        }

        /**
         * @brief Returns whether the vector is empty.
         * @return A boolean representing whether the vector is empty.
         */
        bool empty() const {
            return (size == 0);
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
                if (_capacity == 0) {
                    reserve(2);
                } else {
                    reserve(_capacity * 2);
                }
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
            } else if (position == _size) {
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
            /* Bounds check */
            if (position > _size) {
                throw out_of_range("Out of range");
            }
            
            /* Reserve memory */
            if (_capacity < count + _size) {
                reserve(count + _size);
            }

            /* Shift existing elements */
            for (size_t i = _size; i > position; i--) {
                contents[i + count - 1] = contents[i - 1];
            }

            /* Add new elements */
            for (size_t i = position; i < position + count; i++) {
                contents[i] = value;
            }

            /* Update size */
            _size += count;
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
            for (size_t i = _size; i > position; i--) {
                contents[i + d - 1] = contents[i - 1];
            }

            /* Add new elements */
            size_t i = position;
            for (It it = first; it != last; it++, i++) {
                contents[i] = *it;
            }

            /* Update size */
            _size += d;
        }

        /**
         * @brief Erases an element at the specified position.
         * @param position The position of the element to erase.
         * @throws std::out_of_range
         */
        void erase(size_t position) {
            if (position >= _size) {
                throw out_of_range("Out of bounds");
            }
            for (size_t i = position; i < _size - 1; i++) {
                contents[i] = contents[i+1];
            }
            _size--;
        }

        /**
         * @brief Removes all elements in a range.
         * @param first The first element to erase (inclusive).
         * @param last The last element to erase (exclusive).
         * @throws std::out_of_range
         */
        void erase(size_t first, size_t last) {
            /* Boundary check */
            if ((first >= _size ) || (last > _size) || (last < first)) {
                throw out_of_range("Out of range");
            }

            /* Copy elements */
            size_t j = first;
            for (size_t i = last; i < _size; i++, j++) {
                contents[j] = contents[i];
            }

            /* Update size */
            _size -= (last - first);
        }
        
        /**
         * @brief Swaps the contents of two vectors.
         * @param other The other vector to be swapped.
         */
        void swap(Vector& other) noexcept {
            /* Allocate temporary variables */
            T* temp_data = contents;
            size_t temp_size = _size;
            size_t temp_capacity = _capacity;

            /* Swap */
            contents = other.contents;
            _size = other._size;
            _capacity = other._capacity;

            other.contents = temp_data;
            other._size = temp_size;
            other._capacity = temp_capacity;
        }

        /**
         * @brief Constructs an element at the specified position within the vector.
         * @param pos The position to construct the element.
         * @param args Arguments passed to the object constructor.
         */
        template <typename... Args>
        void emplace(size_t pos, Args&&... args) {
            /* Bounds check */
            if (pos > _size) {
                throw out_of_range("Out of range");
            } else if (pos == _size) {
                emplace_back(std::forward<Args>(args)...);

            }

            /* Reserve space */
            reserve(_capacity > 0 ? capacity * 2 : 1);

            /* Shift elements */
            for (size_t i = _size; i > pos; i--) {
                contents[i] = contents[i-1];
            }

            /* Construct element */
            new (&contents[pos]) T(std::forward<Args>(args)...);

            /* Update size */
            _size++;
        }

        /**
         * @brief Constructs an elements at the end of the vector.
         * @param args Arguments passed to the object constructor.
         */
        template <typename... Args>
        void emplace_back(Args&&... args) {
            /* Reserve space if necessary */
            if (_size == _capacity) {
                if (_capacity == 0) {
                    reserve(2);
                } else {
                    reserve(_capacity * 2);
                }
            }

            /* Construct element */
            new (&contents[_size]) T(std::forward<Args>(args)...);

            /* Update size */
            _size++;
        }
        
        /**
         * @brief Clears the vector and sets its size to 0.
         */
        void clear() {
            _size = 0;
        }
        /** @} */
    
    /**
     * @name Iterators
     * @{
     */

    iterator begin() { return contents; }

    const_iterator begin() const { return contents; }

    iterator end() { return contents + _size; }

    const_iterator end() const { return contents + _size; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    const_iterator cbegin() const { return begin(); }

    const_iterator cend() const { return end(); }

    const_reverse_iterator crbegin() const { return rbegin(); }

    const_reverse_iterator crend() const { return rend(); }

    /** @} */
};