#include <iostream>
#include <string>
#include "../include/schedule_engine.hpp"
#include "../include/instructor.hpp"
#include "../include/full_time_professor.hpp"
#include "../include/occasional_lecturer.hpp"
#include "../include/course.hpp"
#include "../include/space.hpp"

// ══════════════════════════════════════════════════════════
// HELPERS para el CLI
// ══════════════════════════════════════════════════════════

void print_separator() {
    std::cout << "\n========================================\n";
}

void print_menu() {
    print_separator();
    std::cout << "   UNIVERSITY SCHEDULING SYSTEM\n";
    print_separator();
    std::cout << "1. Load data from files\n";
    std::cout << "2. Assign instructor to course\n";
    std::cout << "3. Assign room to course\n";
    std::cout << "4. List all courses\n";
    std::cout << "5. List all instructors\n";
    std::cout << "6. List all spaces\n";
    std::cout << "7. Exit\n";
    print_separator();
    std::cout << "Select an option: ";
}

// ══════════════════════════════════════════════════════════
// Verifica traslape de horario entre dos cursos
// ══════════════════════════════════════════════════════════
bool schedules_overlap(course& a, course& b) {
    if (a.get_course_day() != b.get_course_day()) return false;
    // Traslape si uno empieza antes de que el otro termine
    return a.get_start_hour() < b.get_end_hour() &&
           b.get_start_hour() < a.get_end_hour();
}

// ══════════════════════════════════════════════════════════
// Asignar instructor a curso con todas las reglas de negocio
// ══════════════════════════════════════════════════════════
void assign_instructor_to_course(schedule_engine& engine,
                                  instructor** instructors, int num_instructors,
                                  course* courses, int num_courses) {
    // Mostrar cursos disponibles
    std::cout << "\n--- Courses ---\n";
    for (int i = 0; i < num_courses; i++) {
        std::cout << i << ". " << courses[i].course_code
                  << " - " << courses[i].course_name;
        if (courses[i].get_instructor() != nullptr) {
            std::cout << " [Instructor: " << courses[i].get_instructor()->get_name() << "]";
        }
        std::cout << "\n";
    }

    int course_idx;
    std::cout << "Select course index: ";
    std::cin >> course_idx;
    if (course_idx < 0 || course_idx >= num_courses) {
        std::cout << "[ERROR] Invalid course index.\n";
        return;
    }

    // Mostrar instructores disponibles
    std::cout << "\n--- Instructors ---\n";
    for (int i = 0; i < num_instructors; i++) {
        std::cout << i << ". " << instructors[i]->get_name()
                  << " (" << instructors[i]->get_department() << ")\n";
    }

    int inst_idx;
    std::cout << "Select instructor index: ";
    std::cin >> inst_idx;
    if (inst_idx < 0 || inst_idx >= num_instructors) {
        std::cout << "[ERROR] Invalid instructor index.\n";
        return;
    }

    instructor* new_inst = instructors[inst_idx];
    course& target = courses[course_idx];

    // ── Regla: no exceder máximo de clases ──
    if (new_inst->exceeds_maximum_courses()) {
        std::cout << "[BLOCKED] " << new_inst->get_name()
                  << " has reached their maximum course limit.\n";
        return;
    }

    // ── Regla: no double-booking de instructor ──
    for (int i = 0; i < num_courses; i++) {
        if (i == course_idx) continue;
        if (courses[i].get_instructor() == new_inst &&
            schedules_overlap(courses[i], target)) {
            std::cout << "[BLOCKED] " << new_inst->get_name()
                      << " is already assigned to "
                      << courses[i].course_code
                      << " at an overlapping time.\n";
            return;
        }
    }

    // ── Regla: prioridad full_time sobre occasional ──
    instructor* current_inst = target.get_instructor();

    if (current_inst != nullptr) {
        bool new_is_fulltime = (dynamic_cast<full_time_professor*>(new_inst) != nullptr);
        bool cur_is_fulltime = (dynamic_cast<full_time_professor*>(current_inst) != nullptr);

        // Si el actual es full_time y el nuevo es occasional → bloqueado
        if (cur_is_fulltime && !new_is_fulltime) {
            std::cout << "[BLOCKED] A full-time professor is already assigned. "
                      << "Occasional lecturers cannot displace them.\n";
            return;
        }

        // Si ambos son full_time → comparar por departamento del curso
        if (cur_is_fulltime && new_is_fulltime) {
            bool new_same_dept = (new_inst->get_department() == target.department);
            bool cur_same_dept = (current_inst->get_department() == target.department);

            if (cur_same_dept && !new_same_dept) {
                std::cout << "[BLOCKED] Current professor is from the same department "
                          << "and has priority.\n";
                return;
            }
            if (!cur_same_dept && new_same_dept) {
                // nuevo tiene prioridad, desplazar al actual
                std::cout << "[INFO] " << new_inst->get_name()
                          << " from same department displaces "
                          << current_inst->get_name() << ".\n";
                // decrementar al desplazado si es occasional
                occasional_lecturer* occ = dynamic_cast<occasional_lecturer*>(current_inst);
                if (occ) occ->decrement_courses();
            }
            // Si ambos son del mismo depto o ambos de diferente → se permite
        }

        // Si el actual es occasional y el nuevo es full_time → desplazar
        if (!cur_is_fulltime && new_is_fulltime) {
            std::cout << "[INFO] Full-time professor displaces occasional lecturer "
                      << current_inst->get_name() << ".\n";
            occasional_lecturer* occ = dynamic_cast<occasional_lecturer*>(current_inst);
            if (occ) occ->decrement_courses();
        }
    }

    // ── Asignar ──
    target.set_instructor(new_inst);
    new_inst->increment_courses();
    std::cout << "[OK] " << new_inst->get_name()
              << " assigned to " << target.course_code << ".\n";
}

