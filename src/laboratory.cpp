#include "../include/laboratory.hpp"
#include <iostream>

laboratory::laboratory(std::string b_name, int r_num, int capacity, std::string* eq)
    : space(b_name, r_num, capacity), specialized_equipment(eq) {
}

// It's important to release the pointer's memory in the destructor.
laboratory::~laboratory() {
    if (specialized_equipment != nullptr) {
        delete specialized_equipment;
        specialized_equipment = nullptr;
    }
}

// Implementation of the method of the abstract class "space".
void laboratory::print_details() const {
    std::cout << "Laboratory " << building_name << " | Lab number: " << room_number 
            << "| Capacity " << max_seating_capacity 
            << "| Equipment " << *specialized_equipment << std::endl;
}