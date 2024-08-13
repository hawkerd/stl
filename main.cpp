#include <iostream>
#include "vector.h"  // Assuming your vector class is in this header

int main() {
    // Create a vector of integers
    Vector<int> vec;

    // Test initial push_back()
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "Initial vector after push_back operations:\n";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }
    std::cout << "Initial capacity: " << vec.capacity() << std::endl;

    // Test shrinking
    vec.resize(5, 100);  // Expanding size
    std::cout << "Capacity after resizing to 5: " << vec.capacity() << std::endl;
    vec.shrink_to_fit(); // Shrink to fit the size
    std::cout << "Capacity after shrink_to_fit: " << vec.capacity() << std::endl;

    std::cout << "Vector after shrinking:\n";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }

    // Test shrinking with a smaller size
    vec.resize(2);  // Shrink size to 2
    std::cout << "Vector after resizing to 2:\n";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << std::endl;
    }
    std::cout << "Capacity before shrink_to_fit: " << vec.capacity() << std::endl;
    vec.shrink_to_fit();  // Shrink capacity to match size
    std::cout << "Capacity after shrink_to_fit: " << vec.capacity() << std::endl;

    // Test shrinking an empty vector
    vec.clear();
    std::cout << "Vector after clearing (size should be 0): " << vec.size() << std::endl;
    std::cout << "Capacity before shrink_to_fit on empty vector: " << vec.capacity() << std::endl;
    vec.shrink_to_fit();  // Shrink capacity to match size
    std::cout << "Capacity after shrink_to_fit on empty vector: " << vec.capacity() << std::endl;

    return 0;
}
