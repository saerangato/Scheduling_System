#include "../include/instructor.hpp"

// default constructor
instructor::instructor() {
    name = "";
    payroll_numbers = "";
    department = "";
}

// constructor with parameters
instructor::instructor(std::string n, std::string pnum, std::string dep) {
    name = n;
    payroll_numbers = pnum;
    department = dep;
}


// virtual destructor (empty, but necessary for polymorphism)
instructor::~instructor() {}

// getters and setters 

void instructor::set_name(std::string n) {
    name = n;
}

std::string instructor::get_name() {
    return name;
}

void instructor::set_payroll_numbers(std::string pnum) {
    payroll_numbers = pnum;
}

std::string instructor::get_payroll_numbers() {
    return payroll_numbers;
}

void instructor::set_department(std::string dep) {
    department = dep;
}

std::string instructor::get_department() {
    return department;
}


// operator overloading

bool instructor::operator==(const instructor& other) {
// Two instructors are equal if they have the same payroll number
    return this->payroll_numbers == other.payroll_numbers;
}

bool instructor::operator<(const instructor& other) {
    // Basic logic for the scheduling engine to expand it
    // An occasional teacher is "less than" a full-time teacher
    return false; //simple placeholder 
}

bool instructor::operator>(const instructor& other) {
  // Same as the < operator but in reverse
    return false; // simple placeholder 
}