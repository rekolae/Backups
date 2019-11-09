#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

int sum_recursive(std::vector< int > int_vector) {
    int sum = 0;
    int size = int_vector.size();

    if (size == 1) {
        sum = int_vector.at(0);
        return sum;
    }

    else if (size == 2) {
        sum = int_vector.at(0) + int_vector.at(1);
        return sum;
    }

    else {
        sum = int_vector.at(0) + int_vector.at(size - 1);
        int_vector.at(size - 1) = sum;
        int_vector.erase(int_vector.begin());
        return sum_recursive(int_vector);
    }
}


int main()
{
    std::cout << "Enter integers separated by spaces: ";
    std::string line;
    getline(std::cin, line);
    std::vector<std::string> strings = split(line, ' ', true);
    std::vector<int> integers;
    for(auto s : strings){
        integers.push_back(stoi(s));
    }

    std::cout << "Sum: " << sum_recursive(integers) << std::endl;
}
