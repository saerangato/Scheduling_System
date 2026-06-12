#ifndef CLASSROOM_HPP
#define CLASSROOM_HPP

#include "space.hpp"
#include <string>

class classroom : public space {
    public:
    classroom(std::string b_name, int r_num, int capacity);

    virtual ~classroom(); // agregar a UML

    void print_details() const override;
};


#endif