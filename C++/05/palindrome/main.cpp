#include <iostream>
#include <string>
#include <algorithm>


bool checker(std::string word, std::string reverse, int n)
{
    if (n == 0) {
        return true;
    }
    else if (word.at(n - 1) == reverse.at(n - 1)) {
        return checker(word, reverse, n - 1);
    }
    else {
        return false;
    }
}


bool palindrome_recursive(std::string word) {
    std::string word_reverse = word;
    std::reverse(word.begin(), word.end());
    int n = word.length();
    if (checker(word, word_reverse, n)) {
        return true;
    }

    else {
        return false;
    }
}

int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
