#include <iostream>

int main() {
    char c;
    int current_depth = 0, complexity = 0;
    while (std::cin >> c) {
        if (c == '{') {
            current_depth++;
            complexity += current_depth;
        }
        else if (c == '}') 
            current_depth--; 
    }
    std::cout << complexity;
}