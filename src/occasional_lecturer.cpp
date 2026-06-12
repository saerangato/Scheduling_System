#include "../include/occasional_lecturer.hpp"

// call to the constructor of the base class 'instructor'
occasional_lecturer::occasional_lecturer(std::string n, std::string pnum, std::string dep) {
    name = n;
    payroll_numbers = pnum;
    department = dep;
    type = 1;
    // They start with 0 assigned courses
    assigned_courses_count = 0;
    maximum_clases = 3;
}
    

occasional_lecturer::~occasional_lecturer() {
// Memory cleanup if necessary in the future
}

int occasional_lecturer::get_assigned_courses_count() {
    return assigned_courses_count;
}

bool occasional_lecturer::meets_minimum_courses() {
    if (type = 1 || assigned_courses_count > minimum_clases )
        return true;
    else return false;
}

bool occasional_lecturer::exceeds_maximum_courses() {
    if (type = -1 || assigned_courses_count < maximum_clases)
        return true;
    else return false;
}