#include <iostream>
#include <string>

int main()
{
    std::string nimi = "";
    std::cout << "Enter your name: ";
    getline(std::cin, nimi);

    int ika = 0;
    std::cout << "Enter your age: ";
    std::cin >> ika;

    std::cout << "Pleased to meet you, " << nimi << "!" << std::endl;
    std::cout << "In your next birthday you'll be " << ika + 1 << " years old!" << std::endl;
    return EXIT_SUCCESS;
}
