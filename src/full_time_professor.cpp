#include "../include/full_time_professor.hpp"

// I use the initialization list to call the parent class constructor
full_time_professor::full_time_professor(std::string n, std::string pnum, std::string dep) 
    : instructor(n, pnum, dep) {
    
// They start with 0 assigned courses
    assigned_courses_count = 0;
}

full_time_professor::~full_time_professor() {
// Memory clearing if necessary in the future
}

int full_time_professor::get_assigned_courses_count() {
    return assigned_courses_count;
}