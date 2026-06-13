#ifndef SCHEDULE_ENGINE_H
#define SCHEDULE_ENGINE_H
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
};

#endif
