#include <iostream>

using namespace std;


int main() {
    int luku1;
    int luku2 = 111;
    int luku3;
    int *osoitin1 = new int;
    int *osoitin2 = new int(222);
    cout << "Input a number: ";
    cin >> luku3;

    cout << luku1 << " "
         << luku2 << " "
         << luku3 << " "
         << *osoitin1 << " "
         << *osoitin2 << endl;

    delete osoitin1;

    *osoitin1 = 333;
}
