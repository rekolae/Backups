#include <iostream>

int main()
{
    int numbers = 0;
    int x = 1;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers;

    while ( x <= numbers) {
        if ( x % 3 == 0) {
            if ( x % 7 == 0) {
                std::cout << "zip boing" << std::endl;
                x++;
            }

            else {
                std::cout << "zip" << std::endl;
                x++;
            }
        }

        else if ( x % 7 == 0 ) {
                std::cout << "boing" << std::endl;
                x++;
            }

        else {
            std::cout << x << std::endl;
            x++;
        }
    }
}
