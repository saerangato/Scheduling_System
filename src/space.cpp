#include "../include/space.hpp"
#include <iostream>

    space::space(std::string b_name, int r_num, int capacity)
        : building_name(b_name), room_number(r_num), max_seating_capacity(capacity){

        };

    space::~space(){};

    std::string space::get_building_name() const {
        return building_name;
    }

    int space::get_room_number() const{
        return room_number;
    }

    int space::get_max_seating_capacity() const{
        return max_seating_capacity;
    }

