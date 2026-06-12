#include<iostream>
#include<optional>
#include<string>
#include"course.hpp"

course::course(std::string courseCode, std::string courseName, std::string dep, int n_students) {
    course_code = courseCode;
    course_name = courseName;
    department = dep;
    num_students = n_students;
}

course::~course() {

}

void course::set_instructor(instructor* inst) {
    assigned_instructor = inst;
}

instructor* course::get_instructor() {
    if (assigned_instructor.has_value()) {
        return assigned_instructor.value();
    }
    return nullptr;
}

void course::set_space(space* spac) {
    assigned_space = spac;
}

space* course::get_space() {
    if (assigned_space.has_value()) {
        return assigned_space.value();
    }
    return nullptr;
}

void course::print_details() {
    std::cout<<"Course name: "<< course_name
    << "\nCourse code: "<< course_code<<
    "\nDepartment: "<< department
    << "\nNumber of students: "<< num_students<< 
    "\nInstructor: "; 
    if (assigned_instructor.has_value())
        std::cout << "\nInstructor assigned";
    else
        std::cout << "\nNo instructor assigned";
    std::cout<<"\nSpace: "; 
    if (assigned_instructor.has_value())
        std::cout << "\nInstructor assigned"<<"\n";
    else
        std::cout << "\nNo instructor assigned"<< "\n";
}