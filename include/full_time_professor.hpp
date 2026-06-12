#ifndef FULL_TIME_PROFESSOR_HPP
#define FULL_TIME_PROFESSOR_HPP

#include "instructor.hpp"
#include <string>

class full_time_professor : public instructor {
private:
    int assigned_courses_count;

public:
    full_time_professor(std::string n, std::string pnum, std::string dep);
    virtual ~full_time_professor();

    int get_assigned_courses_count();
    bool virtual meets_minimum_courses();
    bool virtual exceeds_maximum_courses();
};

#endif