#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>
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

    course::course(std::string courseCode, std::string courseName, std::string dep, int n_students, std::string day, int start, int end);

    // Getters necesarios para que tu schedule_engine compile
    int get_enrollment() { return num_students; }
    std::string get_course_day() { return course_day; }
    int get_start_hour() { return start_hour; }
    int get_end_hour() { return end_hour; }
    space* get_assigned_space() { return assigned_space.value_or(nullptr); }
    void assign_space(space* s) { assigned_space = s; }
    void course::set_instructor(instructor* inst);
    instructor* course::get_instructor();
    void course::set_space(space* spac);
    space* course::get_space();
    void course::print_details();
};

#endif