#ifndef SPACE_HPP
#define SPACE_HPP

#include <string>

class space {
protected:
    std::string building_name;
    int room_number;
    int max_seating_capacity;

public:
    space(std::string b_name, int r_num, int capacity);
    virtual ~space();

    string get_building_name() const;
    int get_room_number() const;
    int get_max_seating_capacity() const;

    virtual void print_details() const;

};

#endif