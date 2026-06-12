#include <iostream>
#include <optional>
#include <string>
#include "../include/course.hpp"

// Ajustamos el constructor para recibir los nuevos parámetros
course::course(std::string courseCode, std::string courseName, std::string dep, int n_students, std::string day, int start, int end) {
    course_code = courseCode;
    course_name = courseName;
    department = dep;
    num_students = n_students;
    course_day = day;
    start_hour = start;
    end_hour = end;
}

course::~course() {}

void course::set_instructor(instructor* inst) {
    assigned_instructor = inst;
}

instructor* course::get_instructor() {
    return assigned_instructor.value_or(nullptr);
}

void course::set_space(space* spac) {
    assigned_space = spac;
}

space* course::get_space() {
    return assigned_space.value_or(nullptr);
}

void course::print_details() {
    std::cout << "Course: " << course_name << " (" << course_code << ")" << std::endl;
}

int course::get_enrollment() { 
    return num_students; 
}

std::string course::get_course_day() { 
    return course_day; 
}
    
int course::get_start_hour() { 
    return start_hour; 
}
    
int course::get_end_hour() { 
    return end_hour; 
}

space* course::get_assigned_space() { 
    return assigned_space.value_or(nullptr); 
}
    
void course::assign_space(space* s) { 
    assigned_space = s; 
}
