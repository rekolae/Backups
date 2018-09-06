#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());

        if (not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }

    if (not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }

    return result;
}


void print_subnet(std::string id, std::map< std::string, std::vector< std::string > > &people, int loop_number = 0)
{
    loop_number++;

    if (people.find(id) != people.end()) {
        int size = people.at(id).size();
        if (size != 0) {
            for (int index = 0; index < size; index++) {
                for (int x = 0; x < loop_number; x++) {
                    std::cout << "..";
                }

                std::cout << people.at(id).at(index) << std::endl;
                print_subnet(people.at(id).at(index), people, loop_number);
            }
        }
    }
}


int count_subnet_size(std::string id, std::map< std::string, std::vector< std::string > > &people,  int &subnet_size, int loop_number = 0)
{
    loop_number++;

    if (people.find(id) != people.end()) {
        int size = people.at(id).size();
        if (size != 0) {
            for (int index = 0; index < size; index++) {
                subnet_size++;
                for (int x = 0; x < loop_number; x++) {
                }

                count_subnet_size(people.at(id).at(index), people, subnet_size, loop_number);
            }
        }
    }
    return subnet_size;
}

void count_subnet_depth(std::string id, std::map< std::string, std::vector< std::string > > &people,  std::vector< int > &subnet_depth, int loop_number = 0)
{
    loop_number++;

    if (people.find(id) != people.end()) {
        int size = people.at(id).size();
        if (size != 0) {
            for (int index = 0; index < size; index++) {
                for (int x = 0; x < loop_number; x++) {
                }

                count_subnet_depth(people.at(id).at(index), people, subnet_depth, loop_number);
            }
        }
    }
    subnet_depth.push_back(loop_number);
}


int main()
{
    std::map< std::string, std::vector< std::string > > people;

    while (true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if (command == "S" or command == "s") {
            if (parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }

            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if (people.find(id1) == people.end()) {
                people[id1];
            }

            people[id1].push_back(id2);
        }

        else if (command == "P" or command == "p"){
            if (parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }

            std::string id = parts.at(1);

            std::cout << id << std::endl;
            print_subnet(id, people);
        }

        else if (command == "C" or command == "c"){
            if (parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }

            std::string id = parts.at(1);
            int subnet_size = 0;
            std::cout << count_subnet_size(id, people, subnet_size) << std::endl;
        }

        else if (command == "D" or command == "d"){
            if (parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }

            std::string id = parts.at(1);
            std::vector< int > subnet_depth;
            count_subnet_depth(id, people, subnet_depth);
            std::sort(subnet_depth.begin(), subnet_depth.end());
            std::cout << subnet_depth.back() << std::endl;


        }

        else if (command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        }

        else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
