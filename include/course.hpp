#include<iostream>
#include<string>
#include"instructor.hpp"
#include"space.hpp"

class course {
    private:
        std::string course_code;
        std::string course_name;
        std::string department;
        int num_students;
        optional <instructor*> assigned_instructor;
        optional <space*> assigned_space;
    public:
        course(std::string courseCode, std::string courseName, std::string dep, int n_students);
        ~course();
        void set_instructor(instructor* inst);
        instructor* get_instructor();
        void set_space(space* spac);
        space* get_space();
        void virtual print_details();
};