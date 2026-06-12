#include "../include/laboratory.hpp"
#include <iostream>

laboratory::laboratory(std::string b_name, int r_num, int capacity, std::string* eq)
    : space(b_name, r_num, capacity), specialized_equipment(eq) {
}

laboratory::~laboratory() {
    if (specialized_equipment != nullptr) {
        delete specialized_equipment;
        specialized_equipment = nullptr;
    }
}

void laboratory::print_details() const {
    std::cout << "Laboratory " << building_name << " | Lab number: " << room_number
              << " | Capacity " << max_seating_capacity
              << " | Equipment ";
              
    // Validación de seguridad para el puntero dinámico
    if (specialized_equipment != nullptr) {
        std::cout << *specialized_equipment << std::endl;
    } else {
        std::cout << "None" << std::endl;
    }
}