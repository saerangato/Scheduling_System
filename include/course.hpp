#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include<optional>
#include "space.hpp"
#include "instructor.hpp"
#include "schedule.hpp"

class course {
public: 
    std::string course_name, course_code, department;
    int num_students;
    schedule course_schedule; // replacement of primitive variables for the object schedule
    std::optional<instructor*> assigned_instructor;
    std::optional<space*> assigned_space;

    course(std::string courseCode, std::string courseName, std::string dep, int n_students, schedule sched);
    
    ~course();

    void set_instructor(instructor* inst);
    instructor* get_instructor();
    void set_space(space* spac);
    space* get_space();
    void print_details();

    // Getters & setters
    int get_enrollment();
    std::string get_course_day();
    int get_start_hour();
    int get_end_hour();
    schedule get_schedule();
    space* get_assigned_space();
    void assign_space(space* s);
};

#endif