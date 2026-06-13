#include "../include/full_time_professor.hpp"
#include<iostream>

// I use the initialization list to call the parent class constructor
full_time_professor::full_time_professor(std::string n, std::string pnum, std::string dep) {
    type = -1;
    name = n;
    payroll_numbers = pnum;
    department = dep;
// They start with 0 assigned courses
    assigned_courses_count = 0;
    minimum_classes = 2;
}

full_time_professor::~full_time_professor() {
// Memory clearing if necessary in the future
}

int full_time_professor::get_assigned_courses_count() {
    return assigned_courses_count;
}

bool full_time_professor::meets_minimum_courses() {
    if (type == 1 || assigned_courses_count > minimum_classes )
        return true;
    else return false;
}

bool full_time_professor::exceeds_maximum_courses() {
    if (type == -1 || assigned_courses_count < maximum_classes)
        return true;
    else return false;
}