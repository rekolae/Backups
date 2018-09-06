#include "player.hh"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string name):
    name_(name) {
    points_ = 0;
}


string Player::get_name() {
    return name_;
}


int Player::get_points() {
    return points_;
}


int Player::has_won() {
    if (points_ == 50) {
        return true;
    }
    return false;
}


void Player::add_points(int points) {
    points_ += points;
    if (points_ > 50) {
        cout << name_ << " gets penalty points!" << endl;
        points_ = 25;
    }
}
