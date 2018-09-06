#include "cards.hh"
#include <iostream>

Cards::Cards(): firstAddress_ (nullptr) {

}

void Cards::add (int id)
{
    Card_data* newAddress = new Card_data {id, nullptr, nullptr};
    if (firstAddress_ == nullptr) {
        firstAddress_ = newAddress;
        lastAddress_ = newAddress;
    }

    else {
        newAddress->next = lastAddress_;
        lastAddress_->previous = newAddress;
        lastAddress_ = newAddress;
    }
}

void Cards::print_from_top_to_bottom (std::ostream &s)
{
    Card_data* addressToPrint = lastAddress_;
    int number = 1;

    if (addressToPrint == nullptr) {
        s << "";
    }

    else {
        while (addressToPrint != nullptr) {
            s << number << ": " << addressToPrint->data << std::endl;
            ++number;
            addressToPrint = addressToPrint->next;
        }
    }
}

bool Cards::remove (int &id)
{
    if (firstAddress_ == nullptr) {
        return false;
    }

    Card_data* addressToDelete = lastAddress_;
    id = lastAddress_->data;

    if (firstAddress_ == lastAddress_) {
        firstAddress_ = nullptr;
        lastAddress_ = nullptr;
    }

    else {
        lastAddress_ = lastAddress_->next;
    }

    delete addressToDelete;
    return true;
}

bool Cards::bottom_to_top()
{
    if (firstAddress_ == nullptr) {
        return false;
    }

    else if (lastAddress_ == firstAddress_) {
        return true;
    }

    Card_data* addressOfBottom = firstAddress_;
    addressOfBottom->previous->next = nullptr;
    firstAddress_ = addressOfBottom->previous;
    lastAddress_->previous = addressOfBottom;
    addressOfBottom ->next = lastAddress_;
    lastAddress_ = addressOfBottom;
    lastAddress_->previous = nullptr;

    return true;
}

bool Cards::top_to_bottom()
{
    if (lastAddress_ == nullptr) {
        return false;
    }

    else if (lastAddress_ == firstAddress_) {
        return true;
    }

    Card_data* addressOfTop = lastAddress_;
    addressOfTop->next->previous = nullptr;
    lastAddress_ = addressOfTop->next;
    firstAddress_->next = addressOfTop;
    firstAddress_ = addressOfTop;
    firstAddress_->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    s << "bottomToTop \n";
}

Cards::~Cards()
{
    Card_data* addressToFree;
    while (firstAddress_ != nullptr) {
        addressToFree = firstAddress_;
        firstAddress_ = firstAddress_->previous;
        delete addressToFree;
    }
}
