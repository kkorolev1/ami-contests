#pragma once

#include <string>


class Animal {
public:
    virtual std::string voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal() {
    }
};


class Tiger: public Animal {
    std::string voice() const override {
        return "Rrrr";
    }
};


class Wolf: public Animal {
    std::string voice() const override {
        return "Wooo";
    }
};


class Fox: public Animal {
    std::string voice() const override {
        return "Tyaf";
    }
};