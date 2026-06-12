#include<iostream>
#include<string>
#include"course.hpp"

course::course(std::string courseCode, std::string courseName, std::string dep, int n_students) {
    course_code = courseCode;
    course_name = courseName;
    department = dep;
    num_students = n_students;
}

course::~course() {
std::cout<<"hola";
}

void course::set_instructor(instructor* inst) {
    assigned_instructor.instructor(inst);
}

instructor* course::get_instructor() {
    return assigned_instructor;
}

void course::set_space(space* spac) {
    assigned_space.space(spac);
}

space* course::get_space() {
    return assigned_space;
}

void course::print_details() {
    std::cout<<"Course name: ", course_name, "\nCourse code: ", course_code, "\nDepartment: ", department, "\nNumber of students: ", num_students, "\nInstructor: ", assigned_instructor, "\nSpace: ", assigned_space, "\n";
}