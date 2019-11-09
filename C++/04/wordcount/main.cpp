#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>

int main()
{
    std::map< std::string, std::set < int > > counter;
    std::string input_file;
    int row = 1;
    std::string line;
    int whitespace_index;
    std::string part;
    std::map< std::string, std::set < int > >::iterator iter_counter;
    std::set < int >::iterator iter_numbers;
    std::string numbers;
    long int end = std::string::npos;

    std::cout << "Input file: ";
    std::cin >> input_file;
    std::ifstream read_file(input_file);

    if (read_file) {
        while (getline(read_file, line)) {
            while ((whitespace_index = line.find(" ")) != end) {
                part = line.substr(0, whitespace_index);
                counter[part].insert(row);
                line.erase(0, whitespace_index + 1);
            }

            counter[line].insert(row);
            row++;
        }
        iter_counter = counter.begin();
        while (iter_counter != counter.end()) {
            numbers.clear();
            for (iter_numbers = iter_counter->second.begin(); iter_numbers != iter_counter->second.end(); ++iter_numbers ) {
                if (iter_numbers == iter_counter->second.begin()) {
                    numbers += std::to_string(*iter_numbers);
                }
                else {
                    numbers += ", " + std::to_string(*iter_numbers);
                }
            }
            std::cout << iter_counter->first << " " << iter_counter->second.size() << ": " << numbers << std::endl;
            iter_counter++;
        }
    }

    else {
        std::cout << "Error! The file " << input_file << " cannot be opened." << std::endl;
        exit(EXIT_FAILURE);
    }
}