// ══════════════════════════════════════════════════════════
// Asignar espacio a curso con todas las reglas de negocio
// ══════════════════════════════════════════════════════════
void assign_room_to_course(course* courses, int num_courses,
                            space** spaces, int num_spaces) {
    // Mostrar cursos
    std::cout << "\n--- Courses ---\n";
    for (int i = 0; i < num_courses; i++) {
        std::cout << i << ". " << courses[i].course_code
                  << " - " << courses[i].course_name;
        if (courses[i].get_assigned_space() != nullptr) {
            std::cout << " [Room assigned]";
        }
        std::cout << "\n";
    }

    int course_idx;
    std::cout << "Select course index: ";
    std::cin >> course_idx;
    if (course_idx < 0 || course_idx >= num_courses) {
        std::cout << "[ERROR] Invalid course index.\n";
        return;
    }

    // Mostrar espacios
    std::cout << "\n--- Spaces ---\n";
    for (int i = 0; i < num_spaces; i++) {
        std::cout << i << ". " << spaces[i]->get_building_name()
                  << " Room " << spaces[i]->get_room_number()
                  << " (Capacity: " << spaces[i]->get_max_seating_capacity() << ")\n";
    }

    int space_idx;
    std::cout << "Select space index: ";
    std::cin >> space_idx;
    if (space_idx < 0 || space_idx >= num_spaces) {
        std::cout << "[ERROR] Invalid space index.\n";
        return;
    }

    course& target = courses[course_idx];
    space* new_space = spaces[space_idx];

    // ── Regla: capacidad ──
    if (target.get_enrollment() > new_space->get_max_seating_capacity()) {
        std::cout << "[BLOCKED] Room capacity (" << new_space->get_max_seating_capacity()
                  << ") is less than course enrollment (" << target.get_enrollment() << ").\n";
        return;
    }

    // ── Regla: no double-booking de espacio ──
    for (int i = 0; i < num_courses; i++) {
        if (i == course_idx) continue;
        if (courses[i].get_assigned_space() == new_space &&
            schedules_overlap(courses[i], target)) {
            std::cout << "[BLOCKED] Room " << new_space->get_building_name()
                      << " " << new_space->get_room_number()
                      << " is already booked for " << courses[i].course_code
                      << " at an overlapping time.\n";
            return;
        }
    }

    // ── Asignar ──
    target.assign_space(new_space);
    std::cout << "[OK] Room " << new_space->get_building_name()
              << " " << new_space->get_room_number()
              << " assigned to " << target.course_code << ".\n";
}

