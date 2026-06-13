#ifndef SCHEDULE_ENGINE_H
#define SCHEDULE_ENGINE_H
#include <string> 
class instructor;
class course;
class space;

class schedule_engine {
private:
    instructor** instructors_array;
    space** spaces_array;
    course* courses_array; // Este puede quedarse con un solo *, porque course no hereda de nadie

    
    int num_instructors;
    int num_courses;
    int num_spaces;

public:
    // Constructor y Destructor
    schedule_engine();
    ~schedule_engine();

    // Métodos de operación
    bool room_assignment(course* cour, space* spac);
    bool lecturer_limit_classes();
    bool exit_program();

    // Getters
    instructor** get_instructors()   { return instructors_array; }
    int get_num_instructors()        { return num_instructors; }
    space**      get_spaces()        { return spaces_array; }
    int get_num_spaces()             { return num_spaces; }
    course*      get_courses()       { return courses_array; }
    int get_num_courses()            { return num_courses; }

    // Load data
    void load_instructors(const std::string& filename);
    void load_spaces(const std::string& filename);
    void load_courses(const std::string& filename);
};

#endif
