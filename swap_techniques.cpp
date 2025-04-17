#include <iostream>
#include <algorithm> // For std::swap
#include <tuple>     // For tuple assignment
#include <utility>   // For std::exchange

// Function prototypes
void swap_with_xor(int x, int y);
void swap_with_third_variable(int x, int y);
void swap_with_addition(int x, int y);
void swap_with_multiplication(int x, int y);
void swap_with_subtraction(int x, int y);
void swap_with_division(int x, int y);
void swap_with_bitwise_and(int x, int y);
void swap_with_bitwise_or(int x, int y);
void swap_with_std_swap(int x, int y);
void swap_with_tuple(int x, int y);
void swap_with_pointers(int x, int y);
void swap_with_array(int x, int y);
void swap_with_exchange(int x, int y);

int main() {
   
    int a = 10, b = 20;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap_with_xor(a, b);
    swap_with_third_variable(a, b);
    swap_with_addition(a, b);
    swap_with_multiplication(a, b);
    swap_with_subtraction(a, b);
    swap_with_division(a, b);
    swap_with_bitwise_and(a, b);
    swap_with_bitwise_or(a, b);
    swap_with_std_swap(a, b);
    swap_with_tuple(a, b);
    swap_with_pointers(a, b);
    swap_with_array(a, b);
    swap_with_exchange(a, b);
    return 0;
}

void swap_with_xor(int x, int y) {
    x ^= y;
    y ^= x;
    x ^= y;
    std::cout << "After swap using XOR: x = " << x << ", y = " << y << std::endl;
}

void swap_with_third_variable(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
    std::cout << "After swap using third variable: x = " << x << ", y = " << y << std::endl; 
}

void swap_with_addition(int x, int y) {
    x = x + y;
    y = x - y;
    x = x - y;
    std::cout << "After swap using addition: x = " << x << ", y = " << y << std::endl; 
}

void swap_with_multiplication(int x, int y) {
    x = x * y;
    y = x / y;
    x = x / y;
    std::cout << "After swap using multiplication: x = " << x << ", y = " << y << std::endl; 
}   

void swap_with_subtraction(int x, int y) {
    x = x - y;
    y = x + y;
    x = y - x;
    std::cout << "After swap using subtraction: x = " << x << ", y = " << y << std::endl; 
}

void swap_with_division(int x, int y) {
    if (y == 0 || x == 0) {
        std::cout << "After swap using division: ERROR (division by zero)" << std::endl;
        return;
    }
    x = x / y;
    y = x * y;
    if (x == 0) {
        std::cout << "After swap using division: ERROR (division by zero)" << std::endl;
        return;
    }
    x = y / x;
    std::cout << "After swap using division: x = " << x << ", y = " << y << std::endl; 
}

void swap_with_bitwise_and(int x, int y) {
    std::cout << "After swap using bitwise AND (INCORRECT, does not swap): x = " << (x & y) << ", y = " << (x & y) << std::endl; 
}

void swap_with_bitwise_or(int x, int y) {
    std::cout << "After swap using bitwise OR (INCORRECT, does not swap): x = " << (x | y) << ", y = " << (x | y) << std::endl; 
}

// New swap techniques
void swap_with_std_swap(int x, int y) {
    std::swap(x, y);
    std::cout << "After swap using std::swap: x = " << x << ", y = " << y << std::endl;
}

void swap_with_tuple(int x, int y) {
#if __cplusplus >= 201703L
    std::tie(x, y) = std::make_tuple(y, x);
    std::cout << "After swap using tuple assignment: x = " << x << ", y = " << y << std::endl;
#else
    std::cout << "Tuple assignment requires C++17 or higher." << std::endl;
#endif
}

void swap_with_pointers(int x, int y) {
    int* px = &x;
    int* py = &y;
    int temp = *px;
    *px = *py;
    *py = temp;
    std::cout << "After swap using pointers: x = " << x << ", y = " << y << std::endl;
}

void swap_with_array(int x, int y) {
    int arr[2] = {x, y};
    int temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
    std::cout << "After swap using array: x = " << arr[0] << ", y = " << arr[1] << std::endl;
}

void swap_with_exchange(int x, int y) {
#if __cplusplus >= 201402L
    x = std::exchange(y, x);
    std::cout << "After swap using std::exchange: x = " << x << ", y = " << y << std::endl;
#else
    std::cout << "std::exchange requires C++14 or higher." << std::endl;
#endif
}