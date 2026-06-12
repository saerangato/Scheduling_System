#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include <string>

class instructor {
protected:
    std::string name;
    std::string payroll_numbers;
    std::string department;

public:
    // constructores y destructor
    instructor();
    instructor(std::string n, std::string pnum, std::string dep);
    virtual ~instructor();

    // getters y setters
    void set_name(std::string n);
    std::string get_name();

    void set_payroll_numbers(std::string pnum);
    std::string get_payroll_numbers();

    void set_department(std::string dep);
    std::string get_department();

    // Ssbrecarga de operadores usando referencias (corrigiendo el UML para que compile bien)
    virtual bool operator==(const instructor& other);
    virtual bool operator<(const instructor& other);
    virtual bool operator>(const instructor& other);
};

#endif