// ══════════════════════════════════════════════════════════
// Regla de salida: todos los full_time deben tener mínimo 2
// ══════════════════════════════════════════════════════════
bool can_exit(instructor** instructors, int num_instructors) {
    bool all_met = true;
    for (int i = 0; i < num_instructors; i++) {
        full_time_professor* ftp = dynamic_cast<full_time_professor*>(instructors[i]);
        if (ftp != nullptr && !ftp->meets_minimum_courses()) {
            std::cout << "[BLOCKED] " << ftp->get_name()
                      << " has only " << ftp->get_assigned_courses_count()
                      << " course(s) assigned (minimum: 2).\n";
            all_met = false;
        }
    }
    return all_met;
}

// ══════════════════════════════════════════════════════════
// MAIN
// ══════════════════════════════════════════════════════════
int main() {
    schedule_engine engine;

    // Punteros locales para operar en el main
    // El engine es dueño de la memoria; aquí solo los usamos
    instructor** instructors = nullptr;
    space**      spaces      = nullptr;
    course*      courses     = nullptr;
    int num_instructors = 0, num_spaces = 0, num_courses = 0;

    bool data_loaded = false;
    int option = 0;

    while (true) {
        print_menu();
        std::cin >> option;

        switch (option) {

        // ── 1. Cargar datos ──
        case 1: {
            try {
                engine.load_instructors("instructors.csv");
                engine.load_spaces("spaces.csv");
                engine.load_courses("courses.csv");

                // Exponer los arreglos del engine al main
                // Agrega getters en schedule_engine.h:
                //   instructor** get_instructors(); int get_num_instructors();
                //   space**      get_spaces();      int get_num_spaces();
                //   course*      get_courses();     int get_num_courses();
                instructors     = engine.get_instructors();
                num_instructors = engine.get_num_instructors();
                spaces          = engine.get_spaces();
                num_spaces      = engine.get_num_spaces();
                courses         = engine.get_courses();
                num_courses     = engine.get_num_courses();

                data_loaded = true;
                std::cout << "[OK] Data loaded successfully.\n";
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] " << e.what() << "\n";
            }
            break;
        }

        // ── 2. Asignar instructor ──
        case 2: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            assign_instructor_to_course(engine, instructors, num_instructors, courses, num_courses);
            break;
        }

        // ── 3. Asignar sala ──
        case 3: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            assign_room_to_course(courses, num_courses, spaces, num_spaces);
            break;
        }

        // ── 4. Listar cursos ──
        case 4: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            print_separator();
            for (int i = 0; i < num_courses; i++) {
                std::cout << "Course: " << courses[i].course_code
                          << " | " << courses[i].course_name
                          << " | Students: " << courses[i].get_enrollment()
                          << " | Day: " << courses[i].get_course_day()
                          << " " << courses[i].get_start_hour()
                          << "-" << courses[i].get_end_hour();
                if (courses[i].get_instructor())
                    std::cout << " | Instructor: " << courses[i].get_instructor()->get_name();
                if (courses[i].get_assigned_space())
                    std::cout << " | Room: " << courses[i].get_assigned_space()->get_building_name()
                              << " " << courses[i].get_assigned_space()->get_room_number();
                std::cout << "\n";
            }
            break;
        }

        // ── 5. Listar instructores ──
        case 5: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            print_separator();
            for (int i = 0; i < num_instructors; i++) {
                full_time_professor* ftp = dynamic_cast<full_time_professor*>(instructors[i]);
                std::cout << instructors[i]->get_name()
                          << " | " << instructors[i]->get_department()
                          << " | " << (ftp ? "Full-time" : "Occasional")
                          << " | Courses: ";
                if (ftp) std::cout << ftp->get_assigned_courses_count();
                else {
                    occasional_lecturer* occ = dynamic_cast<occasional_lecturer*>(instructors[i]);
                    if (occ) std::cout << occ->get_assigned_courses_count();
                }
                std::cout << "\n";
            }
            break;
        }

        // ── 6. Listar espacios ──
        case 6: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            print_separator();
            for (int i = 0; i < num_spaces; i++) {
                spaces[i]->print_details();
            }
            break;
        }

        // ── 7. Salir ──
        case 7: {
            if (!data_loaded || can_exit(instructors, num_instructors)) {
                std::cout << "Goodbye.\n";
                return 0;
            }
            std::cout << "[BLOCKED] Cannot exit: not all obligations are met.\n";
            break;
        }

        default:
            std::cout << "[ERROR] Invalid option.\n";
            break;
        }
    }

    return 0;
}