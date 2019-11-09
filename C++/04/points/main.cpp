#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main() {
    string file_to_read;
    string line;
    map< string, int > points;
    map< string, int >::iterator iter;
    std::string::size_type separator_index = 0;
    std::string part = "";
    vector< string > parts;

    cout << "Input file: ";
    getline(cin, file_to_read);

    ifstream file_read(file_to_read);

    if (file_read) {
        while (getline(file_read, line)) {
            while ((separator_index = line.find(":")) != std::string::npos) {
                part = line.substr(0, separator_index);
                parts.push_back(part);
                line.erase(0, separator_index + 1);
                parts.push_back(line);
                string name = parts.at(0);
                int name_points = stoi (parts.at(1));
                parts.clear();

                if (points.find(name) != points.end()) {
                    points.at(name) += name_points;

                }

                else {
                    points.insert({name, name_points});
                }
            }     
        }
        iter = points.begin();
        cout << "Final scores:" << endl;
        while (iter != points.end()) {
            cout << iter->first << ": " << iter->second << endl;
            iter++;
        }
    }

    else {
        cout << "Error! The file "<< file_to_read << " cannot be opened." << endl;
        exit(EXIT_SUCCESS);
    }
}
