#include <iostream>
#include <string>
#include <memory>
#include "address.h"

using namespace std;

/*
void Parse(const std::string& line, Address * const address) {
    if (line.size() > 5)
        throw runtime_error("Parse");
    address->Country = line;
}

void Unify(Address * const address) {
    if (address->Country.size() < 2)
        throw runtime_error("Unify");
}

std::string Format(const Address& address) {
    return address.Country + " " + address.City + " " + address.Street + " " + address.House;
}
*/

int main() {
    std::string line;
    auto address = make_unique<Address>();
    while (getline(std::cin, line)) {
        try {
            Parse(line, address.get());
            Unify(address.get());
            std::cout << Format(*address) << "\n";
        } catch (...) {
            cout << "exception\n";
        }
    }
    return 0;
}
