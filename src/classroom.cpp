#include "../include/classroom.hpp"
#include <iostream>

classroom::classroom(std::string b_name, int r_num, int capacity)
    : space(b_name, r_num, capacity) {
}

classroom::~classroom() {}

// Implementation of the method of the abstract class "space".
void classroom::print_details() const {
    std::cout << "Classroom" << building_name << "| Room number: " << room_number 
            << " | Capacity: " << max_seating_capacity << std::endl;
}