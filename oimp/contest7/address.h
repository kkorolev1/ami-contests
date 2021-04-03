#include <string>

using namespace std;

struct Address {
    std::string Country;
    std::string City;
    std::string Street;
    std::string House;
};

void Parse(const std::string& line, Address * const address);

void Unify(Address * const address);

std::string Format(const Address& address);