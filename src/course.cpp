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

// Estas son las funciones que el compilador te estaba pidiendo
// para que el motor de horarios funcione correctamente:

void course::print_details() {
    std::cout << "Course: " << course_name << " (" << course_code << ")" << std::endl;
}