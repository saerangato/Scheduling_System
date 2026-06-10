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
    public:
        course(std::string course_code, std::string course_name, std::string dep, int n_students);
        ~course();
        void set_instructor();
        void* get_instructor();
        void set_space();
        void* get_space();
        void virtual print_details();
};