#include <iostream>
#include <optional>
#include <string>
#include "../include/course.hpp"

// Ajustamos el constructor para recibir los nuevos parámetros
course::course(std::string courseCode, std::string courseName, std::string dep, int n_students, schedule sched) {
    course_code = courseCode;
    course_name = courseName;
    department = dep;
    num_students = n_students;
    course_schedule = sched;
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
    return course_schedule.get_day_of_week(); 
}

int course::get_start_hour() {
    return course_schedule.get_start_time(); 
}

int course::get_end_hour() {
    return course_schedule.get_end_time(); 
}

space* course::get_assigned_space() { 
    return assigned_space.value_or(nullptr); 
}
    
void course::assign_space(space* s) { 
    assigned_space = s; 
}
