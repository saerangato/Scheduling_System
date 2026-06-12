#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include<optional>
#include "space.hpp"
#include "instructor.hpp"

class course {
public: 
    std::string course_name, course_code, department;
    int num_students;
    std::string course_day;
    int start_hour;
    int end_hour;
    std::optional<instructor*> assigned_instructor;
    std::optional<space*> assigned_space;

    course(std::string courseCode, std::string courseName, std::string dep, int n_students, std::string day, int start, int end);
    
    ~course();

    void course::set_instructor(instructor* inst);
    instructor* course::get_instructor();
    void course::set_space(space* spac);
    space* course::get_space();
    void course::print_details();

    // Getters & setters
    int get_enrollment();
    std::string get_course_day();
    int get_start_hour();
    int get_end_hour();
    space* get_assigned_space();
    void assign_space(space* s);
};

#endif