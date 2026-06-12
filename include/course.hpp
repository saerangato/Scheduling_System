#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>
#include "space.hpp"
#include "instructor.hpp"

class course {
public: 
    std::string course_name;
    int num_students;
    std::string course_day;
    int start_hour;
    int end_hour;
    instructor* assigned_instructor;
    space* assigned_space;

    course(std::string name, int students, std::string day, int start, int end);

    // Getters necesarios para que tu schedule_engine compile
    int get_enrollment() { return num_students; }
    std::string get_course_day() { return course_day; }
    int get_start_hour() { return start_hour; }
    int get_end_hour() { return end_hour; }
    space* get_assigned_space() { return assigned_space; }
    void assign_space(space* s) { assigned_space = s; }
};

#endif