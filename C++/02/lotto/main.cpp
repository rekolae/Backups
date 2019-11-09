#include <iostream>

using namespace std;

int error (int a, int b);
void calculate_possibility (unsigned int a, unsigned int b);


int main ()
{
    int number_of_lotteryballs = 0;
    int number_of_drawn_balls = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> number_of_lotteryballs ;
    cout << "Enter the number of the drawn balls: ";
    cin >> number_of_drawn_balls;
    if (not error(number_of_lotteryballs, number_of_drawn_balls)) {
        calculate_possibility(number_of_lotteryballs, number_of_drawn_balls);
        exit (EXIT_SUCCESS);
    }

    else {
        exit (EXIT_FAILURE);
    }
}


int error (int lotteryballs, int drawn_balls)
{
    if (lotteryballs <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        return true;
    }

    else if (drawn_balls <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        return true;
    }

    else if (drawn_balls > lotteryballs) {
        cout << "At most the total number of balls can be drawn." << endl;
        return true;
    }

    else {
        return false;
    }
}


void calculate_possibility (unsigned int lotteryballs, unsigned int drawn_balls)
{
    unsigned long int upper_factorial = 1;
    unsigned long int drawn_balls_factorial = 1;
    unsigned long int lottery_drawn_factorial = 1;
    unsigned long int p = lotteryballs - drawn_balls;
    unsigned long int possibility = 0;

    for (unsigned int x = 1; x <= lotteryballs; x++) {
        upper_factorial = upper_factorial * x;
    }

    for (unsigned int x = 1; x <= p; x++) {
        lottery_drawn_factorial = lottery_drawn_factorial * x;
    }

    for (unsigned int x = 1; x <= drawn_balls; x++) {
        drawn_balls_factorial = drawn_balls_factorial * x;
    }
    possibility = upper_factorial / (lottery_drawn_factorial * drawn_balls_factorial);
    cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << possibility << endl;

}
