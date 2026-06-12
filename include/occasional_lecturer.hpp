#ifndef OCCASIONAL_LECTURER_HPP
#define OCCASIONAL_LECTURER_HPP

#include "instructor.hpp"
#include <string>

class occasional_lecturer : public instructor {
private:
    int assigned_courses_count;

public:
    occasional_lecturer(std::string n, std::string pnum, std::string dep);
   virtual ~occasional_lecturer();

    int get_assigned_courses_count();
    bool virtual meets_minimum_courses();
    bool virtual exceeds_maximum_courses();
};

#endif