#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for (int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}


int same_values(std::vector< int > ints)
{
    int first_integer = ints.front();

    for (int vector_integer : ints) {
        if (first_integer != vector_integer) {
            return false;
        }
    }
    return true;
}


int is_ordered_ascending(std::vector< int > ints)
{
    int previous_integer = ints.front();
    int next_integer;
    int size = ints.size();

    for (int index = 1; index < size; index++) {
        next_integer = ints.at(index);

        if (previous_integer > next_integer) {
            return false;
        }

        else {
            previous_integer = next_integer;
        }
    }
    return true;
}


int is_arithmetic_series(std::vector< int > ints)
{
    int previous_subtr = ints.at(0) - ints.at(1);
    int next_subtr;
    int size = ints.size();

    for (int index = 1; index < size - 1; index++) {
        next_subtr = ints.at(index) - ints.at(index + 1);

        if (previous_subtr != next_subtr) {
            return false;
        }
        else {
            previous_subtr = next_subtr;
        }
    }
    return true;
}


int is_geometric_series(std::vector< int > ints)
{
    double previous_ratio = double(ints.at(0)) / double(ints.at(1));
    double next_ratio;
    int size = ints.size();

    for (int index = 1; index < size - 1; index++) {
        next_ratio = double(ints.at(index)) / double(ints.at(index + 1));

        if (std::find(ints.begin(), ints.end(), 0) != ints.end()) {
            return false;
        }
        else {
            if (previous_ratio != next_ratio) {
                return false;
            }
            else {
                previous_ratio = next_ratio;
            }
        }
    }
    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if (same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if (is_ordered_ascending(integers))
        std::cout << "The integers are in an ascending order" << std::endl;
    else
        std::cout << "The integers are not in an ascending order" << std::endl;

    if (is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if (is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
