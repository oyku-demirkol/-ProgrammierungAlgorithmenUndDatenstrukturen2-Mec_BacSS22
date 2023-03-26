/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include<cassert>
#include<algorithm>

using namespace std;

std::string read_iban() {
    std::string iban;
    std::cout << "iban(please without space character): ";
    std::cin >> iban;
    return iban;
}

std::string get_country(std::string iban) {
    auto country = iban.substr(0, 2);

    return country;
}
std::string get_country_alphabet_position(std::string country) {
    string result = "";
    for (int IndexOfcharacter = 0; IndexOfcharacter < country.size(); IndexOfcharacter++) {
        int value = (int)country[IndexOfcharacter] - 55;
        result += to_string(value);
    }

    return result;
}
std::string get_alphabet_position(std::string alphabet) {
    string result = "";
    for (char c : alphabet) {

        if (isdigit(c)) {
            result = c;
        }
        else {
            result += to_string(c - 55);
        }

    }

    return result;
}
int string_modulo(const std::string& num, int divisor) {
    if (num.size() <= 2)
        return stoi(num) % divisor;

    int reminder = stoi(num.substr(0, 2));
    for (int i = 2; i < num.length(); i += 7) {
        reminder = stoi(to_string(reminder) + num.substr(i, 7)) % divisor;
    }
    return reminder;
}

bool is_valid_iban_at(std::string iban) {

    if (iban.length() != 20) {
        return false;
    }

    //https://en.wikipedia.org/wiki/International_Bank_Account_Number

    string bank = iban.substr(4, 5);
    string account = iban.substr(9, 11);
    string country = get_country_alphabet_position("AT"); //convert to int
    string check = iban.substr(2, 2);
    // num = bank + account + country + check 
    string num = bank + account + country + check;
    int res = string_modulo(num, 97);
    if (res == 1) {
        return true;
    }
    else {

        return false;
    }
}
bool is_valid_iban_de(std::string iban) {

    if (iban.length() != 22) {
        return false;
    }

    //https://en.wikipedia.org/wiki/International_Bank_Account_Number
    string country = get_country_alphabet_position("DE"); //convert to int
    string check = iban.substr(2, 2);
    string bank = iban.substr(4, 5);
    string account = iban.substr(9, 13);


    // num = bank + account + country + check 
    string num = bank + account + country + check;
    int res = string_modulo(num, 97);
    if (res == 1) {
        return true;
    }
    else {

        return false;
    }
}
bool is_valid_iban_it(std::string iban) {

    if (iban.length() != 27) {
        return false;
    }

    string bank = iban.substr(5, 10);
    string account = iban.substr(15, 12);
    string country = get_country_alphabet_position("IT"); //convert to int
    string CIN = get_alphabet_position(iban.substr(4, 1));
    string check = iban.substr(2, 2);
    // num = cin + bank + account +country +check  
    string num = CIN + bank + account + country + check;
    int res = string_modulo(num, 97);
    if (res == 1) {
        return true;
    }
    else {

        return false;
    }
}

int main() {
    string iban = read_iban();
    string country = get_country(iban);
    if (country == "AT") {
        cout << (is_valid_iban_at(iban) ? "okey\n" : "not okey\n");
    }
    if (country == "DE") {
        cout << (is_valid_iban_de(iban) ? "okey\n" : "not okey\n");
    }
    if (country == "IT") {
        cout << (is_valid_iban_it(iban) ? "okey\n" : "not okey\n");
    }




}
