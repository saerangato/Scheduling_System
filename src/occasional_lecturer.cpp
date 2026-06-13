#include "../include/occasional_lecturer.hpp"

// call to the constructor of the base class 'instructor'
occasional_lecturer::occasional_lecturer(std::string n, std::string pnum, std::string dep) {
    name = n;
    payroll_numbers = pnum;
    department = dep;
    type = 1;
    // They start with 0 assigned courses
    assigned_courses_count = 0;
    maximum_classes = 3;
}
    

occasional_lecturer::~occasional_lecturer() {
// Memory cleanup if necessary in the future
}

int occasional_lecturer::get_assigned_courses_count() {
    return assigned_courses_count;
}

bool occasional_lecturer::meets_minimum_courses() {
    return true; // occasional no tiene mínimo
}

bool occasional_lecturer::exceeds_maximum_courses() {
    return assigned_courses_count >= maximum_classes; // has reached 3?
}

void occasional_lecturer::increment_courses() {
    assigned_courses_count++;
}

void occasional_lecturer::decrement_courses() {
    assigned_courses_count--;
}