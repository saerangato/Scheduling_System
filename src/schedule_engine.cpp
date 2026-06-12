#include "schedule_engine.hpp"
#include "course.hpp"
#include "space.hpp"
#include "instructor.hpp"
#include <iostream>

using namespace std;

// 1. Iniciar todo en cero al encender el motor
schedule_engine::schedule_engine() {
    num_instructors = 0;
    num_courses = 0;
    num_spaces = 0;
    
    instructors_array = nullptr;
    courses_array = nullptr;
    spaces_array = nullptr;
}

// 2. Limpiar todo al apagar el motor
schedule_engine::~schedule_engine() {
    delete[] instructors_array;
    delete[] courses_array;
    delete[] spaces_array;
}

// 3. Las funciones 
bool schedule_engine::room_assignment(course* cour, space* spac) {
    
    // Revisar capacidad
    if (cour->get_enrollment() > spac->get_max_capacity()) {
        cout << "Error: Hay mas alumnos que sillas en este salon." << endl;
        return false; 
    }

    // --- PASO 2: EMPALMES ---
    for (int i = 0; i < num_courses; i++) {
        course* otro = courses_array[i]; 
        
        // Guardamos si chocan en el mismo lugar y día
        bool mismo_salon = (otro->get_assigned_space() == spac);
        bool mismo_dia = (otro->get_day() == cour->get_day());

        if (mismo_salon && mismo_dia) {
            // Revisamos si las horas se cruzan
            bool choca_inicio = (cour->get_start_time() < otro->get_end_time());
            bool choca_fin = (cour->get_end_time() > otro->get_start_time());

            if (choca_inicio && choca_fin) {
                cout << "Error: Este salon ya esta ocupado a esa hora." << endl;
                return false; 
            }
        }
    }

    // Si todo salió bien
    cour->assign_space(spac);
    cout << "Exito: Salon asignado." << endl;
    return true;
}

// Demás funciones

bool schedule_engine::lecturer_limit_classes() {
    for (int i = 0; i < num_instructors; i++) {
        // Le preguntamos directo al instructor si ya se pasó de su límite
        if (instructors_array[i]->exceeds_maximum_courses()) {
            cout << "Error: Un profesor de catedra excede el maximo de 3 clases." << endl;
            return false;
        }
    }
    return true;
}

bool schedule_engine::exit_program() {
    bool can_exit = true; 

    for (int i = 0; i < num_instructors; i++) {
        // Le preguntamos directo al instructor si NO cumple con su mínimo
        if (!instructors_array[i]->meets_minimum_courses()) {
            cout << "Error al salir: Un profesor de planta tiene menos de 2 clases asignadas." << endl;
            can_exit = false; 
        }
    }

    if (can_exit) {
        cout << "Obligaciones del contrato cumplidas. Cerrando sistema" << endl;
    }
    
    return can_exit;
}