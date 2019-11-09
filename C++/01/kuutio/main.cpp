#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    int cube = 0;
    cout << "Enter a number: ";
    cin >> number;
    cube = number * number * number;

    if ( cube < 0 || number > cube) {
        cout << "Error! The cube of " << number << " is not " << cube <<  "." << endl;
    }

    else {
        cout << "The cube of " << number << " is " << cube <<  "." << endl;
    }
}
