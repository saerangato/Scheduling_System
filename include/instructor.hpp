#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include <string>

class instructor {
protected:
    std::string name;
    std::string payroll_numbers;
    std::string department;
    int minimum_clases, type, maximum_clases;

public:
    // constructors and destructors
    instructor();
    instructor(std::string n, std::string pnum, std::string dep, int _type);
    virtual ~instructor();

    // getters and setters
    void set_name(std::string n);
    std::string get_name();

    void set_payroll_numbers(std::string pnum);
    std::string get_payroll_numbers();

    void set_department(std::string dep);
    std::string get_department();

    // operator overloading using references (correcting the UML so that it compiles correctly)
    virtual bool operator==(const instructor& other);
    virtual bool operator<(const instructor& other);
    virtual bool operator>(const instructor& other);

    bool virtual meets_minimum_courses();
    bool virtual exceeds_maximum_courses();
};

#endif