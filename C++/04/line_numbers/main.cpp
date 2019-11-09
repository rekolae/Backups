#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string file_name_read;
    string file_name_write;
    string line;
    int line_number = 1;

    cout << "Input file: ";
    getline(cin, file_name_read);

    cout << "Output file: ";
    getline(cin, file_name_write);

    ifstream file_read(file_name_read);


    if (file_read) {
        ofstream file_write(file_name_write);
        while (getline(file_read, line)) {
            file_write << line_number << " " << line << endl;
            line_number++;
        }
        file_read.close(), file_write.close();
        exit(EXIT_SUCCESS);
    }

    else {
        cout << "Error! The file "<< file_name_read << " cannot be opened." << endl;
        exit(EXIT_FAILURE);

    }
}
