#ifndef LABORATORY_HPP
#define LABORATORY_HPP

#include "space.hpp"
#include <string>

class laboratory : public space {
    private:
    std::string* specialized_equipment;

    public:
    laboratory(std::string b_name, int r_num, int capacity, std::string* eq);

    virtual ~laboratory(); 

    void print_details() const override;
};


#endif