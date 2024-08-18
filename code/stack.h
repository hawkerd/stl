#include "vector.h"

using namespace std;

/**
 * @class Stack
 * @brief A last in - first out data structure.
 * 
 * The Stack template class is a container that manages a last in -
 * first out (LIFO) data structure. It is meant to replicate the C++ 
 * STL std::stack<T>.
 * 
 * @tparam T The type of data stored in the stack.
 */
template <typename T>
class Stack {
    private:
        // Underlying container
        Vector<T> v;

    public:

        /**
         * @brief Pushes an element onto the top of the stack.
         * @param value The value of the element to push.
         */
        void push(const T& value) {
            v.push_back(value);
        }

        /**
         * @brief Pops an element off the top of the stack.
         * @throws std::out_of_range
         */
        void pop() {
            if (v.empty()) {
                throw out_of_range("Popping from an empty stack");
            }
            v.pop_back();
        }

        /**
         * @brief Returns a reference to the element at the top of the stack.
         * @throws std::out_of_range
         */
        T& top() {
            if (v.empty()) {
                throw out_of_range("Out of range");
            }
            return v.back();
        }

        /**
         * @brief Returns a constant reference to the element at the top of the stack.
         * @throws std::out_of_range
         */
        const T& top() const {
            if (v.empty()) {
                throw out_of_range("Out of range");
            }
            return v.back();
        }

        /**
         * @brief Returns a boolean to indicate whether the stack is empty.
         */
        bool empty() {
            return v.empty();
        }

        /**
         * @brief Returns the size of the stack.
         */
        size_t size() {
            return v.size();
        }

        /**
         * @brief Swaps the contents of one stack with another.
         */
        void swap(Stack& other) {
            v.swap(other.v);
        }
};