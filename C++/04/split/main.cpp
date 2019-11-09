#include <iostream>
#include <string>
#include <vector>


std::vector< std::string > split(std::string line, char separator, bool no_whitespace = false) {
    std::vector< std::string > vector;
    std::string::size_type separator_index = 0;
    std::string part = "";
    int separator_length = 1;
    if (not no_whitespace) {
        while ((separator_index = line.find(separator)) != std::string::npos) {
            part = line.substr(0, separator_index);
            vector.push_back(part);
            line.erase(0, separator_index + separator_length);
        }
        vector.push_back(line);
        return vector;
    }


    else {
        while ((separator_index = line.find(separator)) != std::string::npos) {
            part = line.substr(0, separator_index);
            if (part != "") {
                vector.push_back(part);
            }
            line.erase(0, separator_index + separator_length);
        }
        if (line != "") {
            vector.push_back(line);
        }
        return vector;
    }
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}
