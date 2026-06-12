#include "../include/occasional_lecturer.hpp"

// call to the constructor of the base class 'instructor'
occasional_lecturer::occasional_lecturer(std::string n, std::string pnum, std::string dep) 
    : instructor(n, pnum, dep) {
    

// They start with 0 assigned courses
    assigned_courses_count = 0;
}

occasional_lecturer::~occasional_lecturer() {
// Memory cleanup if necessary in the future
}

int occasional_lecturer::get_assigned_courses_count() {
    return assigned_courses_count;
}