#include <cstddef>
#include <stdexcept>

using namespace std;

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
        // Default constructor
        Vector(size_t size = 0, const T& value = T())
            : _size(size), _capacity(size) {
            
            // Allocate memory
            contents = nullptr;
            if (_size > 0) {
                contents = new T[_size];
            }

            // Iterate over the array and initialize values
            for (size_t i = 0; i < _size; i++) {
                contents[i] = value;
            }
        }

        // Default destructor
        ~Vector() {
            delete[] contents;
            contents = nullptr;
        }

        // Indexing using at()
        T& at(size_t index) {
            // Bounds checking
            if (index >= _size) {
                throw out_of_range("Index out of range");
            } else {
                return contents[index];
            }
        }

        // Indexing using []
        T& operator[](size_t index) { //todo: update capacity, error checking
            return contents[index];
        }

        size_t size() {
            return _size;
        }

        size_t capacity() {
            return _capacity;
        }

        T* data() {
            return this->contents;
        }


        // Reserve - increase the capacity of the vector without changing the contents or size
        void reserve(size_t new_capacity) {
            if (new_capacity >= _capacity) {
                // Allocate new memory
                T* new_contents = new T[new_capacity];

                // Copy over contents
                for (size_t i = 0; i < _size; i++) {
                    new_contents[i] = contents[i];
                }

                // Update pointers
                delete[] contents;
                contents = new_contents;

                // Update capacity
                _capacity = new_capacity;
            }

        }


        // Resize - changes the vectors size. Will delete elements or fill them with T() if necessary
        void resize(size_t new_size, const T& value = T()) {
            if (new_size > _size) {
                reserve(new_size);
                for (size_t i = _size; i < new_size; i++) {
                    contents[i] = value;
                }
            }
            _size = new_size;
        }

        void push_back(const T& value) {
            if (_size == _capacity) {
                reserve(_capacity * 2);
            }

            contents[_size] = value;
            _size++;
        }

        void pop_back() {
            if (_size > 0) {
                _size--;
            }
        }

        T& back() {
            if (_size > 0) {
                return contents[_size - 1];
            } else {
                throw std::out_of_range("Vector is empty");
            }
        }

        T& front() {
            if (_size > 0) {
                return contents[0];
            } else {
                throw std::out_of_range("Vector is empty");
            }
        }

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

        void clear() {
            _size = 0;
        }

    
};