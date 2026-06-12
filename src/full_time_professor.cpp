#include "../include/full_time_professor.hpp"

// uso la lista de inicializacion para llamar al constructor de la clase padre
full_time_professor::full_time_professor(std::string n, std::string pnum, std::string dep) 
    : instructor(n, pnum, dep) {
    
    // inician con 0 cursos asignados
    assigned_courses_count = 0;
}

full_time_professor::~full_time_professor() {
    // limpieza de memoria si fuera necesario en el futuro
}

int full_time_professor::get_assigned_courses_count() {
    return assigned_courses_count;
}