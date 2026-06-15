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
    course* courses_array;

    int num_instructors;
    int num_courses;
    int num_spaces;

    bool schedules_overlap(course& a, course& b);

public:
    // Constructor y Destructor
    schedule_engine();
    ~schedule_engine();

    // Métodos de operación
    bool room_assignment(course* cour, space* spac);
    bool lecturer_limit_classes();
    bool exit_program();
    void assign_instructor_to_course();
    void assign_room_to_course();

    // Getters
    instructor** get_instructors()  { return instructors_array; }
    int get_num_instructors()       { return num_instructors; }
    space**      get_spaces()       { return spaces_array; }
    int get_num_spaces()            { return num_spaces; }
    course*      get_courses()      { return courses_array; }
    int get_num_courses()           { return num_courses; }

    // Load data
    void load_instructors(const std::string& filename);
    void load_spaces(const std::string& filename);
    void load_courses(const std::string& filename);
};

#endif