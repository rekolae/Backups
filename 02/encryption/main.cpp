#include <iostream>
#include <string>

using namespace std;

int error (string key);
int string_is_lower(string text);
int lowercase_alphabets_in_key(string key);
void encrypt (string key, string message);

int main ()
{   string key;
    string message;
    cout << "Enter the encryption key: ";
    cin >> key;

    if (not error(key)) {

        cout << "Enter the text to be encrypted: ";
        cin >> message;
        if (not string_is_lower(message)) {
            exit(EXIT_FAILURE);
        }

        else {
            encrypt(key, message);
        }
    }

    else {
        exit(EXIT_FAILURE);
    }

}


void encrypt(string key, string message)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int index_number;
    char encrypted_char;
    int len = message.length();
    string encrypted_message;
    for (int x = 0; x < len; x++) {
        index_number = alphabet.find(message.at(x));
        encrypted_char = key.at(index_number);
        encrypted_message += encrypted_char;
    }
    cout << "Encrypted text: " << encrypted_message << endl;
}



int error (string key)
{
    if (key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return true;
    }

    else if (not string_is_lower(key)) {
        return true;
    }

    else if (not lowercase_alphabets_in_key(key)) {
        return true;
    }

    else {
        return false;
    }
}


int string_is_lower (string text)
{
    int len = text.length();
    for (int x = 0; x < len; x++) {
        int ascii_value =  static_cast< int >( text.at(x) );
        if (ascii_value < 97) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }
    }

    return true;
}


int lowercase_alphabets_in_key(string key)
{
    string alphabet = "abcdefghijklmnopqrtsuvwxyz";
    for (int x = 0; x < 26; x++) {
        if (key.find(alphabet.at(x)) == std::string::npos) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return false;
        }
    }

    return true;
}



















