#include "../include/occasional_lecturer.hpp"

// llamada al constructor de la clase base 'instructor'
occasional_lecturer::occasional_lecturer(std::string n, std::string pnum, std::string dep) 
    : instructor(n, pnum, dep) {
    
    // inician con 0 cursos asignados
    assigned_courses_count = 0;
}

occasional_lecturer::~occasional_lecturer() {
    // impieza de memoria si fuera necesario en el futuro
}

int occasional_lecturer::get_assigned_courses_count() {
    return assigned_courses_count;
}