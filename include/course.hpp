#pragma once
#include <string>
#include <optional>
#include "instructor.hpp"
#include "space.hpp"

class course {
    private:
        std::string course_code;
        std::string course_name;
        std::string department;
        int num_students;
        std::optional<instructor*> assigned_instructor;
        std::optional<space*> assigned_space;
    public:
        course(std::string courseCode, std::string courseName, std::string dep, int n_students);
        ~course();
        void set_instructor(instructor* inst);
        instructor* get_instructor();
        void set_space(space* spac);
        space* get_space();
        virtual void print_details();
        int get_enrollment() { return num_students; }
        std::string get_course_day() { return "Monday"; } 
        int get_start_hour() { return 8; }             
        int get_end_hour() { return 10; }                 
        space* get_assigned_space() { return assigned_space.value_or(nullptr); }
        void assign_space(space* s) { assigned_space = s; }
};